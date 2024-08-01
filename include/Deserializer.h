#ifndef OPEN_JSON_DESERIALIZER_H
#define OPEN_JSON_DESERIALIZER_H

#include <iostream>
#include "CommonDef.h"
#include <nlohmann/json.hpp>
#include "boost/optional.hpp"
#include "TypeTraits.h"
#include "Setter.h"


namespace open_json::deserializer {

    template<class T, class B, class ArgT>
    static void SetData(T &object, void (B::*SetterPtr)(ArgT &&), const nlohmann::json &jsonObject);

    template<class T, class B, class ArgT>
    std::enable_if_t<
            (!is_const<ArgT>::value && !is_pointer<ArgT>::value) ||
            (!is_const<ArgT>::value && is_pointer<ArgT>::value) ||
            (is_const<ArgT>::value && !is_pointer<ArgT>::value), void>
    static SetData(T &object, void (B::*SetterPtr)(ArgT), const nlohmann::json &jsonObject);

    template<class T, class B, class ArgT>
    std::enable_if_t<is_const<ArgT>::value && is_pointer<ArgT>::value, void>
    static SetData(T &object, void (B::*SetterPtr)(ArgT), const nlohmann::json &jsonObject);


    template<size_t iteration, class T>
    static void DoDeserialize(T *object, const nlohmann::json &jsonObject);

    template<size_t iteration, class T>
    std::enable_if_t<(iteration > 1), void>
    static Deserialize(T &object, const nlohmann::json &jsonObject);

    template<size_t iteration, class T>
    std::enable_if_t<(iteration == 1), void>
    static Deserialize(T &object, const nlohmann::json &jsonObject);

    template<size_t iteration, class T>
    std::enable_if_t<(iteration == 0), void>
    static Deserialize(T &, const nlohmann::json &);

    template<class T>
    std::enable_if_t<is_enum<T>::value && !is_pointer<T>::value, T>
    static FromJsonObject(const nlohmann::json &jsonObject);

    template<class T>
    std::enable_if_t<is_enum<T>::value && !is_pointer<T>::value, void>
    static FromJsonObject(T &object, const nlohmann::json &jsonObject);

    template<class T>
    std::enable_if_t<is_bool<T>::value && !is_pointer<T>::value, T>
    static FromJsonObject(const nlohmann::json &jsonObject);

    template<class T>
    std::enable_if_t<is_bool<T>::value && !is_pointer<T>::value, void>
    static FromJsonObject(T &object, const nlohmann::json &jsonObject);

    template<class T>
    std::enable_if_t<is_char<T>::value && !is_pointer<T>::value, T>
    static FromJsonObject(const nlohmann::json &jsonObject);

    template<class T>
    std::enable_if_t<is_char<T>::value && !is_pointer<T>::value, void>
    static FromJsonObject(T &object, const nlohmann::json &jsonObject);

    template<class T>
    std::enable_if_t<is_int8<T>::value && !is_pointer<T>::value, T>
    static FromJsonObject(const nlohmann::json &jsonObject);

    template<class T>
    std::enable_if_t<is_int8<T>::value && !is_pointer<T>::value, void>
    static FromJsonObject(T &object, const nlohmann::json &jsonObject);

    template<class T>
    std::enable_if_t<is_uint8<T>::value && !is_pointer<T>::value, T>
    static FromJsonObject(const nlohmann::json &jsonObject);

    template<class T>
    std::enable_if_t<is_uint8<T>::value && !is_pointer<T>::value, void>
    static FromJsonObject(T &object, const nlohmann::json &jsonObject);

    template<class T>
    std::enable_if_t<is_int16<T>::value && !is_pointer<T>::value, T>
    static FromJsonObject(const nlohmann::json &jsonObject);

    template<class T>
    std::enable_if_t<is_int16<T>::value && !is_pointer<T>::value, void>
    static FromJsonObject(T &object, const nlohmann::json &jsonObject);

    template<class T>
    std::enable_if_t<is_uint16<T>::value && !is_pointer<T>::value, T>
    static FromJsonObject(const nlohmann::json &jsonObject);

