#ifndef OPEN_JSON_OPEN_JSON_H
#define OPEN_JSON_OPEN_JSON_H


#include "string"
#include "gsl/gsl"
#include "nlohmann/json.hpp"
#include "Deserializer.h"


namespace open_json {

    /************************** Serializing to Json String *************************/
    template<class T>
    [[nodiscard]]
    static std::string ToJson(gsl::not_null<const T &&> object) {
//        auto jsonObject = Serializer::ToJson(std::move(object))
//        return jsonObject.dump();
    }

    template<class T>
    [[nodiscard]]
    static std::string ToJson(gsl::not_null<const T &> object) {
//        auto jsonObject = Serializer::ToJson(std::move(object))
//        return jsonObject.dump();
    }

    template<class T>
    [[nodiscard]]
    static std::string ToJson(gsl::not_null<const T *> object) {
//        auto jsonObject = Serializer::ToJson(std::move(object))
//        return jsonObject.dump();
    }

    template<class T>
    [[nodiscard]]
    static std::string ToJson(gsl::not_null<const T *const *> object) {
//        auto jsonObject = Serializer::ToJson(std::move(object))
//        return jsonObject.dump();
    }


    /************************** Deserializing to CPP object from Json String *************************/
    template<class T>
    static void FromJson(gsl::not_null<T &> object, const std::string &jsonString) {
        auto jsonObject = nlohmann::json::parse(jsonString);
        Deserializer::FromJson(object, jsonObject);
    }

    template<class T>
    static void FromJson(gsl::not_null<T *> object, const std::string &jsonString) {
        auto jsonObject = nlohmann::json::parse(jsonString);
        Deserializer::FromJson(object, jsonObject);
    }

    template<class T>
    static void FromJson(gsl::not_null<T **> object, const std::string &jsonString) {
        auto jsonObject = nlohmann::json::parse(jsonString);
        Deserializer::FromJson(object, jsonObject);
    }
}

#endif //OPEN_JSON_OPEN_JSON_H
