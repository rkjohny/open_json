#ifndef OPEN_JSON_SERIALIZER_H
#define OPEN_JSON_SERIALIZER_H

#include <iostream>
#include "CommonDef.h"
#include "TypeTraits.h"
#include "nlohmann/json.hpp"
#include "boost/optional.hpp"
#include "string"
#include "Getter.h"


namespace open_json::serializer {

    template<class T>
    std::enable_if_t<is_pointer_v<T>, void>
    static GetData(T &object, nlohmann::json &jsonObject, const char * name);

    template<class T>
    std::enable_if_t<!is_pointer_v<T>, void>
    static GetData(T &object, nlohmann::json &jsonObject, const char * name);

    template<std::size_t iteration, class T>
    static void DoSerialize(const T &object, nlohmann::json &jsonObject);

    template<std::size_t iteration, class T>
    std::enable_if_t<(iteration > 1), void>
    static Serialize(const T &object, nlohmann::json &jsonObject);

    template<std::size_t iteration, class T>
    std::enable_if_t<(iteration == 1), void>
    static Serialize(const T &object, nlohmann::json &jsonObject);

    template<std::size_t iteration, class T>
    std::enable_if_t<(iteration == 0), void>
    static Serialize(const T &object, nlohmann::json &);

    template<class T>
    std::enable_if_t<is_enum_v<T> && !is_pointer_v<T>, nlohmann::json>
    static ToJsonObject(const T &object);

    template<class T>
    std::enable_if_t<
            (is_number_v<T> || is_bool_v<T>) && !is_pointer_v<T>, nlohmann::json>
    static ToJsonObject(const T &object);

    template<class T>
    std::enable_if_t<is_char_v<T> && !is_pointer_v<T>, nlohmann::json>
    static ToJsonObject(const T &object);

    template<class T>
    std::enable_if_t<is_string_v<T> && !is_pointer_v<T>, nlohmann::json>
    static ToJsonObject(const T &object);

    template<class T>
    static nlohmann::json ToJsonObject(const std::unique_ptr<T> &object);

    template<class T>
    static nlohmann::json ToJsonObject(const std::shared_ptr<T> &object);

    template<class T>
    static nlohmann::json ToJsonObject(const std::weak_ptr<T> &object);

    template<class T>
    static nlohmann::json ToJsonObject(const boost::optional<T> &object);

    template<class T>
    std::enable_if_t<is_class_v<T> && !is_pointer_v<T>, nlohmann::json>
    static ToJsonObject(const T &object);

    template<class T>
    std::enable_if_t<is_vector_v<T> && !is_pointer_v<T>, nlohmann::json>
    static ToJsonObject(const T &object);

    template<class T>
    std::enable_if_t<is_array_v<T>, nlohmann::json>
    static ToJsonObject(const T &object, const std::size_t &length);

    template<class T>
    std::enable_if_t<is_pointer_v<T> && !is_array_v<T>, nlohmann::json>
    static ToJsonObject(const T &object, const std::size_t &length);

    template<class T>
    std::enable_if_t<is_pointer_v<T> && !is_array_v<T>, nlohmann::json>
    static ToJsonObject(const T &object);


    template<class T>
    std::enable_if_t<!is_pointer_v<T>, void>
    static GetData(T &object, nlohmann::json &jsonObject, const char * name) {
        jsonObject[std::string(name)] = ToJsonObject(object);
    }

    template<class T>
    std::enable_if_t<is_pointer_v<T>, void>
    static GetData(T &object, nlohmann::json &jsonObject, const char * name) {
        if (object) {
            jsonObject[std::string(name)] = ToJsonObject(object);
        }
    }

    template<std::size_t iteration, class T>
    static void DoSerialize(const T &object, nlohmann::json &jsonObject) {
        using ObjectType = remove_all_cvrp_t<T>;
        constexpr auto getter = std::get<iteration>(ObjectType::getters);
        auto getterName = getter.name;
        //using GetterReturnType = typename decltype( getter )::type;
        auto method = getter.fp;

        const auto returnedObject = (object.*method)();

        GetData(returnedObject, jsonObject, getterName);
    }

    template<std::size_t iteration, class T>
    std::enable_if_t<(iteration > 1), void>
    static Serialize(const T &object, nlohmann::json &jsonObject) {
        DoSerialize<iteration - 1, T>(object, jsonObject);

        Serialize<iteration - 1, T>(object, jsonObject);
    }

    template<std::size_t iteration, class T>
    std::enable_if_t<(iteration == 1), void>
    static Serialize(const T &object, nlohmann::json &jsonObject) {
        DoSerialize<0, T>(object, jsonObject);
    }

    /**
     * added to remove compile error.
     * when setters length is 0, it will try to compile with iteration = 0
     */
    template<std::size_t iteration, class T>
    std::enable_if_t<(iteration == 0), void>
    static Serialize(const T &, nlohmann::json &) {
    }


