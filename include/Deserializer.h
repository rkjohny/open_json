#ifndef OPEN_JSON_DESERIALIZER_H
#define OPEN_JSON_DESERIALIZER_H

#include <iostream>
#include "CommonDef.h"
#include <nlohmann/json.hpp>
#include "TypeTraits.h"
#include "Setter.h"
#include "Utils.h"

namespace open_json::deserializer {

    template<class T, class B, class ArgT>
    static void SetData(T &object, void (B::*SetterPtr)(ArgT &&), const nlohmann::json &jsonObject);

    template<class T, class B, class ArgT>
    std::enable_if_t<
            (!is_const_v<ArgT> && !is_pointer_v<ArgT>) ||
            (!is_const_v<ArgT> && is_pointer_v<ArgT>) ||
            (is_const_v<ArgT> && !is_pointer_v<ArgT>), void>
    static SetData(T &object, void (B::*SetterPtr)(ArgT), const nlohmann::json &jsonObject);

    template<class T, class B, class ArgT>
    std::enable_if_t<is_const_v<ArgT> && is_pointer_v<ArgT>, void>
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
    std::enable_if_t<is_enum_v<T> && !is_pointer_v<T>, T>
    static FromJsonObject(const nlohmann::json &jsonObject);

    template<class T>
    std::enable_if_t<is_enum_v<T> && !is_pointer_v<T>, void>
    static FromJsonObject(T &object, const nlohmann::json &jsonObject);

    template<class T>
    std::enable_if_t<is_bool_v<T> && !is_pointer_v<T>, T>
    static FromJsonObject(const nlohmann::json &jsonObject);

    template<class T>
    std::enable_if_t<is_bool_v<T> && !is_pointer_v<T>, void>
    static FromJsonObject(T &object, const nlohmann::json &jsonObject);

    template<class T>
    std::enable_if_t<is_char_v<T> && !is_pointer_v<T>, T>
    static FromJsonObject(const nlohmann::json &jsonObject);

    template<class T>
    std::enable_if_t<is_char_v<T> && !is_pointer_v<T>, void>
    static FromJsonObject(T &object, const nlohmann::json &jsonObject);

    template<class T>
    std::enable_if_t<is_int8_v<T> && !is_pointer_v<T>, T>
    static FromJsonObject(const nlohmann::json &jsonObject);

    template<class T>
    std::enable_if_t<is_int8_v<T> && !is_pointer_v<T>, void>
    static FromJsonObject(T &object, const nlohmann::json &jsonObject);

    template<class T>
    std::enable_if_t<is_uint8_v<T> && !is_pointer_v<T>, T>
    static FromJsonObject(const nlohmann::json &jsonObject);

    template<class T>
    std::enable_if_t<is_uint8_v<T> && !is_pointer_v<T>, void>
    static FromJsonObject(T &object, const nlohmann::json &jsonObject);

    template<class T>
    std::enable_if_t<is_int16_v<T> && !is_pointer_v<T>, T>
    static FromJsonObject(const nlohmann::json &jsonObject);

    template<class T>
    std::enable_if_t<is_int16_v<T> && !is_pointer_v<T>, void>
    static FromJsonObject(T &object, const nlohmann::json &jsonObject);

    template<class T>
    std::enable_if_t<is_uint16_v<T> && !is_pointer_v<T>, T>
    static FromJsonObject(const nlohmann::json &jsonObject);

    template<class T>
    std::enable_if_t<is_uint16_v<T> && !is_pointer_v<T>, void>
    static FromJsonObject(T &object, const nlohmann::json &jsonObject);

    template<class T>
    std::enable_if_t<is_int32_v<T> && !is_pointer_v<T>, T>
    static FromJsonObject(const nlohmann::json &jsonObject);

    template<class T>
    std::enable_if_t<is_int32_v<T> && !is_pointer_v<T>, void>
    static FromJsonObject(T &object, const nlohmann::json &jsonObject);

    template<class T>
    std::enable_if_t<is_uint32_v<T> && !is_pointer_v<T>, T>
    static FromJsonObject(const nlohmann::json &jsonObject);

    template<class T>
    std::enable_if_t<is_uint32_v<T> && !is_pointer_v<T>, void>
    static FromJsonObject(T &object, const nlohmann::json &jsonObject);

    template<class T>
    std::enable_if_t<is_int64_v<T> && !is_pointer_v<T>, T>
    static FromJsonObject(const nlohmann::json &jsonObject);

    template<class T>
    std::enable_if_t<is_int64_v<T> && !is_pointer_v<T>, void>
    static FromJsonObject(T &object, const nlohmann::json &jsonObject);

