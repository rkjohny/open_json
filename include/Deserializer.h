#ifndef OPEN_JSON_DESERIALIZER_H
#define OPEN_JSON_DESERIALIZER_H

#include "CommonDef.h"
#include <nlohmann/json.hpp>
#include "boost/optional.hpp"
#include "TypeTraits.h"


namespace open_json::deserializer {

    template<class T, class B, class ArgT>
    static void SetData(T &object, void (B::*SetterPtr)(ArgT), const nlohmann::json &jsonObject);

    template<size_t iteration, class T>
    static void DoDeserialize(T *object, const nlohmann::json &jsonObject);

    template<size_t iteration, class T>
    typename std::enable_if<(iteration > 1), void>::type
    static Deserialize(T &object, const nlohmann::json &jsonObject);

    template<size_t iteration, class T>
    typename std::enable_if<(iteration == 1), void>::type
    static Deserialize(T &object, const nlohmann::json &jsonObject);

    template<size_t iteration, class T>
    typename std::enable_if<(iteration == 0), void>::type
    static Deserialize(T &, const nlohmann::json &);

    template<class T>
    typename std::enable_if<std::is_reference<T>::value || std::is_const<T>::value || Is_Array<T>::Value, T>::type
    FromJsonObject(nlohmann::json &);

    template<class T, size_t length>
    typename std::enable_if<std::is_reference<T>::value || std::is_const<T>::value || Is_Array<T>::Value, T>::type
    FromJsonObject(nlohmann::json &);

    template<class T>
    typename std::enable_if<Is_Enum<T>::Value && !Is_Pointer<T>::Value, T>::type
    static FromJsonObject(const nlohmann::json &jsonObject);

    template<class T>
    typename std::enable_if<Is_Bool<T>::Value && !Is_Pointer<T>::Value, T>::type
    static FromJsonObject(const nlohmann::json &jsonObject);

    template<class T>
    typename std::enable_if<Is_Char<T>::Value && !Is_Pointer<T>::Value, T>::type
    static FromJsonObject(const nlohmann::json &jsonObject);

//    template<class T>
//    typename std::enable_if<Is_UChar<T>::Value && !Is_Pointer<T>::Value, T>::type
//    static FromJsonObject(const nlohmann::json &jsonObject);

    template<class T>
    typename std::enable_if<Is_Int8<T>::Value && !Is_Pointer<T>::Value, T>::type
    static FromJsonObject(const nlohmann::json &jsonObject);

    template<class T>
    typename std::enable_if<Is_UInt8<T>::Value && !Is_Pointer<T>::Value, T>::type
    static FromJsonObject(const nlohmann::json &jsonObject);

    template<class T>
    typename std::enable_if<Is_Int16<T>::Value && !Is_Pointer<T>::Value, T>::type
    static FromJsonObject(const nlohmann::json &jsonObject);

    template<class T>
    typename std::enable_if<Is_UInt16<T>::Value && !Is_Pointer<T>::Value, T>::type
    static FromJsonObject(const nlohmann::json &jsonObject);

    template<class T>
    typename std::enable_if<Is_Int32<T>::Value && !Is_Pointer<T>::Value, T>::type
    static FromJsonObject(const nlohmann::json &jsonObject);

    template<class T>
    typename std::enable_if<Is_UInt32<T>::Value && !Is_Pointer<T>::Value, T>::type
    static FromJsonObject(const nlohmann::json &jsonObject);

    template<class T>
    typename std::enable_if<Is_Int64<T>::Value && !Is_Pointer<T>::Value, T>::type
    static FromJsonObject(const nlohmann::json &jsonObject);

    template<class T>
    typename std::enable_if<Is_UInt64<T>::Value && !Is_Pointer<T>::Value, T>::type
    static FromJsonObject(const nlohmann::json &jsonObject);

    template<class T>
    typename std::enable_if<Is_Float<T>::Value && !Is_Pointer<T>::Value, T>::type
    static FromJsonObject(const nlohmann::json &jsonObject);

    template<class T>
    typename std::enable_if<Is_Double<T>::Value && !Is_Pointer<T>::Value, T>::type
    static FromJsonObject(const nlohmann::json &jsonObject);

    template<class T>
    typename std::enable_if<Is_LongDouble<T>::Value && !Is_Pointer<T>::Value, T>::type
    static FromJsonObject(const nlohmann::json &jsonObject);

    template<class T>
    typename std::enable_if<Is_String<T>::Value && !Is_Pointer<T>::Value, T>::type
    static FromJsonObject(const nlohmann::json &jsonObject);

    template<class T>
    typename std::enable_if<Is_Class<T>::Value && !Is_Pointer<T>::Value, T>::type
    static FromJsonObject(const nlohmann::json &jsonObject);

    template<class T>
    typename std::enable_if<Is_Pointer<T>::Value, T>::type
    static FromJsonObject(const nlohmann::json &jsonObject);


