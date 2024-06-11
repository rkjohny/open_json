#ifndef OPEN_JSON_OPEN_JSON_H
#define OPEN_JSON_OPEN_JSON_H


#include "string"
#include "nlohmann/json.hpp"

/** include all header file to support single file include **/
#include "CommonDef.h"
#include "StringUtils.h"
#include "TypeTraits.h"
#include "GetterSetterDef.h"
#include "Getter.h"
#include "Setter.h"
#include "Deserializer.h"
#include "Serializer.h"
#include "Serializable.h"
#include "SOFactory.h"
/** end of include of all header file **/


namespace open_json {

    /************************** Serializing to Json String *************************/
    template<class T>
    [[nodiscard]]
    static std::string ToJson(const T &&object) {
        auto jsonObject = Serializer::ToJson(object);
        return jsonObject.dump();
    }

    template<class T>
    [[nodiscard]]
    static std::string ToJson(const T &object) {
        auto jsonObject = Serializer::ToJson(object);
        return jsonObject.dump();
    }

    template<class T>
    [[nodiscard]]
    static std::string ToJson(const T *object) {
        static_assert(object == nullptr, "Argument cannot be null");
        auto jsonObject = Serializer::ToJson(object);
        return jsonObject.dump();
    }

    template<class T>
    [[nodiscard]]
    static std::string ToJson(const T *const *object) {
        static_assert(object == nullptr, "Argument cannot be null");
        //static_assert(*object == nullptr, "Argument cannot be null");
        auto jsonObject = Serializer::ToJson(object);
        return jsonObject.dump();
    }


    /************************** Deserializing to CPP object from Json String *************************/
    template<class T>
    static void FromJson(T &object, const std::string &jsonString) {
        auto jsonObject = nlohmann::json::parse(jsonString);
        Deserializer::FromJson(object, jsonObject);
    }

    template<class T>
    static void FromJson(const T *object, const std::string &jsonString) {
        static_assert(object == nullptr, "Argument cannot be null");
        auto jsonObject = nlohmann::json::parse(jsonString);
        Deserializer::FromJson(object, jsonObject);
    }

    template<class T>
    static void FromJson(const T *const *object, const std::string &jsonString) {
        static_assert(object == nullptr, "Argument cannot be null");
        //static_assert(*object == nullptr, "Argument cannot be null");
        auto jsonObject = nlohmann::json::parse(jsonString);
        Deserializer::FromJson(object, jsonObject);
    }
}

#endif //OPEN_JSON_OPEN_JSON_H