    template<class T>
    std::enable_if_t<is_uint64_v<T> && !is_pointer_v<T>, T>
    static FromJsonObject(const nlohmann::json &jsonObject);

    template<class T>
    std::enable_if_t<is_uint64_v<T> && !is_pointer_v<T>, void>
    static FromJsonObject(T &object, const nlohmann::json &jsonObject);

    template<class T>
    std::enable_if_t<is_float_v<T> && !is_pointer_v<T>, T>
    static FromJsonObject(const nlohmann::json &jsonObject);

    template<class T>
    std::enable_if_t<is_float_v<T> && !is_pointer_v<T>, void>
    static FromJsonObject(T &object, const nlohmann::json &jsonObject);

    template<class T>
    std::enable_if_t<is_double_v<T> && !is_pointer_v<T>, T>
    static FromJsonObject(const nlohmann::json &jsonObject);

    template<class T>
    std::enable_if_t<is_double_v<T> && !is_pointer_v<T>, void>
    static FromJsonObject(T &object, const nlohmann::json &jsonObject);

    template<class T>
    std::enable_if_t<is_long_double_v<T> && !is_pointer_v<T>, T>
    static FromJsonObject(const nlohmann::json &jsonObject);

    template<class T>
    std::enable_if_t<is_long_double_v<T> && !is_pointer_v<T>, void>
    static FromJsonObject(T &object, const nlohmann::json &jsonObject);

    template<class T>
    std::enable_if_t<is_string_v<T> && !is_pointer_v<T>, T>
    static FromJsonObject(const nlohmann::json &jsonObject);

    template<class T>
    std::enable_if_t<is_string_v<T> && !is_pointer_v<T>, void>
    static FromJsonObject(T &object, const nlohmann::json &jsonObject);

    template<class T>
    std::enable_if_t<is_class_v<T> && !is_pointer_v<T>, T>
    static FromJsonObject(const nlohmann::json &jsonObject);

    template<class T>
    std::enable_if_t<is_class_v<T> && !is_pointer_v<T>, void>
    static FromJsonObject(T &object, const nlohmann::json &jsonObject);

    template<class T>
    std::enable_if_t<is_vector_v<T> && !is_pointer_v<T>, T>
    static FromJsonObject(const nlohmann::json &jsonObject);

    template<class T>
    std::enable_if_t<is_vector_v<T> && !is_pointer_v<T>, void>
    static FromJsonObject(T &object, const nlohmann::json &jsonObject);

    template<class T>
    std::enable_if_t<is_pointer_v<T> && is_pointer_v<remove_all_cvr_single_p_t<T>>, T>
    static FromJsonObject(const nlohmann::json &jsonObject);

    template<class T>
    std::enable_if_t<is_pointer_v<T> && !is_pointer_v<remove_all_cvr_single_p_t<T>>, T>
    static FromJsonObject(const nlohmann::json &jsonObject);

    template<class T>
    std::enable_if_t<is_pointer_v<T>, T>
    static FromJsonObject(const nlohmann::json &jsonArray, size_t length);

    template<class T>
    std::enable_if_t<is_unique_ptr_v<T>, T>
    static FromJsonObject(const nlohmann::json &jsonObject);

    template<class T>
    std::enable_if_t<is_shared_ptr_v<T>, T>
    static FromJsonObject(const nlohmann::json &jsonObject);

    template<class T>
    std::enable_if_t<is_map_v<T>, void>
    static FromJsonObject(T &mapObj, const nlohmann::json &jsonObject);

    template<class T>
    std::enable_if_t<is_map_v<T>, T>
    static FromJsonObject(const nlohmann::json &jsonObject);




    //************************ Implementation *************************************

    template<class T, class B, class ArgT>
    static void SetData(T &object, void (B::*SetterPtr)(ArgT &&), const nlohmann::json &jsonObject) {
        using Type = remove_all_cvr_t<ArgT>;

        Type var = FromJsonObject<Type>(jsonObject);
        (object.*SetterPtr)(std::move(var));
    }

    template<class T, class B, class ArgT>
    std::enable_if_t<
            (!is_const_v<ArgT> && !is_pointer_v<ArgT>) ||
            (!is_const_v<ArgT> && is_pointer_v<ArgT>) ||
            (is_const_v<ArgT> && !is_pointer_v<ArgT>), void>
    static SetData(T &object, void (B::*SetterPtr)(ArgT), const nlohmann::json &jsonObject) {
        using Type = remove_all_cvr_t<ArgT>;

        Type var = FromJsonObject<Type>(jsonObject);
        (object.*SetterPtr)(var);
    }

