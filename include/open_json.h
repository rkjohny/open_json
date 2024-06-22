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
    static nlohmann::json ToJson(const T &&object) {
        return  Serializer::ToJson(object);
    }

    template<class T>
    [[nodiscard]]
    static nlohmann::json ToJson(const T &object) {
        return Serializer::ToJson(object);
    }

    template<class T>
    [[nodiscard]]
    static nlohmann::json ToJson(const T *object) {
        return Serializer::ToJson(object);
    }

    template<class T>
    [[nodiscard]]
    static nlohmann::json ToJson(const T *const *object) {
        return Serializer::ToJson(object);
    }


    /************************** Deserializing to CPP object from Json String *************************/

    /*

    template<class T>
    static void FromJson(T &object, const std::string &jsonString) {
        auto jsonObject = nlohmann::json::parse(jsonString);
        Deserializer::FromJson(object, jsonObject);
    }

    template<class T>
    static void FromJson(const T *object, const std::string &jsonString) {
        //static_assert(object == nullptr, "Argument cannot be null");
        auto jsonObject = nlohmann::json::parse(jsonString);
        Deserializer::FromJson(object, jsonObject);
    }

    template<class T>
    static void FromJson(const T *const *object, const std::string &jsonString) {
        //static_assert(object == nullptr, "Argument cannot be null");
        //static_assert(*object == nullptr, "Argument cannot be null");
        auto jsonObject = nlohmann::json::parse(jsonString);
        Deserializer::FromJson(object, jsonObject);
    }
*/
}

#endif //OPEN_JSON_OPEN_JSON_H