    template<class T>
    std::enable_if_t<is_uint16<T>::value && !is_pointer<T>::value, void>
    static FromJsonObject(T &object, const nlohmann::json &jsonObject);

    template<class T>
    std::enable_if_t<is_int32<T>::value && !is_pointer<T>::value, T>
    static FromJsonObject(const nlohmann::json &jsonObject);

    template<class T>
    std::enable_if_t<is_int32<T>::value && !is_pointer<T>::value, void>
    static FromJsonObject(T &object, const nlohmann::json &jsonObject);

    template<class T>
    std::enable_if_t<is_uint32<T>::value && !is_pointer<T>::value, T>
    static FromJsonObject(const nlohmann::json &jsonObject);

    template<class T>
    std::enable_if_t<is_uint32<T>::value && !is_pointer<T>::value, void>
    static FromJsonObject(T &object, const nlohmann::json &jsonObject);

    template<class T>
    std::enable_if_t<is_int64<T>::value && !is_pointer<T>::value, T>
    static FromJsonObject(const nlohmann::json &jsonObject);

    template<class T>
    std::enable_if_t<is_int64<T>::value && !is_pointer<T>::value, void>
    static FromJsonObject(T &object, const nlohmann::json &jsonObject);

    template<class T>
    std::enable_if_t<is_uint64<T>::value && !is_pointer<T>::value, T>
    static FromJsonObject(const nlohmann::json &jsonObject);

    template<class T>
    std::enable_if_t<is_uint64<T>::value && !is_pointer<T>::value, void>
    static FromJsonObject(T &object, const nlohmann::json &jsonObject);

    template<class T>
    std::enable_if_t<is_float<T>::value && !is_pointer<T>::value, T>
    static FromJsonObject(const nlohmann::json &jsonObject);

    template<class T>
    std::enable_if_t<is_float<T>::value && !is_pointer<T>::value, void>
    static FromJsonObject(T &object, const nlohmann::json &jsonObject);

    template<class T>
    std::enable_if_t<is_double<T>::value && !is_pointer<T>::value, T>
    static FromJsonObject(const nlohmann::json &jsonObject);

    template<class T>
    std::enable_if_t<is_double<T>::value && !is_pointer<T>::value, void>
    static FromJsonObject(T &object, const nlohmann::json &jsonObject);

    template<class T>
    std::enable_if_t<is_long_double<T>::value && !is_pointer<T>::value, T>
    static FromJsonObject(const nlohmann::json &jsonObject);

    template<class T>
    std::enable_if_t<is_long_double<T>::value && !is_pointer<T>::value, void>
    static FromJsonObject(T &object, const nlohmann::json &jsonObject);

    template<class T>
    std::enable_if_t<is_string<T>::value && !is_pointer<T>::value, T>
    static FromJsonObject(const nlohmann::json &jsonObject);

    template<class T>
    std::enable_if_t<is_string<T>::value && !is_pointer<T>::value, void>
    static FromJsonObject(T &object, const nlohmann::json &jsonObject);

    template<class T>
    std::enable_if_t<is_class<T>::value && !is_pointer<T>::value, T>
    static FromJsonObject(const nlohmann::json &jsonObject);

    template<class T>
    std::enable_if_t<is_class<T>::value && !is_pointer<T>::value, void>
    static FromJsonObject(T &object, const nlohmann::json &jsonObject);

    template<class T>
    std::enable_if_t<is_vector<T>::value && !is_pointer<T>::value, T>
    static FromJsonObject(const nlohmann::json &jsonObject);

    template<class T>
    std::enable_if_t<is_vector<T>::value && !is_pointer<T>::value, void>
    static FromJsonObject(T &object, const nlohmann::json &jsonObject);

    template<class T>
    std::enable_if_t<is_pointer<T>::value && is_pointer<remove_all_cvr_single_p_t<T>>::value, T>
    static FromJsonObject(const nlohmann::json &jsonObject);

    template<class T>
    std::enable_if_t<is_pointer<T>::value && !is_pointer<remove_all_cvr_single_p_t<T>>::value, T>
    static FromJsonObject(const nlohmann::json &jsonObject);