    template<class T, class B, class ArgT>
    std::enable_if_t<is_const_v<ArgT> && is_pointer_v<ArgT>, void>
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
    std::enable_if_t<is_enum_v<T> && !is_pointer_v<T>, T>
    static FromJsonObject(const nlohmann::json &jsonObject) {
        return static_cast<T>(jsonObject.template get<int32_t>());
    }

    template<class T>
    std::enable_if_t<is_enum_v<T> && !is_pointer_v<T>, void>
    static FromJsonObject(T &object, const nlohmann::json &jsonObject) {
        object = static_cast<T>(jsonObject.template get<int32_t>());
    }

    /*********************************************************************************
     * object type: bool
     *********************************************************************************/
    template<class T>
    std::enable_if_t<is_bool_v<T> && !is_pointer_v<T>, T>
    static FromJsonObject(const nlohmann::json &jsonObject) {
        return static_cast<bool>(jsonObject.template get<bool>());
    }

    template<class T>
    std::enable_if_t<is_bool_v<T> && !is_pointer_v<T>, void>
    static FromJsonObject(T &object, const nlohmann::json &jsonObject) {
        object = static_cast<bool>(jsonObject.template get<bool>());
    }

    /*********************************************************************************
     * object type: char
     *********************************************************************************/
    template<class T>
    std::enable_if_t<is_char_v<T> && !is_pointer_v<T>, T>
    static FromJsonObject(const nlohmann::json &jsonObject) {
        return static_cast<char>(jsonObject.template get<char>());
    }

    template<class T>
    std::enable_if_t<is_char_v<T> && !is_pointer_v<T>, void>
    static FromJsonObject(T &object, const nlohmann::json &jsonObject) {
        object = static_cast<char>(jsonObject.template get<char>());
    }

    /***********************************************************************************
     * object type: int8_t
     ***********************************************************************************/
    template<class T>
    std::enable_if_t<is_int8_v<T> && !is_pointer_v<T>, T>
    static FromJsonObject(const nlohmann::json &jsonObject) {
        return static_cast<int32_t>(jsonObject.template get<int8_t>());
    }

    template<class T>
    std::enable_if_t<is_int8_v<T> && !is_pointer_v<T>, void>
    static FromJsonObject(T &object, const nlohmann::json &jsonObject) {
        object = static_cast<int32_t>(jsonObject.template get<int8_t>());
    }

    /***********************************************************************************
    * object type: uint8_t
    ***********************************************************************************/
    template<class T>
    std::enable_if_t<is_uint8_v<T> && !is_pointer_v<T>, T>
    static FromJsonObject(const nlohmann::json &jsonObject) {
        return static_cast<int32_t>(jsonObject.template get<uint8_t>());
    }

    template<class T>
    std::enable_if_t<is_uint8_v<T> && !is_pointer_v<T>, void>
    static FromJsonObject(T &object, const nlohmann::json &jsonObject) {
        object = static_cast<int32_t>(jsonObject.template get<uint8_t>());
    }

    /***********************************************************************************
     * object type: int16_t
     ***********************************************************************************/
    template<class T>
    std::enable_if_t<is_int16_v<T> && !is_pointer_v<T>, T>
    static FromJsonObject(const nlohmann::json &jsonObject) {
        return static_cast<int32_t>(jsonObject.template get<int16_t>());
    }

    template<class T>
    std::enable_if_t<is_int16_v<T> && !is_pointer_v<T>, void>
    static FromJsonObject(T &object, const nlohmann::json &jsonObject) {
        object = static_cast<int32_t>(jsonObject.template get<int16_t>());
    }

    /***********************************************************************************
     * object type: uint16_t
     ***********************************************************************************/
    template<class T>
    std::enable_if_t<is_uint16_v<T> && !is_pointer_v<T>, T>
    static FromJsonObject(const nlohmann::json &jsonObject) {
        return static_cast<int32_t>(jsonObject.template get<uint16_t>());
    }

    template<class T>
    std::enable_if_t<is_uint16_v<T> && !is_pointer_v<T>, void>
    static FromJsonObject(T &object, const nlohmann::json &jsonObject) {
        object = static_cast<int32_t>(jsonObject.template get<uint16_t>());
    }

    /***********************************************************************************
     * object type: int32_t
     ***********************************************************************************/
    template<class T>
    std::enable_if_t<is_int32_v<T> && !is_pointer_v<T>, T>
    static FromJsonObject(const nlohmann::json &jsonObject) {
        return static_cast<int32_t>(jsonObject.template get<int32_t>());
    }

