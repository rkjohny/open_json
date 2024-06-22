#ifndef OPEN_JSON_DESERIALIZER_H
#define OPEN_JSON_DESERIALIZER_H

#include "CommonDef.h"
#include <nlohmann/json.hpp>
#include "boost/optional.hpp"
#include "TypeTraits.h"


namespace open_json {

    class Deserializer final {
    private:
        MAKE_STATIC(Deserializer);

        /**
         * calls the setter method with type = boost::optional<T>
         */
        template<class T, class B, class ArgT>
        static void
        SetData(T *object, void (B::*SetterPtr)(const boost::optional<ArgT> &), const nlohmann::json &jsonObject) {
            using Type = typename Remove_CVR<ArgT>::Type;

            boost::optional<Type> var;
            FromJson(var, jsonObject);
            (object->*SetterPtr)(var);
        }

        /**
         * calls the setter method with type = std::unique_ptr<T>
         */
        template<class T, class B, class ArgT>
        static void
        SetData(T *object, void (B::*SetterPtr)(const std::unique_ptr<ArgT> &&), const nlohmann::json &jsonObject) {
            using Type = typename Remove_CVR<ArgT>::Type;

            std::unique_ptr<Type> var;
            FromJson(var, jsonObject);
            (object->*SetterPtr)(std::move(var));
        }

        /**
         * calls the setter method with type = std::shared_ptr<T>
         */
        template<class T, class B, class ArgT>
        static void
        SetData(T *object, void (B::*SetterPtr)(const std::shared_ptr<ArgT> &), const nlohmann::json &jsonObject) {
            using Type = typename Remove_CVR<ArgT>::Type;

            std::shared_ptr<Type> var;
            FromJson(var, jsonObject);
            (object->*SetterPtr)(var);
        }

        /**
         * calls the setter method with type = std::weak_ptr<T>
         */
        template<class T, class B, class ArgT>
        static void
        SetData(T *object, void (B::*SetterPtr)(const std::weak_ptr<ArgT> &), const nlohmann::json &jsonObject) {
            using Type = typename Remove_CVR<ArgT>::Type;

            std::weak_ptr<Type> var;
            FromJson(var, jsonObject);
            (object->*SetterPtr)(var);
        }

        /**
         * calls the setter method with rvalue reference type argument
         */
        template<class T, class B, class ArgT>
        static void SetData(T *object, void ( B::*SetterPtr)(ArgT &&), const nlohmann::json &jsonObject) {
            using Type = typename Remove_CVR<ArgT>::Type;

            Type var;
            FromJson(var, jsonObject);
            (object->*SetterPtr)(std::move(var));
        }


        /**
         * calls the setter method with rvalue reference type argument
         */
        template<class T, class B, class ArgT>
        static void SetData(T *object, void ( B::*SetterPtr)(const ArgT &&), const nlohmann::json &jsonObject) {
            using Type = typename Remove_CVR<ArgT>::Type;

            Type var;
            FromJson(var, jsonObject);
            (object->*SetterPtr)(std::move(var));
        }

        /**
         * calls the setter method with value type argument
         */
        template<class T, class B, class ArgT>
        static void SetData(T *object, void ( B::*SetterPtr)(const ArgT), const nlohmann::json &jsonObject) {
            using Type = typename Remove_CVR<ArgT>::Type;

            Type var;
            FromJson(var, jsonObject);
            (object->*SetterPtr)(var);
        }

        /**
         * calls the setter method with reference type argument
         */
        template<class T, class B, class ArgT>
        static void SetData(T *object, void ( B::*SetterPtr)(ArgT &), const nlohmann::json &jsonObject) {
            using Type = typename Remove_CVR<ArgT>::Type;

            Type var;
            FromJson(var, jsonObject);
            (object->*SetterPtr)(var);
        }

        /**
         * calls the setter method with constant reference type argument
         */
        template<class T, class B, class ArgT>
        static void SetData(T *object, void ( B::*SetterPtr)(const ArgT &), const nlohmann::json &jsonObject) {
            using Type = typename Remove_CVR<ArgT>::Type;

            Type var;
            FromJson(var, jsonObject);
            (object->*SetterPtr)(var);
        }