    //////////////////////////////// Enum ///////////////////
    template<class T>
    std::enable_if_t<is_enum_v<T> && !is_pointer_v<T>, nlohmann::json>
    static ToJsonObject(const T &object) {
        return nlohmann::json(static_cast<int>(object));
    }

    //////////////////////////////// Bool, Integer, Decimal ///////////////////
    template<class T>
    std::enable_if_t<
            (is_number_v<T> || is_bool_v<T>) && !is_pointer_v<T>, nlohmann::json>
    static ToJsonObject(const T &object) {
        return nlohmann::json(object);
    }

    ///////////////// char ///////////////////////////////////
    // TODO: why it is needed? it should be covered by is_int8
    template<class T>
    std::enable_if_t<is_char_v<T> && !is_pointer_v<T>, nlohmann::json>
    static ToJsonObject(const T &object) {
        return nlohmann::json(static_cast<int8_t> (object));
    }

    /////////////////////// std::string //////////////////////////////////////
    template<class T>
    std::enable_if_t<is_string_v<T> && !is_pointer_v<T>, nlohmann::json>
    static ToJsonObject(const T &object) {
        return nlohmann::json(std::string(object));
    }

    //////////////////  custom object ////////////////////////
    template<class T>
    std::enable_if_t<is_class_v<T> && !is_pointer_v<T>, nlohmann::json>
    static ToJsonObject(const T &object) {
        nlohmann::json jsonObject = nlohmann::json::object();

        using ObjectType = remove_all_cvrp_t<T>;
        auto getters = ObjectType::getters;
        const auto length = std::tuple_size<decltype(getters)>::value;
        if (length > 0) {
            Serialize<length>(object, jsonObject);
        }
        return jsonObject;
    }

    //////////////////  std::vector ////////////////////////
    template<class T>
    std::enable_if_t<is_vector_v<T> && !is_pointer_v<T>, nlohmann::json>
    static ToJsonObject(const T &object) {
        std::size_t length = object.size();
        nlohmann::json jsonObject = nlohmann::json::array();

        if (length > 0) {
            for (auto &arrValue: object) {
                jsonObject.push_back(ToJsonObject(arrValue));
            }
        }
        return jsonObject;
    }

    ////////////////// Array ///////////////////////////////
    template<class T>
    std::enable_if_t<is_array_v<T>, nlohmann::json>
    static ToJsonObject(const T &object, const std::size_t &length) {
        nlohmann::json jsonObject = nlohmann::json::array();
        if (length > 0) {
            for (std::size_t i = 0; i < length; ++i) {
                jsonObject.push_back(ToJsonObject(object[i]));
            }
        }
        return jsonObject;
    }

    template<class T>
    std::enable_if_t<is_pointer_v<T> && !is_array_v<T>, nlohmann::json>
    static ToJsonObject(const T &object, const std::size_t &length) {
        nlohmann::json jsonObject = nlohmann::json::array();
        if (object) {
            if (length > 0) {
                for (std::size_t i = 0; i < length; ++i) {
                    jsonObject.push_back(ToJsonObject(object[i]));
                }
            }
        }
        return jsonObject;
    }

    ////////////////// Map ///////////////////////////////
    template<class T>
    std::enable_if_t<is_map_v<T> && !is_pointer_v<T>, nlohmann::json>
    static ToJsonObject(const T &object) {
        nlohmann::json jsonObject = nlohmann::json::object();

        auto itr = object.begin();
        while (itr != object.end()) {
            auto &key = itr->first;
            auto &value = itr->second;
            jsonObject[ToJsonObject(key)] = ToJsonObject(value);
            ++itr;
        }
        return jsonObject;
    }

    ////////////////// Pointer ///////////////////////////////
    template<class T>
    std::enable_if_t<is_pointer_v<T> && !is_array_v<T>, nlohmann::json>
    static ToJsonObject(const T &object) {
        if (object) {
            return ToJsonObject(*object);
        }
        return {};
    }

    ///////////////////// std::unique_ptr<T> ///////////////////////////////////
    template<class T>
    static nlohmann::json ToJsonObject(const std::unique_ptr<T> &object) {
        if (object) {
            return ToJsonObject(*object);
        }
        return {};
    }

    ///////////////////// std::shared_ptr<T> ///////////////////////////////////
    template<class T>
    static nlohmann::json ToJsonObject(const std::shared_ptr<T> &object) {
        if (object) {
            return ToJsonObject(*object);
        }
        return {};
    }

    ///////////////////// std::weak_ptr<T> ///////////////////////////////////
    template<class T>
    static nlohmann::json ToJsonObject(const std::weak_ptr<T> &object) {
        auto sharedObject = object.lock();
        if (sharedObject) {
            nlohmann::json jsonObject = ToJsonObject(*sharedObject);
            sharedObject.reset();
            return jsonObject;
        }
        return {};
    }

    ///////////////////// boost::optional<T> ///////////////////////////////////
    template<class T>
    static nlohmann::json ToJsonObject(const boost::optional<T> &object) {
        if (object) {
            return ToJsonObject(*object);
        }
        return {};
    }

}


#endif //OPEN_JSON_SERIALIZER_H