    template<class T>
    std::enable_if_t<is_int32_v<T> && !is_pointer_v<T>, void>
    static FromJsonObject(T &object, const nlohmann::json &jsonObject) {
        object = static_cast<int32_t>(jsonObject.template get<int32_t>());
    }

    /***********************************************************************************
     * object type: uint32_t
     ***********************************************************************************/
    template<class T>
    std::enable_if_t<is_uint32_v<T> && !is_pointer_v<T>, T>
    static FromJsonObject(const nlohmann::json &jsonObject) {
        return static_cast<uint32_t>(jsonObject.template get<uint32_t>());
    }

    template<class T>
    std::enable_if_t<is_uint32_v<T> && !is_pointer_v<T>, void>
    static FromJsonObject(T &object, const nlohmann::json &jsonObject) {
        object = static_cast<uint32_t>(jsonObject.template get<uint32_t>());
    }

    /***********************************************************************************
     * object type: int64_t
     ***********************************************************************************/
    template<class T>
    std::enable_if_t<is_int64_v<T> && !is_pointer_v<T>, T>
    static FromJsonObject(const nlohmann::json &jsonObject) {
        return static_cast<int64_t>(jsonObject.template get<int64_t>());
    }

    template<class T>
    std::enable_if_t<is_int64_v<T> && !is_pointer_v<T>, void>
    static FromJsonObject(T &object, const nlohmann::json &jsonObject) {
        object = static_cast<int64_t>(jsonObject.template get<int64_t>());
    }

    /***********************************************************************************
     * object type: uint64_t
     ***********************************************************************************/
    template<class T>
    std::enable_if_t<is_uint64_v<T> && !is_pointer_v<T>, T>
    static FromJsonObject(const nlohmann::json &jsonObject) {
        return static_cast<uint64_t>(jsonObject.template get<uint64_t>());
    }

    template<class T>
    std::enable_if_t<is_uint64_v<T> && !is_pointer_v<T>, void>
    static FromJsonObject(T &object, const nlohmann::json &jsonObject) {
        object = static_cast<uint64_t>(jsonObject.template get<uint64_t>());
    }

    /***********************************************************************************
     * object type: float
     ***********************************************************************************/
    template<class T>
    std::enable_if_t<is_float_v<T> && !is_pointer_v<T>, T>
    static FromJsonObject(const nlohmann::json &jsonObject) {
        return static_cast<double_t>(jsonObject.template get<float_t>());
    }

    template<class T>
    std::enable_if_t<is_float_v<T> && !is_pointer_v<T>, void>
    static FromJsonObject(T &object, const nlohmann::json &jsonObject) {
        object = static_cast<double_t>(jsonObject.template get<float_t>());
    }

    /***********************************************************************************
    * object type: double
    ***********************************************************************************/
    template<class T>
    std::enable_if_t<is_double_v<T> && !is_pointer_v<T>, T>
    static FromJsonObject(const nlohmann::json &jsonObject) {
        return static_cast<double_t>(jsonObject.template get<double_t>());
    }

    template<class T>
    std::enable_if_t<is_double_v<T> && !is_pointer_v<T>, void>
    static FromJsonObject(T &object, const nlohmann::json &jsonObject) {
        object = static_cast<double_t>(jsonObject.template get<double_t>());
    }

    /***********************************************************************************
     * object type: long double
     ***********************************************************************************/
    template<class T>
    std::enable_if_t<is_long_double_v<T> && !is_pointer_v<T>, T>
    static FromJsonObject(const nlohmann::json &jsonObject) {
        return static_cast<double_t>(jsonObject.template get<long double>());
    }

    template<class T>
    std::enable_if_t<is_long_double_v<T> && !is_pointer_v<T>, void>
    static FromJsonObject(T &object, const nlohmann::json &jsonObject) {
        object = static_cast<double_t>(jsonObject.template get<long double>());
    }

    /***********************************************************************************
     * object type: std::string
     ***********************************************************************************/
    template<class T>
    std::enable_if_t<is_string_v<T> && !is_pointer_v<T>, T>
    static FromJsonObject(const nlohmann::json &jsonObject) {
        return jsonObject.template get<std::string>();
    }

    template<class T>
    std::enable_if_t<is_string_v<T> && !is_pointer_v<T>, void>
    static FromJsonObject(T &object, const nlohmann::json &jsonObject) {
        object = jsonObject.template get<std::string>();
    }