    template<class T>
    std::enable_if_t<is_pointer<T>::value, T>
    FromJsonObject(const nlohmann::json &jsonArray, size_t length);




    template<class T, class B, class ArgT>
    static void SetData(T &object, void (B::*SetterPtr)(ArgT &&), const nlohmann::json &jsonObject) {
        using Type = remove_all_cvr_t<ArgT>;

        Type var = FromJsonObject<Type>(jsonObject);
        (object.*SetterPtr)(std::move(var));
    }

    template<class T, class B, class ArgT>
    std::enable_if_t<
            (!is_const<ArgT>::value && !is_pointer<ArgT>::value) ||
            (!is_const<ArgT>::value && is_pointer<ArgT>::value) ||
            (is_const<ArgT>::value && !is_pointer<ArgT>::value), void>
    static SetData(T &object, void (B::*SetterPtr)(ArgT), const nlohmann::json &jsonObject) {
        using Type = remove_all_cvr_t<ArgT>;

        Type var = FromJsonObject<Type>(jsonObject);
        (object.*SetterPtr)(var);
    }

    template<class T, class B, class ArgT>
    std::enable_if_t<is_const<ArgT>::value && is_pointer<ArgT>::value, void>
    static SetData(T &object, void (B::*SetterPtr)(ArgT), const nlohmann::json &jsonObject) {
        using Type = remove_all_cvr_t<ArgT>;

        Type var = FromJsonObject<Type>(jsonObject);
        (object.*SetterPtr)(const_cast<ArgT>(var));
    }


    /**
     * get the setter at tuple position referenced by iteration.
     * call the setter to set the value to the object's property.
     */
    template<size_t iteration, class T>
    static void DoDeserialize(T &object, const nlohmann::json &jsonObject) {
        using DerivedType = remove_all_cvrp_t<T>;
        auto setters = DerivedType::setters;
        auto setter = std::get<iteration>(setters);

        using BaseType = remove_all_cvrp_t<typename decltype(setter)::ClassType>;
        //using ArgT = typename decltype( setter )::ArgType;

        auto name = setter.name;
        auto fp = setter.fp;

        if (jsonObject.template contains<nlohmann::json>(name)) {
            const auto &jsonValue = jsonObject.template at<nlohmann::json>(name);

            if (!jsonValue.is_null()) {
                // BaseObjectType and DerivedObjectType can be same type
                SetData<DerivedType, BaseType>(object, fp, jsonValue);
            }
        }
    }

    /**
     * execute the setter at position greater than 0
     */
    template<size_t iteration, class T>
    std::enable_if_t<(iteration > 1), void>
    static Deserialize(T &object, const nlohmann::json &jsonObject) {
        DoDeserialize<iteration - 1>(object, jsonObject);

        Deserialize<iteration - 1>(object, jsonObject);
    }

    /**
     * execute the setter at position 0
     */
    template<size_t iteration, class T>
    std::enable_if_t<(iteration == 1), void>
    static Deserialize(T &object, const nlohmann::json &jsonObject) {
        DoDeserialize<0>(object, jsonObject);
    }

    /**
     * added to remove compile error.
     * when setters length is 0, it will try to compile with iteration = 0
     */
    template<size_t iteration, class T>
    std::enable_if_t<(iteration == 0), void>
    static Deserialize(T &, const nlohmann::json &) {
    }


    /********************************************************************************
     * object type: enum
     ********************************************************************************/
    template<class T>
    std::enable_if_t<is_enum<T>::value && !is_pointer<T>::value, T>
    static FromJsonObject(const nlohmann::json &jsonObject) {
        return static_cast<T>(jsonObject.template get<int32_t>());
    }

    template<class T>
    std::enable_if_t<is_enum<T>::value && !is_pointer<T>::value, void>
    static FromJsonObject(T &object, const nlohmann::json &jsonObject) {
        object = static_cast<T>(jsonObject.template get<int32_t>());
    }

