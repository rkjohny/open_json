#ifndef OPEN_JSON_SERIALIZER_H
#define OPEN_JSON_SERIALIZER_H

#include <iostream>
#include "CommonDef.h"
#include "TypeTraits.h"
#include "nlohmann/json.hpp"
#include "boost/optional.hpp"
#include "string"


namespace open_json {
    namespace  serializer {

        template<class T>
        static void GetData(const std::unique_ptr<T> &object, nlohmann::json &jsonObject, const char *name) {
            if (object) {
                jsonObject[std::string(name)] = ToJson(object);
            } else {
                //value is null and will be ignored.
            }
        }

        template<class T>
        static void GetData(const std::shared_ptr<T> &object, nlohmann::json &jsonObject, const char *name) {
            if (object) {
                jsonObject[std::string(name)] = ToJson(object);
            } else {
                //value is null and will be ignored.
            }
        }

        template<class T>
        static void GetData(const std::weak_ptr<T> &object, nlohmann::json &jsonObject, const char *name) {
            std::shared_ptr<T> shareObject = object.lock();
            if (shareObject) {
                jsonObject[std::string(name)] = ToJson(shareObject);
            } else {
                //value is null and will be ignored.
            }
        }

        template<class T>
        static void GetData(const boost::optional<T> &object, nlohmann::json &jsonObject, const char *name) {
            if (object) {
                jsonObject[std::string(name)] = ToJson(object);
            } else {
                //value is null and will be ignored.
            }
        }
        
        template<class T>
        static void GetData(const T &object, nlohmann::json &jsonObject, const char *name) {
            jsonObject[std::string(name)] = ToJson(object);
        }

        template<class T>
        static void GetData(const T *object, nlohmann::json &jsonObject, const char *name) {
            if (object) {
                jsonObject[std::string(name)] = ToJson(object);
            } else {
                //value is null and will be ignored.
            }
        }

        template<class T>
        static void GetData(const T *const *object, nlohmann::json &jsonObject, const char *name) {
            if (object && *object) {
                jsonObject[std::string(name)] = ToJson(object);
            } else {
                //value is null and will be ignored.
            }
        }

        template<std::size_t iteration, class T>
        static void DoSerialize(T *object, nlohmann::json &jsonObject) {
            using ObjectType = typename Remove_CVRP<T>::Type;
            constexpr auto getter = std::get<iteration>(ObjectType::getters);
            auto getterName = getter.name;
            //using GetterReturnType = typename decltype( getter )::Type;
            auto method = getter.fp;

            const auto &getterReturnedObject = (object->*method)();

            GetData(getterReturnedObject, jsonObject, getterName);
        }

        template<std::size_t iteration, class T>
        typename std::enable_if<(iteration > 1), void>::type
        static Serialize(T *object, nlohmann::json &jsonObject) {
            DoSerialize<iteration - 1, T>(object, jsonObject);

            Serialize<iteration - 1, T>(object, jsonObject);
        }

        template<std::size_t iteration, class T>
        typename std::enable_if<(iteration == 1), void>::type
        static Serialize(T *object, nlohmann::json &jsonObject) {
            DoSerialize<0, T>(object, jsonObject);
        }

        /**
         * added to remove compile error.
         * when setters length is 0, it will try to compile with iteration = 0
         */
        template<std::size_t iteration, class T>
        typename std::enable_if<(iteration == 0), void>::type
        static Serialize(T *, nlohmann::json &) {
        }

        template<class T>
        typename std::enable_if<std::is_array<T>::value, nlohmann::json>::type
        static ToJson(const T &&) {
            static_assert(true, "Serialization of array is not supported.");
        }


        //////////////////////////////// Enum ///////////////////

        template<class T>
        typename std::enable_if<std::is_enum<T>::value, nlohmann::json>::type
        static ToJson(const T &&object) {
            return nlohmann::json(static_cast<int>(object));
        }

        template<class T>
        typename std::enable_if<std::is_enum<T>::value, nlohmann::json>::type
        static ToJson(const T &object) {
            return nlohmann::json(static_cast<int>(object));
        }

        template<class T>
        typename std::enable_if<std::is_enum<T>::value, nlohmann::json>::type
        static ToJson(const T *object) {
            return nlohmann::json(static_cast<int>(*object));
        }

        template<class T>
        typename std::enable_if<std::is_enum<T>::value, nlohmann::json>::type
        static ToJson(const T *const *object) {
            return nlohmann::json(static_cast<int>(**object));
        }