        /**
         * special handling for char array.
         * No other array type is supported.
         */
        template<class T, class B>
        static void SetData(T *object, void ( B::*SetterPtr)(char *), const nlohmann::json &jsonObject) {
            char *var;
            FromJson(&var, jsonObject);
            (object->*SetterPtr)(var);
        }

        /**
         * special handling for char array.
         * No other array type is supported.
         */
        template<class T, class B>
        static void SetData(T *object, void ( B::*SetterPtr)(const char *), const nlohmann::json &jsonObject) {
            char *var;
            FromJson(&var, jsonObject);
            (object->*SetterPtr)(var);
        }

        /**
         * calls the setter method with pointer type argument
         */
        template<class T, class B, class ArgT>
        static void SetData(T *object, void ( B::*SetterPtr)(ArgT *), const nlohmann::json &jsonObject) {
            using Type = typename Remove_CVR<ArgT>::Type;

            Type *var = new Type();
            FromJson(var, jsonObject);
            (object->*SetterPtr)(var);
        }

        /**
         * calls the setter method with constant pointer type argument
         */
        template<class T, class B, class ArgT>
        static void SetData(T *object, void ( B::*SetterPtr)(const ArgT *), const nlohmann::json &jsonObject) {
            using Type = typename Remove_CVR<ArgT>::Type;

            Type *var = new Type();
            FromJson(var, jsonObject);
            (object->*SetterPtr)(var);
        }

        /**
         * calls the setter method with constant pointer type argument
         */
        template<class T, class B, class ArgT>
        static void SetData(T *object, void ( B::*SetterPtr)(ArgT **), const nlohmann::json &jsonObject) {
            using Type = typename Remove_CVR<ArgT>::Type;

            Type **var = new Type *();
            FromJson(var, jsonObject);
            (object->*SetterPtr)(var);
        }

        /**
         * calls the setter method with constant pointer type argument
         * TODO: make first level const, i.e const ArgT* const*
         */
        template<class T, class B, class ArgT>
        static void SetData(T *object, void ( B::*SetterPtr)(const ArgT *const *), const nlohmann::json &jsonObject) {
            using Type = typename Remove_CVR<ArgT>::Type;

            Type **var = new Type *();
            FromJson(var, jsonObject);
            (object->*SetterPtr)(var);
        }

        /**
         * get the setter at tuple position referenced by iteration.
         * call the setter to set the value to the object's property.
         */
        template<size_t iteration, class T>
        static void DoDeserialize(T *object, const nlohmann::json &jsonObject) {
            using BaseObjectType = typename Remove_CVR<T>::Type;
            auto setters = BaseObjectType::setters;
            auto setter = std::get<iteration>(setters);

            using DerivedObjectType = typename Remove_CVR<typename decltype(setter)::Class>::Type;
            //using ArgT = typename decltype( setter ) ::Type;
            auto name = setter.name;
            auto fp = setter.fp;

            bool found = false;

            if (jsonObject.template contains<nlohmann::json>(name)) {
                const auto &jval = jsonObject.template at<nlohmann::json>(name);

                if (!jval.is_null()) {
                    found = true;
                    // BaseObjectType and DerivedObjectType can be same type
                    SetData<BaseObjectType, DerivedObjectType>(object, fp, jval);
                }
            }

            if (!found) {
                //value is null and will be ignored.
            }
        }

        /**
         * execute the setter at position greater than 0
         */
        template<size_t iteration, class T>
        typename std::enable_if<(iteration > 1), void>::type
        static Deserialize(T *object, const nlohmann::json &jsonObject) {
            DoDeserialize<iteration - 1>(object, jsonObject);

            Deserialize<iteration - 1>(object, jsonObject);
        }

        /**
         * execute the setter at position 0
         */
        template<size_t iteration, class T>
        typename std::enable_if<(iteration == 1), void>::type
        static Deserialize(T *object, const nlohmann::json &jsonObject) {
            DoDeserialize<0>(object, jsonObject);
        }

        /**
         * added to remove compile error.
         * when setters length is 0, it will try to compile with iteration = 0
         */
        template<size_t iteration, class T>
        typename std::enable_if<(iteration == 0), void>::type
        static Deserialize(T *, const nlohmann::json &) {
        }

    public:

        /**
         * object is constant reference, return error
         */
        template<class T>
        typename std::enable_if<std::is_const<T>::value, void>::type
        FromJson(T &) {
            static_assert(true, "object cannot be constant");
        }

        /**
         * object is constant pointer, return error
         */
        template<class T>
        typename std::enable_if<std::is_const<T>::value, void>::type
        FromJson(T *) {
            static_assert(true, "object pointer cannot be constant");
        }

        /**
         * object is an array, return error
         */
        template<class T>
        typename std::enable_if<std::is_array<T>::value, void>::type
        FromJson(T &) {
            static_assert(true, "Deserialization of array is not supported.");
        }


        /********************************************************************************
         * object type: enum
         ********************************************************************************/
        template<class T>
        typename std::enable_if<std::is_enum<T>::value, void>::type
        static FromJson(T &object, const nlohmann::json &jsonObject) {
            object = static_cast<typename Remove_CVR<T>::Type>(jsonObject.template get<int32_t>());
        }

        /********************************************************************************
         * object type: enum*
         ********************************************************************************/
        template<class T>
        typename std::enable_if<std::is_enum<T>::value, void>::type
        static FromJson(T *object, const nlohmann::json &jsonObject) {
            *object = static_cast<typename Remove_CVR<T>::Type>(jsonObject.template get<int32_t>());
        }

        /********************************************************************************
         * object type: enum**
         ********************************************************************************/
        template<class T>
        typename std::enable_if<std::is_enum<T>::value, void>::type
        static FromJson(T **object, const nlohmann::json &jsonObject) {
            using Type = typename Remove_CVR<T>::Type;
            *object = new Type(static_cast<Type>(jsonObject.template get<int32_t>()));
        }

        /*********************************************************************************
         * object type: bool
         *********************************************************************************/
        template<class T>
        typename std::enable_if<Is_Bool<T>::Value, void>::type
        static FromJson(T &object, const nlohmann::json &jsonObject) {
            object = static_cast<bool>(jsonObject.template get<bool>());
        }

        /*********************************************************************************
         * object type: bool*
         * object should be allocated;
         *
         * example of usages:
         *
         *      nlohmann::json jsonObject = nlohmann::json(true);
         *
         * example1:
         *      bool bvalue;
         *      FromJson(&bvalue, jsonObject);
         *
         * example2:
         *      bool *p = new bool();
         *      Json::FromJson(p, jsonObject); // p will NOT be allocated
         *      delete p;
         *********************************************************************************/
        template<class T>
        typename std::enable_if<Is_Bool<T>::Value, void>::type
        static FromJson(T *object, const nlohmann::json &jsonObject) {
            *object = static_cast<bool>(jsonObject.template get<bool>());
        }

        /*********************************************************************************
         * object type: bool**
         * object should NOT be allocated;
         *
         * example of usages:
         *
         *      nlohmann::json jsonObject = nlohmann::json(true);
         *
         * example1:
         *      bool *p = nullptr;
         *      FromJson(&p, jsonObject); // *p will be allocated
         *      if (p)
         *          delete p;
         *
         * example2:
         *      bool **p = new bool*();
         *      FromJson(p, jsonObject); // *p will be allocated
         *      if (*p)
         *          delete *p;
         *      if (p)
         *          delete p;
         *********************************************************************************/
        template<class T>
        typename std::enable_if<Is_Bool<T>::Value, void>::type
        static FromJson(T **object, const nlohmann::json &jsonObject) {
            *object = new bool(static_cast<bool>(jsonObject.template get<bool>()));
        }

        /*********************************************************************************
         * object type: char
         *********************************************************************************/
        template<class T>
        typename std::enable_if<Is_Char<T>::Value, void>::type
        static FromJson(T &object, const nlohmann::json &jsonObject) {
            object = static_cast<char>(jsonObject.template get<char>());
        }

        /**********************************************************************************
         * type: char*
         *
         * see usges of for bool*
         ***********************************************************************************/
        template<class T>
        typename std::enable_if<Is_Char<T>::Value, void>::type
        static FromJson(T *object, const nlohmann::json &jsonObject) {
            const std::string str = jsonObject.template get<std::string>();
            strcpy(object, str.c_str());
        }