    /***********************************************************************************
     * object type: custom class
     ***********************************************************************************/
    template<class T>
    std::enable_if_t<is_class_v<T> && !is_pointer_v<T>, T>
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
    std::enable_if_t<is_class_v<T> && !is_pointer_v<T>, void>
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
    std::enable_if_t<is_vector_v<T> && !is_pointer_v<T>, T>
    static FromJsonObject(const nlohmann::json &jsonObject) {
        using Type = remove_all_cvrp_t<T>;
        typedef typename Type::value_type ValueType;

        Type vec = Type();

        for (const auto &arrItem: jsonObject) {
            //ValueType var = FromJsonObject<ValueType>(arrItem);
            vec.push_back(FromJsonObject<ValueType>(arrItem));
        }
        return vec;
    }

    template<class T>
    std::enable_if_t<is_vector_v<T> && !is_pointer_v<T>, void>
    static FromJsonObject(T &object, const nlohmann::json &jsonObject) {
        using Type = remove_all_cvrp_t<T>;
        typedef typename Type::value_type ValueType;

        for (const auto &arrItem: jsonObject) {
            //ValueType var = FromJsonObject<ValueType>(arrItem);
            object.push_back(FromJsonObject<ValueType>(arrItem));
        }
    }

    /***********************************************************************************
     * object type: Pointer
     ***********************************************************************************/
    template<class T>
    std::enable_if_t<is_pointer_v<T> && is_pointer_v<remove_all_cvr_single_p_t<T>>, T>
    static FromJsonObject(const nlohmann::json &jsonObject) {
        using Pointer = remove_all_cvr_t<T>;
        using Type = remove_all_cvr_single_p_t<Pointer>;
        Pointer p = new Type();
        *p = FromJsonObject<Type>(jsonObject);
        return p;
    }

    template<class T>
    std::enable_if_t<is_pointer_v<T> && !is_pointer_v<remove_all_cvr_single_p_t<T>>, T>
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
    std::enable_if_t<is_pointer_v<T>, T>
    static FromJsonObject(const nlohmann::json &jsonArray, size_t length) {
        using Pointer = remove_all_cvr_t<T>;
        using Type = remove_all_cvr_single_p_t<Pointer>;
        Pointer array = new Type[length];
        for (size_t i = 0; i < length; ++i) {
            array[i] = FromJsonObject<Type>(jsonArray[i]);
        }
        return array;
    }

    /***********************************************************************************
    * object type: std::unique_ptr<T>
    ***********************************************************************************/
    template<class T>
    std::enable_if_t<is_unique_ptr_v<T>, T>
    static FromJsonObject(const nlohmann::json &jsonObject) {
        using Type = unique_ptr_value_type_t<T>;
        std::unique_ptr<Type> var = std::make_unique<Type>();
        FromJsonObject(*var.get(), jsonObject);
        return std::move(var);
    }

    /***********************************************************************************
    * object type: std::shared_ptr<T>
    ***********************************************************************************/
    template<class T>
    std::enable_if_t<is_shared_ptr_v<T>, T>
    static FromJsonObject(const nlohmann::json &jsonObject) {
        using Type = shared_ptr_value_type_t<T>;
        std::shared_ptr<Type> var = std::make_shared<Type>();
        FromJsonObject(*var.get(), jsonObject);
        return var;
    }

    /***********************************************************************************
    * object type: std::map
    ***********************************************************************************/
    template<class T>
    std::enable_if_t<is_map_v<T>, void>
    static FromJsonObject(T &mapObj, const nlohmann::json &jsonObject) {
        using KeyType = map_key_type_t<T>;
        using ValueType = map_value_type_t<T>;

        KeyType keyObj = KeyType();
        ValueType valueObj = ValueType();

        auto itr = jsonObject.begin();
        while (itr != jsonObject.end()) {
            // TODO: will work if key is an object type (rather than string or primitive type)
            nlohmann::json keyJson= itr.key();
            FromJsonObject<KeyType>(keyObj, keyJson);

            nlohmann::json valueJson = itr.value();
            FromJsonObject<ValueType>(valueObj, valueJson);

            mapObj.insert(std::pair<KeyType , ValueType>(keyJson, valueObj));
            ++itr;
        }
    }

    template<class T>
    std::enable_if_t<is_map_v<T>, T>
    static FromJsonObject(const nlohmann::json &jsonObject) {
        T mapObj;
        FromJsonObject<T>(mapObj, jsonObject);
        return mapObj;
    }
}

#endif //OPEN_JSON_DESERIALIZER_H