    /*********************************************************************************
     * object type: bool
     *********************************************************************************/
    template<class T>
    std::enable_if_t<is_bool<T>::value && !is_pointer<T>::value, T>
    static FromJsonObject(const nlohmann::json &jsonObject) {
        return static_cast<bool>(jsonObject.template get<bool>());
    }

    template<class T>
    std::enable_if_t<is_bool<T>::value && !is_pointer<T>::value, void>
    static FromJsonObject(T &object, const nlohmann::json &jsonObject) {
        object = static_cast<bool>(jsonObject.template get<bool>());
    }

    /*********************************************************************************
     * object type: char
     *********************************************************************************/
    template<class T>
    std::enable_if_t<is_char<T>::value && !is_pointer<T>::value, T>
    static FromJsonObject(const nlohmann::json &jsonObject) {
        return static_cast<char>(jsonObject.template get<char>());
    }

    template<class T>
    std::enable_if_t<is_char<T>::value && !is_pointer<T>::value, void>
    static FromJsonObject(T &object, const nlohmann::json &jsonObject) {
        object = static_cast<char>(jsonObject.template get<char>());
    }

    /***********************************************************************************
     * object type: int8_t
     ***********************************************************************************/
    template<class T>
    std::enable_if_t<is_int8<T>::value && !is_pointer<T>::value, T>
    static FromJsonObject(const nlohmann::json &jsonObject) {
        return static_cast<int32_t>(jsonObject.template get<int8_t>());
    }

    template<class T>
    std::enable_if_t<is_int8<T>::value && !is_pointer<T>::value, void>
    static FromJsonObject(T &object, const nlohmann::json &jsonObject) {
        object = static_cast<int32_t>(jsonObject.template get<int8_t>());
    }

    /***********************************************************************************
    * object type: uint8_t
    ***********************************************************************************/
    template<class T>
    std::enable_if_t<is_uint8<T>::value && !is_pointer<T>::value, T>
    static FromJsonObject(const nlohmann::json &jsonObject) {
        return static_cast<int32_t>(jsonObject.template get<uint8_t>());
    }

    template<class T>
    std::enable_if_t<is_uint8<T>::value && !is_pointer<T>::value, void>
    static FromJsonObject(T &object, const nlohmann::json &jsonObject) {
        object = static_cast<int32_t>(jsonObject.template get<uint8_t>());
    }

    /***********************************************************************************
     * object type: int16_t
     ***********************************************************************************/
    template<class T>
    std::enable_if_t<is_int16<T>::value && !is_pointer<T>::value, T>
    static FromJsonObject(const nlohmann::json &jsonObject) {
        return static_cast<int32_t>(jsonObject.template get<int16_t>());
    }

    template<class T>
    std::enable_if_t<is_int16<T>::value && !is_pointer<T>::value, void>
    static FromJsonObject(T &object, const nlohmann::json &jsonObject) {
        object = static_cast<int32_t>(jsonObject.template get<int16_t>());
    }

    /***********************************************************************************
     * object type: uint16_t
     ***********************************************************************************/
    template<class T>
    std::enable_if_t<is_uint16<T>::value && !is_pointer<T>::value, T>
    static FromJsonObject(const nlohmann::json &jsonObject) {
        return static_cast<int32_t>(jsonObject.template get<uint16_t>());
    }

    template<class T>
    std::enable_if_t<is_uint16<T>::value && !is_pointer<T>::value, void>
    static FromJsonObject(T &object, const nlohmann::json &jsonObject) {
        object = static_cast<int32_t>(jsonObject.template get<uint16_t>());
    }

    /***********************************************************************************
     * object type: int32_t
     ***********************************************************************************/
    template<class T>
    std::enable_if_t<is_int32<T>::value && !is_pointer<T>::value, T>
    static FromJsonObject(const nlohmann::json &jsonObject) {
        return static_cast<int32_t>(jsonObject.template get<int32_t>());
    }

    template<class T>
    std::enable_if_t<is_int32<T>::value && !is_pointer<T>::value, void>
    static FromJsonObject(T &object, const nlohmann::json &jsonObject) {
        object = static_cast<int32_t>(jsonObject.template get<int32_t>());
    }