        /**********************************************************************************
         * type: char**
         *
         * see usages for bool**
         *
         ***********************************************************************************/
        template<class T>
        typename std::enable_if<Is_Char<T>::Value, void>::type
        static FromJson(T **object, const nlohmann::json &jsonObject) {
            const std::string str = jsonObject.template get<std::string>();
            *object = new char[str.length() + 1];
            strcpy(*object, str.c_str());
        }

        /***********************************************************************************
         * object type: int8_t, int16_t, int32_t
         ***********************************************************************************/
        template<class T>
        typename std::enable_if<Is_Int8<T>::Value || Is_Int16<T>::Value || Is_Int32<T>::Value, void>::type
        static FromJson(T &object, const nlohmann::json &jsonObject) {
            object = static_cast<int32_t>(jsonObject.template get<int32_t>());
        }

        /***********************************************************************************
         * object type: int8_t*, int16_t*, int32_t*
         ***********************************************************************************/
        template<class T>
        typename std::enable_if<Is_Int8<T>::Value || Is_Int16<T>::Value || Is_Int32<T>::Value, void>::type
        static FromJson(T *object, const nlohmann::json &jsonObject) {
            *object = static_cast<int32_t>(jsonObject.template get<int32_t>());
        }

        /***********************************************************************************
         * object type: int8_t**, int16_t**, int32_t**
         ***********************************************************************************/
        template<class T>
        typename std::enable_if<Is_Int8<T>::Value || Is_Int16<T>::Value || Is_Int32<T>::Value, void>::type
        static FromJson(T **object, const nlohmann::json &jsonObject) {
            *object = new int32_t(static_cast<int32_t>(jsonObject.template get<int32_t>()));
        }

        /***********************************************************************************
         * object type: uint8_t, uint16_t, uint32_t
         ***********************************************************************************/
        template<class T>
        typename std::enable_if<Is_UInt8<T>::Value || Is_UInt16<T>::Value || Is_UInt32<T>::Value, void>::type
        static FromJson(T &object, const nlohmann::json &jsonObject) {
            object = static_cast<uint32_t>(jsonObject.template get<uint32_t>());
        }

        /***********************************************************************************
         * object type: uint8_t*, uint16_t*, uint32_t*
         ***********************************************************************************/
        template<class T>
        typename std::enable_if<Is_UInt8<T>::Value || Is_UInt16<T>::Value || Is_UInt32<T>::Value, void>::type
        static FromJson(T *object, const nlohmann::json &jsonObject) {
            *object = static_cast<uint32_t>(jsonObject.template get<uint32_t>());
        }

        /***********************************************************************************
         * object type: uint8_t**, uint16_t**, uint32_t**
         ***********************************************************************************/
        template<class T>
        typename std::enable_if<Is_UInt8<T>::Value || Is_UInt16<T>::Value || Is_UInt32<T>::Value, void>::type
        static FromJson(T **object, const nlohmann::json &jsonObject) {
            *object = new uint32_t(static_cast<T>(jsonObject.template get<uint32_t>()));
        }

        /***********************************************************************************
         * object type: int64_t
         ***********************************************************************************/
        template<class T>
        typename std::enable_if<Is_Int64<T>::Value, void>::type
        static FromJson(T &object, const nlohmann::json &jsonObject) {
            object = static_cast<int64_t>(jsonObject.template get<int64_t>());
        }

        /***********************************************************************************
         * object type: int64_t*
         ***********************************************************************************/
        template<class T>
        typename std::enable_if<Is_Int64<T>::Value, void>::type
        static FromJson(T *object, const nlohmann::json &jsonObject) {
            *object = static_cast<int64_t>(jsonObject.template get<int64_t>());
        }

        /***********************************************************************************
         * object type: int64_t**
         ***********************************************************************************/
        template<class T>
        typename std::enable_if<Is_Int64<T>::Value, void>::type
        static FromJson(T **object, const nlohmann::json &jsonObject) {
            *object = new int64_t(static_cast<int64_t>(jsonObject.template get<int64_t>()));
        }

        /***********************************************************************************
         * object type: uint64_t
         ***********************************************************************************/
        template<class T>
        typename std::enable_if<Is_UInt64<T>::Value, void>::type
        static FromJson(T &object, const nlohmann::json &jsonObject) {
            object = static_cast<uint64_t>(jsonObject.template get<uint64_t>());
        }