        //////////////////////////////// bool ///////////////////

        template<class T>
        typename std::enable_if<Is_Bool<T>::Value, nlohmann::json>::type
        static ToJson(const T &&object) {
            return nlohmann::json(object);
        }

        template<class T>
        typename std::enable_if<Is_Bool<T>::Value, nlohmann::json>::type
        static ToJson(const T &object) {
            return nlohmann::json(object);
        }

        template<class T>
        typename std::enable_if<Is_Bool<T>::Value, nlohmann::json>::type
        static ToJson(const T *object) {
            return nlohmann::json(*object);
        }

        template<class T>
        typename std::enable_if<Is_Bool<T>::Value, nlohmann::json>::type
        static ToJson(const T *const *object) {
            return nlohmann::json(**object);
        }

        ///////////////// char ///////////////////////////////////

        template<class T>
        typename std::enable_if<Is_Char<T>::Value, nlohmann::json>::type
        static ToJson(const T &&object) {
            return nlohmann::json(static_cast<int32_t> (object));
        }

        template<class T>
        typename std::enable_if<Is_Char<T>::Value, nlohmann::json>::type
        static ToJson(const T &object) {
            return nlohmann::json(static_cast<int32_t> (object));
        }

        template<class T>
        typename std::enable_if<Is_Char<T>::Value, nlohmann::json>::type
        static ToJson(const T *object) {
            std::string str = std::string(object);
            return nlohmann::json(std::move(str));
        }

        template<class T>
        typename std::enable_if<Is_Char<T>::Value, nlohmann::json>::type
        static ToJson(const T *const *object) {
            std::string str = std::string(*object);
            return nlohmann::json(std::move(str));
        }

        ///////////////// integer ///////////////////////////////////

        template<class T>
        typename std::enable_if<Is_Integer<T>::Value, nlohmann::json>::type
        static ToJson(const T &&object) {
            return nlohmann::json(object);
        }

        template<class T>
        typename std::enable_if<Is_Integer<T>::Value, nlohmann::json>::type
        static ToJson(const T &object) {
            return nlohmann::json(object);
        }

        template<class T>
        typename std::enable_if<Is_Integer<T>::Value, nlohmann::json>::type
        static ToJson(const T *object) {
            return nlohmann::json(*object);
        }

        template<class T>
        typename std::enable_if<Is_Integer<T>::Value, nlohmann::json>::type
        static ToJson(const T *const *object) {
            return nlohmann::json(**object);
        }

        /////////////////////   Decimal   ///////////////////////////////////

        template<class T>
        typename std::enable_if<Is_Decimal<T>::Value, nlohmann::json>::type
        static ToJson(const T &&object) {
            return nlohmann::json(static_cast<double_t> (object));
        }

        template<class T>
        typename std::enable_if<Is_Decimal<T>::Value, nlohmann::json>::type
        static ToJson(const T &object) {
            return nlohmann::json(static_cast<double_t> (object));
        }

        template<class T>
        typename std::enable_if<Is_Decimal<T>::Value, nlohmann::json>::type
        static ToJson(const T *object) {
            return nlohmann::json(static_cast<double_t> (*object));
        }

        template<class T>
        typename std::enable_if<Is_Decimal<T>::Value, nlohmann::json>::type
        static ToJson(const T *const *object) {
            return nlohmann::json(static_cast<double_t> (**object));
        }

        /////////////////////// std::string //////////////////////////////////////

        template<class T>
        typename std::enable_if<Is_String<T>::Value, nlohmann::json>::type
        static ToJson(T &&object) {
            return nlohmann::json(std::string(object));
        }

        template<class T>
        typename std::enable_if<Is_String<T>::Value, nlohmann::json>::type
        static ToJson(const T &object) {
            return nlohmann::json(std::string(object));
        }

        template<class T>
        typename std::enable_if<Is_String<T>::Value, nlohmann::json>::type
        static ToJson(const T *object) {
            std::string str(*object);
            return nlohmann::json(std::move(str));
        }

        template<class T>
        typename std::enable_if<Is_String<T>::Value, nlohmann::json>::type
        static ToJson(const T *const *object) {
            std::string str(**object);
            return nlohmann::json(std::move(str));
        }

        //////////////////  custom object ////////////////////////