    /**
     * calls the setter method with value type argument
     */
    template<class B, class D, class ArgT>
    static void SetData(B &object, void (D::*SetterPtr)(ArgT), const nlohmann::json &jsonObject) {
        using Type = typename Remove_CVR<ArgT>::Type;

        Type var = FromJsonObject<Type>(jsonObject);
        (object.*SetterPtr)(var);
    }

    /**
     * get the setter at tuple position referenced by iteration.
     * call the setter to set the value to the object's property.
     */
    template<size_t iteration, class T>
    static void DoDeserialize(T &object, const nlohmann::json &jsonObject) {
        using BaseObjectType = typename Remove_CVR<T>::Type;
        auto setters = BaseObjectType::setters;
        auto setter = std::get<iteration>(setters);

        using DerivedObjectType = typename Remove_CVR<typename decltype(setter)::Class>::Type;

        using ArgT = typename decltype( setter )::ArgType;

        auto name = setter.name;
        auto fp = setter.fp;

        bool found = false;

        if (jsonObject.template contains<nlohmann::json>(name)) {
            const auto &jsonValue = jsonObject.template at<nlohmann::json>(name);

            if (!jsonValue.is_null()) {
                found = true;
                // BaseObjectType and DerivedObjectType can be same type

                SetData<BaseObjectType, DerivedObjectType, ArgT>(object, fp, jsonValue);

//                using Type = typename Remove_CVR<ArgT>::Type;
//                Type var = FromJsonObject<Type>(jsonObject);
//                (object.*fp)(var);
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
    static Deserialize(T &object, const nlohmann::json &jsonObject) {
        DoDeserialize<iteration - 1>(object, jsonObject);

        Deserialize<iteration - 1>(object, jsonObject);
    }

    /**
     * execute the setter at position 0
     */
    template<size_t iteration, class T>
    typename std::enable_if<(iteration == 1), void>::type
    static Deserialize(T &object, const nlohmann::json &jsonObject) {
        DoDeserialize<0>(object, jsonObject);
    }

    /**
     * added to remove compile error.
     * when setters length is 0, it will try to compile with iteration = 0
     */
    template<size_t iteration, class T>
    typename std::enable_if<(iteration == 0), void>::type
    static Deserialize(T &, const nlohmann::json &) {
    }


    /**
     * object is constant reference, return error
     */
    template<class T>
    typename std::enable_if<std::is_reference<T>::value || std::is_const<T>::value || Is_Array<T>::Value, T>::type
    FromJsonObject(nlohmann::json &) {
        static_assert(true, "constant or reference object cannot be constructed");
    }

    /**
     * object is constant reference, return error
     */
    template<class T, size_t length>
    typename std::enable_if<std::is_reference<T>::value || std::is_const<T>::value || Is_Array<T>::Value, T>::type
    FromJsonObject(nlohmann::json &) {
        static_assert(true, "constant or reference object cannot be constructed");
    }


    /********************************************************************************
     * object type: enum
     ********************************************************************************/
    template<class T>
    typename std::enable_if<Is_Enum<T>::Value && !Is_Pointer<T>::Value, T>::type
    static FromJsonObject(const nlohmann::json &jsonObject) {
        return static_cast<T>(jsonObject.template get<int32_t>());
    }

    /*********************************************************************************
     * object type: bool
     *********************************************************************************/
    template<class T>
    typename std::enable_if<Is_Bool<T>::Value && !Is_Pointer<T>::Value, T>::type
    static FromJsonObject(const nlohmann::json &jsonObject) {
        return static_cast<bool>(jsonObject.template get<bool>());
    }

    /*********************************************************************************
     * object type: char
     *********************************************************************************/
    template<class T>
    typename std::enable_if<Is_Char<T>::Value && !Is_Pointer<T>::Value, T>::type
    static FromJsonObject(const nlohmann::json &jsonObject) {
        return static_cast<char>(jsonObject.template get<char>());
    }

    /*********************************************************************************
     * object type: unsigned char
     *********************************************************************************/
//    template<class T>
//    typename std::enable_if<Is_UChar<T>::Value && !Is_Pointer<T>::Value, T>::type
//    static FromJsonObject(const nlohmann::json &jsonObject) {
//        return static_cast<unsigned char>(jsonObject.template get<unsigned char>());
//    }

    /***********************************************************************************
     * object type: int8_t
     ***********************************************************************************/
    template<class T>
    typename std::enable_if<Is_Int8<T>::Value && !Is_Pointer<T>::Value, T>::type
    static FromJsonObject(const nlohmann::json &jsonObject) {
        return static_cast<int32_t>(jsonObject.template get<int8_t>());
    }

    /***********************************************************************************
    * object type: uint8_t
    ***********************************************************************************/
    template<class T>
    typename std::enable_if<Is_UInt8<T>::Value && !Is_Pointer<T>::Value, T>::type
    static FromJsonObject(const nlohmann::json &jsonObject) {
        return static_cast<int32_t>(jsonObject.template get<uint8_t>());
    }

    /***********************************************************************************
     * object type: int16_t
     ***********************************************************************************/
    template<class T>
    typename std::enable_if<Is_Int16<T>::Value && !Is_Pointer<T>::Value, T>::type
    static FromJsonObject(const nlohmann::json &jsonObject) {
        return static_cast<int32_t>(jsonObject.template get<int16_t>());
    }

    /***********************************************************************************
     * object type: uint16_t
     ***********************************************************************************/
    template<class T>
    typename std::enable_if<Is_UInt16<T>::Value && !Is_Pointer<T>::Value, T>::type
    static FromJsonObject(const nlohmann::json &jsonObject) {
        return static_cast<int32_t>(jsonObject.template get<uint16_t>());
    }

    /***********************************************************************************
     * object type: int32_t
     ***********************************************************************************/
    template<class T>
    typename std::enable_if<Is_Int32<T>::Value && !Is_Pointer<T>::Value, T>::type
    static FromJsonObject(const nlohmann::json &jsonObject) {
        return static_cast<int32_t>(jsonObject.template get<int32_t>());
    }

    /***********************************************************************************
     * object type: uint32_t
     ***********************************************************************************/
    template<class T>
    typename std::enable_if<Is_UInt32<T>::Value && !Is_Pointer<T>::Value, T>::type
    static FromJsonObject(const nlohmann::json &jsonObject) {
        return static_cast<uint32_t>(jsonObject.template get<uint32_t>());
    }

    /***********************************************************************************
     * object type: int64_t
     ***********************************************************************************/
    template<class T>
    typename std::enable_if<Is_Int64<T>::Value && !Is_Pointer<T>::Value, T>::type
    static FromJsonObject(const nlohmann::json &jsonObject) {
        return static_cast<int64_t>(jsonObject.template get<int64_t>());
    }

    /***********************************************************************************
     * object type: uint64_t
     ***********************************************************************************/
    template<class T>
    typename std::enable_if<Is_UInt64<T>::Value && !Is_Pointer<T>::Value, T>::type
    static FromJsonObject(const nlohmann::json &jsonObject) {
        return static_cast<uint64_t>(jsonObject.template get<uint64_t>());
    }

    /***********************************************************************************
     * object type: float
     ***********************************************************************************/
    template<class T>
    typename std::enable_if<Is_Float<T>::Value && !Is_Pointer<T>::Value, T>::type
    static FromJsonObject(const nlohmann::json &jsonObject) {
        return static_cast<double_t>(jsonObject.template get<float_t>());
    }

    /***********************************************************************************
    * object type: double
    ***********************************************************************************/
    template<class T>
    typename std::enable_if<Is_Double<T>::Value && !Is_Pointer<T>::Value, T>::type
    static FromJsonObject(const nlohmann::json &jsonObject) {
        return static_cast<double_t>(jsonObject.template get<double_t>());
    }

    /***********************************************************************************
     * object type: long double
     ***********************************************************************************/
    template<class T>
    typename std::enable_if<Is_LongDouble<T>::Value && !Is_Pointer<T>::Value, T>::type
    static FromJsonObject(const nlohmann::json &jsonObject) {
        return static_cast<double_t>(jsonObject.template get<long double>());
    }

    /***********************************************************************************
     * object type: std::string
     ***********************************************************************************/
    template<class T>
    typename std::enable_if<Is_String<T>::Value && !Is_Pointer<T>::Value, T>::type
    static FromJsonObject(const nlohmann::json &jsonObject) {
        return jsonObject.template get<std::string>();
    }


    /***********************************************************************************
     * object type: custom class*
     ***********************************************************************************/
    template<class T>
    typename std::enable_if<Is_Class<T>::Value && !Is_Pointer<T>::Value, T>::type
    static FromJsonObject(const nlohmann::json &jsonObject) {
        using Type = typename Remove_CVR<T>::Type;
        auto setters = Type::setters;
        const auto length = std::tuple_size<decltype(setters)>::value;
        Type object = Type();

        if (length > 0) {
            Deserialize<length>(object, jsonObject);
        }
        return object;
    }


    /***********************************************************************************
     * object type: pointer
     ***********************************************************************************/
    template<class T>
    typename std::enable_if<Is_Pointer<T>::Value, T>::type
    static FromJsonObject(const nlohmann::json &jsonObject) {
        using Pointer = typename Remove_CVR<T>::Type;
        using Type = typename Remove_CVRP<Pointer>::Type;
        Pointer tp = new Type();
        *tp = FromJsonObject<Type>(jsonObject);
        return tp;
    }
}


#endif //OPEN_JSON_DESERIALIZER_H