        /***********************************************************************************
         * object type: uint64_t*
         ***********************************************************************************/
        template<class T>
        typename std::enable_if<Is_UInt64<T>::Value, void>::type
        static FromJson(T *object, const nlohmann::json &jsonObject) {
            *object = static_cast<uint64_t>(jsonObject.template get<uint64_t>());
        }

        /***********************************************************************************
         * object type: uint64_t**
         ***********************************************************************************/
        template<class T>
        typename std::enable_if<Is_UInt64<T>::Value, void>::type
        static FromJson(T **object, const nlohmann::json &jsonObject) {
            *object = new uint64_t(static_cast<uint64_t>(jsonObject.template get<uint64_t>()));
        }

        /***********************************************************************************
         * object type: float, double, long double
         ***********************************************************************************/
        template<class T>
        typename std::enable_if<Is_Decimal<T>::Value, void>::type
        static FromJson(T &object, const nlohmann::json &jsonObject) {
            object = static_cast<double_t>(jsonObject.template get<double_t>());
        }

        /***********************************************************************************
         * object type: float*, double*, long double*
         ***********************************************************************************/
        template<class T>
        typename std::enable_if<Is_Decimal<T>::Value, void>::type
        static FromJson(T *object, const nlohmann::json &jsonObject) {
            *object = static_cast<double_t>(jsonObject.template get<double_t>());
        }

        /***********************************************************************************
         * object type: float**, double**, long double**
         ***********************************************************************************/
        template<class T>
        typename std::enable_if<Is_Decimal<T>::Value, void>::type
        static FromJson(T **object, const nlohmann::json &jsonObject) {
            *object = new double_t(static_cast<double_t>(jsonObject.template get<double_t>()));
        }

        /***********************************************************************************
         * object type: std::string
         ***********************************************************************************/
        template<class T>
        typename std::enable_if<Is_String<T>::Value, void>::type
        static FromJson(T &object, const nlohmann::json &jsonObject) {
            object = jsonObject.template get<std::string>();
        }

        /***********************************************************************************
         * object type: std::string*
         ***********************************************************************************/
        template<class T>
        typename std::enable_if<Is_String<T>::Value, void>::type
        static FromJson(T *object, const nlohmann::json &jsonObject) {
            *object = jsonObject.template get<std::string>();
        }

        /***********************************************************************************
         * object type: std::string**
         ***********************************************************************************/
        template<class T>
        typename std::enable_if<Is_String<T>::Value, void>::type
        static FromJson(T **object, const nlohmann::json &jsonObject) {
            *object = new std::string(jsonObject.template get<std::string>());
        }


        /*///////////////////////////  OBJECT ////////////////////////////////////////////*/

        /***********************************************************************************
         * object type: userdefined class{}*
         ***********************************************************************************/
        template<class T>
        typename std::enable_if<Is_Class<T>::Value, void>::type
        static FromJson(T *object, const nlohmann::json &jsonObject) {
            using Type = typename Remove_CVR<T>::Type;
            auto setters = Type::setters;
            const auto length = std::tuple_size<decltype(setters)>::value;
            if (length > 0) {
                Deserialize<length>(object, jsonObject);
            }
        }

        /***********************************************************************************
         * object type: user defined class{}&
         ***********************************************************************************/
        template<class T>
        typename std::enable_if<Is_Class<T>::Value, void>::type
        static FromJson(T &object, const nlohmann::json &jsonObject) {
            FromJson(&object, jsonObject);
        }

        /***********************************************************************************
         * object type: user defined class{}**
         ***********************************************************************************/
        template<class T>
        typename std::enable_if<Is_Class<T>::Value, void>::type
        static FromJson(T **object, const nlohmann::json &jsonObject) {
            using Type = typename Remove_CVR<T>::Type;
            *object = new Type();

            FromJson(*object, jsonObject);
        }


        /*///////////////////////////  VECTOR ////////////////////////////////////////////*/

        /***********************************************************************************
         * special handling for vector of char*
         ***********************************************************************************/
        static void FromJson(std::vector<char *> *object, const nlohmann::json &jsonObject) {
            for (const auto &arrItem: jsonObject) {
                //char *var = new char[arrItem.size()];
                char *var;
                FromJson(&var, arrItem);
                object->push_back(var);
            }
        }