        template<class T>
        typename std::enable_if<Is_Class<T>::Value, nlohmann::json>::type
        static ToJson(const T &&object) {
            nlohmann::json jsonObject = nlohmann::json::object();

            using ObjectType = typename Remove_CVRP<T>::Type;
            auto getters = ObjectType::getters;
            const auto length = std::tuple_size<decltype(getters)>::value;
            if (length > 0) {
                Serialize<length>(&object, jsonObject);
            }
            return jsonObject;
        }

        template<class T>
        typename std::enable_if<Is_Class<T>::Value, nlohmann::json>::type
        static ToJson(const T &object) {
            nlohmann::json jsonObject = nlohmann::json::object();

            using ObjectType = typename Remove_CVRP<T>::Type;
            auto getters = ObjectType::getters;
            const auto length = std::tuple_size<decltype(getters)>::value;
            if (length > 0) {
                Serialize<length>(&object, jsonObject);
            }
            return jsonObject;
        }

        template<class T>
        typename std::enable_if<Is_Class<T>::Value, nlohmann::json>::type
        static ToJson(const T *object) {
            return ToJson(*object);
        }

        template<class T>
        typename std::enable_if<Is_Class<T>::Value, nlohmann::json>::type
        static ToJson(const T *const *object) {
            return ToJson(**object);
        }


        //////////////////  std::vector ////////////////////////

        template<class T>
        typename std::enable_if<Is_Vector<T>::Value, nlohmann::json>::type
        static ToJson(const T &&object) {
            std::size_t length = object.size();
            nlohmann::json jsonObject = nlohmann::json::array();
            size_t index = 0;

            if (length > 0) {
                for (auto &arrValue : object) {
                    jsonObject.push_back(ToJson(arrValue));
                    //jsonObject[index++] = ToJson(arrValue);
                }
            }
            return jsonObject;
        }

        template<class T>
        typename std::enable_if<Is_Vector<T>::Value, nlohmann::json>::type
        static ToJson(const T &object) {
            std::size_t length = object.size();
            nlohmann::json jsonObject = nlohmann::json::array();
            size_t index = 0;

            if (length > 0) {
                for (auto &arrValue : object) {
                    jsonObject[index++] = ToJson(arrValue);
                }
            }
            return jsonObject;
        }

        template<class T>
        typename std::enable_if<Is_Vector<T>::Value, nlohmann::json>::type
        static ToJson(const T *object) {
            return ToJson(*object);
        }

        template<class T>
        typename std::enable_if<Is_Vector<T>::Value, nlohmann::json>::type
        static ToJson(const T *const *object) {
            return ToJson(**object);
        }

        ///////////////////// std::unique_ptr<T> ///////////////////////////////////
        template<class T>
        static nlohmann::json ToJson(const std::unique_ptr<T> &&object) {
            if (object) {
                return ToJson(*object);
            }
            return nlohmann::json();
        }

        template<class T>
        static nlohmann::json ToJson(const std::unique_ptr<T> &object) {
            if (object) {
                return ToJson(*object);
            }
            return nlohmann::json();
        }

        ///////////////////// std::shared_ptr<T> ///////////////////////////////////
        template<class T>
        static nlohmann::json ToJson(const std::shared_ptr<T> &&object) {
            if (object) {
                return ToJson(*object);
            }
            return nlohmann::json();
        }

        template<class T>
        static nlohmann::json ToJson(const std::shared_ptr<T> &object) {
            if (object) {
                return ToJson(*object);
            }
            return nlohmann::json();
        }


        ///////////////////// std::weak_ptr<T> ///////////////////////////////////
        template<class T>
        static nlohmann::json ToJson(const std::weak_ptr<T> &&object) {
            auto sharedObject = object.lock();
            if (sharedObject) {
                return ToJson(*sharedObject);
            }
            return nlohmann::json();
        }

        template<class T>
        static nlohmann::json ToJson(const std::weak_ptr<T> &object) {
            auto sharedObject = object.lock();
            if (sharedObject) {
                return ToJson(*sharedObject);
            }
            return nlohmann::json();
        }

        ///////////////////// boost::optional<T> ///////////////////////////////////
        template<class T>
        static nlohmann::json ToJson(const boost::optional<T> &&object) {
            if (object) {
                return ToJson(*object);
            }
            return nlohmann::json();
        }

        template<class T>
        static nlohmann::json ToJson(const boost::optional<T> &object) {
            if (object) {
                return ToJson(*object);
            }
            return nlohmann::json();
        }

    }
}


#endif //OPEN_JSON_SERIALIZER_H
