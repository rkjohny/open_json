#ifndef OPEN_JSON_SERIALIZER_H
#define OPEN_JSON_SERIALIZER_H

#include <iostream>
#include "CommonDef.h"
#include "TypeTraits.h"
#include "nlohmann/json.hpp"
#include "boost/optional.hpp"
#include "string"


namespace open_json {
    namespace serializer {

        template<std::size_t iteration, class T>
        static void DoSerialize(const T &object, nlohmann::json &jsonObject);

        template<std::size_t iteration, class T>
        typename std::enable_if<(iteration > 1), void>::type
        static Serialize(const T &object, nlohmann::json &jsonObject);

        template<std::size_t iteration, class T>
        typename std::enable_if<(iteration == 1), void>::type
        static Serialize(const T &object, nlohmann::json &jsonObject);

        template<std::size_t iteration, class T>
        typename std::enable_if<(iteration == 0), void>::type
        static Serialize(const T &object, nlohmann::json &);

        template<class T>
        typename std::enable_if<Is_Enum<T>::Value && !Is_Pointer<T>::Value, nlohmann::json>::type
        static ToJsonObject(const T &object);

        template<class T>
        typename std::enable_if<
                (Is_Number<T>::Value || Is_Bool<T>::Value) && !Is_Pointer<T>::Value, nlohmann::json>::type
        static ToJsonObject(const T &object);

        template<class T>
        typename std::enable_if<Is_Char<T>::Value && !Is_Pointer<T>::Value, nlohmann::json>::type
        static ToJsonObject(const T &object);

        template<class T>
        typename std::enable_if<Is_String<T>::Value && !Is_Pointer<T>::Value, nlohmann::json>::type
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
        typename std::enable_if<Is_Class<T>::Value && !Is_Pointer<T>::Value, nlohmann::json>::type
        static ToJsonObject(const T &object);

        template<class T>
        typename std::enable_if<Is_Vector<T>::Value && !Is_Pointer<T>::Value, nlohmann::json>::type
        static ToJsonObject(const T &object);

        template<class T>
        typename std::enable_if<Is_Array<T>::Value, nlohmann::json>::type
        static ToJsonObject(const T &object, const std::size_t &length);

        template<class T>
        typename std::enable_if<Is_Pointer<T>::Value && !Is_Array<T>::Value, nlohmann::json>::type
        static ToJsonObject(const T &object, const std::size_t &length);

        template<class T>
        typename std::enable_if<Is_Pointer<T>::Value && !Is_Array<T>::Value, nlohmann::json>::type
        static ToJsonObject(const T &object);


        template<std::size_t iteration, class T>
        static void DoSerialize(const T &object, nlohmann::json &jsonObject) {
            using ObjectType = typename Remove_CVRP<T>::Type;
            constexpr auto getter = std::get<iteration>(ObjectType::getters);
            auto getterName = getter.name;
            //using GetterReturnType = typename decltype( getter )::Type;
            auto method = getter.fp;

            const auto &getterReturnedObject = (object.*method)();

            jsonObject[std::string(getterName)] = ToJsonObject(getterReturnedObject);
        }

        template<std::size_t iteration, class T>
        typename std::enable_if<(iteration > 1), void>::type
        static Serialize(const T &object, nlohmann::json &jsonObject) {
            DoSerialize<iteration - 1, T>(object, jsonObject);

            Serialize<iteration - 1, T>(object, jsonObject);
        }

        template<std::size_t iteration, class T>
        typename std::enable_if<(iteration == 1), void>::type
        static Serialize(const T &object, nlohmann::json &jsonObject) {
            DoSerialize<0, T>(object, jsonObject);
        }

        /**
         * added to remove compile error.
         * when setters length is 0, it will try to compile with iteration = 0
         */
        template<std::size_t iteration, class T>
        typename std::enable_if<(iteration == 0), void>::type
        static Serialize(const T &, nlohmann::json &) {
        }


        //////////////////////////////// Enum ///////////////////
        template<class T>
        typename std::enable_if<Is_Enum<T>::Value && !Is_Pointer<T>::Value, nlohmann::json>::type
        static ToJsonObject(const T &object) {
            return nlohmann::json(static_cast<int>(object));
        }

        //////////////////////////////// Bool, Integer, Decimal ///////////////////
        template<class T>
        typename std::enable_if<
                (Is_Number<T>::Value || Is_Bool<T>::Value) && !Is_Pointer<T>::Value, nlohmann::json>::type
        static ToJsonObject(const T &object) {
            return nlohmann::json(object);
        }

        ///////////////// char ///////////////////////////////////
        // TODO: why it is needed? it should be covered by Is_Int8
        template<class T>
        typename std::enable_if<Is_Char<T>::Value && !Is_Pointer<T>::Value, nlohmann::json>::type
        static ToJsonObject(const T &object) {
            return nlohmann::json(static_cast<int8_t> (object));
        }

        /////////////////////// std::string //////////////////////////////////////
        template<class T>
        typename std::enable_if<Is_String<T>::Value && !Is_Pointer<T>::Value, nlohmann::json>::type
        static ToJsonObject(const T &object) {
            return nlohmann::json(std::string(object));
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
                return ToJsonObject(*sharedObject);
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

        //////////////////  custom object ////////////////////////
        template<class T>
        typename std::enable_if<Is_Class<T>::Value && !Is_Pointer<T>::Value, nlohmann::json>::type
        static ToJsonObject(const T &object) {
            nlohmann::json jsonObject = nlohmann::json::object();

            using ObjectType = typename Remove_CVRP<T>::Type;
            auto getters = ObjectType::getters;
            const auto length = std::tuple_size<decltype(getters)>::value;
            if (length > 0) {
                Serialize<length>(object, jsonObject);
            }
            return jsonObject;
        }

        //////////////////  std::vector ////////////////////////
        template<class T>
        typename std::enable_if<Is_Vector<T>::Value && !Is_Pointer<T>::Value, nlohmann::json>::type
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
        typename std::enable_if<Is_Array<T>::Value, nlohmann::json>::type
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
        typename std::enable_if<Is_Pointer<T>::Value && !Is_Array<T>::Value, nlohmann::json>::type
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
        typename std::enable_if<Is_Map<T>::Value && !Is_Pointer<T>::Value, nlohmann::json>::type
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
        typename std::enable_if<Is_Pointer<T>::Value && !Is_Array<T>::Value, nlohmann::json>::type
        static ToJsonObject(const T &object) {
            if (object) {
                return ToJsonObject(*object);
            }
            return {};
        }
    }
}

#endif //OPEN_JSON_SERIALIZER_H