    /***********************************************************************************
     * object type: uint32_t
     ***********************************************************************************/
    template<class T>
    std::enable_if_t<is_uint32<T>::value && !is_pointer<T>::value, T>
    static FromJsonObject(const nlohmann::json &jsonObject) {
        return static_cast<uint32_t>(jsonObject.template get<uint32_t>());
    }

    template<class T>
    std::enable_if_t<is_uint32<T>::value && !is_pointer<T>::value, void>
    static FromJsonObject(T &object, const nlohmann::json &jsonObject) {
        object = static_cast<uint32_t>(jsonObject.template get<uint32_t>());
    }

    /***********************************************************************************
     * object type: int64_t
     ***********************************************************************************/
    template<class T>
    std::enable_if_t<is_int64<T>::value && !is_pointer<T>::value, T>
    static FromJsonObject(const nlohmann::json &jsonObject) {
        return static_cast<int64_t>(jsonObject.template get<int64_t>());
    }

    template<class T>
    std::enable_if_t<is_int64<T>::value && !is_pointer<T>::value, void>
    static FromJsonObject(T &object, const nlohmann::json &jsonObject) {
        object = static_cast<int64_t>(jsonObject.template get<int64_t>());
    }

    /***********************************************************************************
     * object type: uint64_t
     ***********************************************************************************/
    template<class T>
    std::enable_if_t<is_uint64<T>::value && !is_pointer<T>::value, T>
    static FromJsonObject(const nlohmann::json &jsonObject) {
        return static_cast<uint64_t>(jsonObject.template get<uint64_t>());
    }

    template<class T>
    std::enable_if_t<is_uint64<T>::value && !is_pointer<T>::value, void>
    static FromJsonObject(T &object, const nlohmann::json &jsonObject) {
        object = static_cast<uint64_t>(jsonObject.template get<uint64_t>());
    }

    /***********************************************************************************
     * object type: float
     ***********************************************************************************/
    template<class T>
    std::enable_if_t<is_float<T>::value && !is_pointer<T>::value, T>
    static FromJsonObject(const nlohmann::json &jsonObject) {
        return static_cast<double_t>(jsonObject.template get<float_t>());
    }

    template<class T>
    std::enable_if_t<is_float<T>::value && !is_pointer<T>::value, void>
    static FromJsonObject(T &object, const nlohmann::json &jsonObject) {
        object = static_cast<double_t>(jsonObject.template get<float_t>());
    }

    /***********************************************************************************
    * object type: double
    ***********************************************************************************/
    template<class T>
    std::enable_if_t<is_double<T>::value && !is_pointer<T>::value, T>
    static FromJsonObject(const nlohmann::json &jsonObject) {
        return static_cast<double_t>(jsonObject.template get<double_t>());
    }

    template<class T>
    std::enable_if_t<is_double<T>::value && !is_pointer<T>::value, void>
    static FromJsonObject(T &object, const nlohmann::json &jsonObject) {
        object = static_cast<double_t>(jsonObject.template get<double_t>());
    }

    /***********************************************************************************
     * object type: long double
     ***********************************************************************************/
    template<class T>
    std::enable_if_t<is_long_double<T>::value && !is_pointer<T>::value, T>
    static FromJsonObject(const nlohmann::json &jsonObject) {
        return static_cast<double_t>(jsonObject.template get<long double>());
    }

    template<class T>
    std::enable_if_t<is_long_double<T>::value && !is_pointer<T>::value, void>
    static FromJsonObject(T &object, const nlohmann::json &jsonObject) {
        object = static_cast<double_t>(jsonObject.template get<long double>());
    }

    /***********************************************************************************
     * object type: std::string
     ***********************************************************************************/
    template<class T>
    std::enable_if_t<is_string<T>::value && !is_pointer<T>::value, T>
    static FromJsonObject(const nlohmann::json &jsonObject) {
        return jsonObject.template get<std::string>();
    }