        static void FromJson(std::vector<const char *> *object, const nlohmann::json &jsonObject) {
            for (const auto &arrItem: jsonObject) {
                //char *var = new char[arrItem.size()];
                char *var;
                FromJson(&var, arrItem);
                object->push_back(var);
            }
        }

        /***********************************************************************************
         * object type: std::vector<T*>*
         ***********************************************************************************/
        template<class T>
        static void FromJson(std::vector<T *> *object, const nlohmann::json &jsonObject) {
            using Type = typename Remove_CVR<T>::Type;

            for (const auto &arrItem: jsonObject) {
                Type *var = new Type();
                FromJson(var, arrItem);
                object->push_back(var);
            }
        }

        /***********************************************************************************
         * object type: std::vector<T*>&
         ***********************************************************************************/
        template<class T>
        static void FromJson(std::vector<T *> &object, const nlohmann::json &jsonObject) {
            FromJson(&object, jsonObject);
        }

        /***********************************************************************************
         * object type: std::vector<T*>**
         ***********************************************************************************/
        template<class T>
        static void FromJson(std::vector<T *> **object, const nlohmann::json &jsonObject) {
            //using Type = typename Remove_CVR<T>::Type;
            *object = new std::vector<T *>();

            FromJson(*object, jsonObject);
        }

        /***********************************************************************************
         * object type: std::vector<T>*
         ***********************************************************************************/
        template<class T>
        static void FromJson(std::vector<T> *object, const nlohmann::json &jsonObject) {
            using Type = typename Remove_CVR<T>::Type;

            for (const auto &arrItem: jsonObject) {
                Type var = Type();
                FromJson(var, arrItem);
                object->push_back(var);
            }
        }

        /***********************************************************************************
         * object type: std::vector<T>&
         ***********************************************************************************/
        template<class T>
        static void FromJson(std::vector<T> &object, const nlohmann::json &jsonObject) {
            FromJson(&object, jsonObject);
        }

        /***********************************************************************************
         * object type: std::vector<T>**
         ***********************************************************************************/
        template<class T>
        static void FromJson(std::vector<T> **object, const nlohmann::json &jsonObject) {
            //using Type = typename Remove_CVR<T>::Type;
            *object = new std::vector<T>();

            FromJson(*object, jsonObject);
        }


        /***********************************************************************************
        * object type: std::unique_ptr<T>
        ***********************************************************************************/
        template<class T>
        static void FromJson(std::unique_ptr<T> &object, const nlohmann::json &jsonObject) {
            using Type = typename Remove_CVR<T>::Type;
            std::unique_ptr<Type> var = std::make_unique<Type>();
            FromJson(var.get(), jsonObject);
            object = std::move(var);
        }

        /***********************************************************************************
        * object type: std::shared_ptr<T>
        ***********************************************************************************/
        template<class T>
        static void FromJson(std::shared_ptr<T> &object, const nlohmann::json &jsonObject) {
            using Type = typename Remove_CVR<T>::Type;
            std::shared_ptr<Type> var = std::make_shared<Type>();
            FromJson(var.get(), jsonObject);
            object = std::move(var);
        }

        /***********************************************************************************
        * object type: std::weak_ptr<T>
        ***********************************************************************************/
        template<class T>
        static void FromJson(std::weak_ptr<T> &object, const nlohmann::json &jsonObject) {
            using Type = typename Remove_CVR<T>::Type;
            std::shared_ptr<Type> var = std::make_shared<Type>();
            FromJson(var.get(), jsonObject);
            object = var;
        }

        /***********************************************************************************
        * object type: boost::optional<T>
        ***********************************************************************************/
        template<class T>
        static void FromJson(boost::optional<T> &object, const nlohmann::json &jsonObject) {
            using Type = typename Remove_CVR<T>::Type;
            Type var = Type();
            FromJson(var, jsonObject);
            object = var;
        }

        template<class T>
        static void FromJson(boost::optional<T *> &object, const nlohmann::json &jsonObject) {
            using Type = typename Remove_CVR<T>::Type;
            Type *var = new Type();
            FromJson(var, jsonObject);
            if (object) {
                delete *object;
            }
            object = var;
        }

    };
}


#endif //OPEN_JSON_DESERIALIZER_H