    template<class T>
    std::enable_if_t<is_string<T>::value && !is_pointer<T>::value, void>
    static FromJsonObject(T &object, const nlohmann::json &jsonObject) {
        object = jsonObject.template get<std::string>();
    }


    /***********************************************************************************
     * object type: custom class
     ***********************************************************************************/
    template<class T>
    std::enable_if_t<is_class<T>::value && !is_pointer<T>::value, T>
    static FromJsonObject(const nlohmann::json &jsonObject) {
        using Type = remove_all_cvrp_t<T>;
        auto setters = Type::setters;
        const auto length = std::tuple_size<decltype(setters)>::value;
        Type object = Type();

        if (length > 0) {
            Deserialize<length>(object, jsonObject);
        }
        return object;
    }

    template<class T>
    std::enable_if_t<is_class<T>::value && !is_pointer<T>::value, void>
    static FromJsonObject(T &object, const nlohmann::json &jsonObject) {
        using Type = remove_all_cvrp_t<T>;
        auto setters = Type::setters;
        const auto length = std::tuple_size<decltype(setters)>::value;
        if (length > 0) {
            Deserialize<length>(object, jsonObject);
        }
    }

    /***********************************************************************************
     * object type: std::vector<T>
     ***********************************************************************************/
    template<class T>
    std::enable_if_t<is_vector<T>::value && !is_pointer<T>::value, T>
    static FromJsonObject(const nlohmann::json &jsonObject) {
        using Type = remove_all_cvrp_t<T>;
        typedef typename Type::value_type ValueType;

        Type vec = Type();

        for (const auto &arrItem: jsonObject) {
            ValueType var = FromJsonObject<ValueType>(arrItem);
            vec.push_back(var);
        }
        return vec;
    }

    template<class T>
    std::enable_if_t<is_vector<T>::value && !is_pointer<T>::value, void>
    static FromJsonObject(T &object, const nlohmann::json &jsonObject) {
        using Type = remove_all_cvrp_t<T>;
        typedef typename Type::value_type ValueType;

        for (const auto &arrItem: jsonObject) {
            ValueType var = FromJsonObject<ValueType>(arrItem);
            object.push_back(var);
        }
    }

    /***********************************************************************************
     * object type: Pointer
     ***********************************************************************************/
    template<class T>
    std::enable_if_t<is_pointer<T>::value && is_pointer<remove_all_cvr_single_p_t<T>>::value, T>
    static FromJsonObject(const nlohmann::json &jsonObject) {
        using Pointer = remove_all_cvr_t<T>;
        using Type = remove_all_cvr_single_p_t<Pointer>;
        Pointer p = new Type();
        *p = FromJsonObject<Type>(jsonObject);
        return p;
    }

    template<class T>
    std::enable_if_t<is_pointer<T>::value && !is_pointer<remove_all_cvr_single_p_t<T>>::value, T>
    static FromJsonObject(const nlohmann::json &jsonObject) {
        using Pointer = remove_all_cvr_t<T>;
        using Type = remove_all_cvr_single_p_t<Pointer>;
        Pointer p = new Type();
        FromJsonObject(*p, jsonObject);
        return p;
    }

    /***********************************************************************************
     * object type: Array
     ***********************************************************************************/
    template<class T>
    std::enable_if_t<is_pointer<T>::value, T>
    FromJsonObject(const nlohmann::json &jsonArray, size_t length) {
        using Pointer = remove_all_cvr_t<T>;
        using Type = remove_all_cvr_single_p_t<Pointer>;
        Pointer array = new Type [length];
        for(size_t i = 0; i<length; ++i) {
            array[i] = FromJsonObject<Type>(jsonArray[i]);
        }
        return array;
    }

    /***********************************************************************************
    * object type: std::unique_ptr<T>
    ***********************************************************************************/
//    template<class T>
//    static void FromJson(const nlohmann::json &jsonObject) {
//        using Type = typename remove_all_cvr_t<T>::type;
//        std::unique_ptr<Type> var = std::make_unique<Type>();
//        FromJson(*var.get(), jsonObject);
//        return std::move(var);
//    }
}

#endif //OPEN_JSON_DESERIALIZER_H
