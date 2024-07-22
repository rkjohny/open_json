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
    template<class T>
    [[nodiscard]]
    static nlohmann::json ToJson(const T &object);

    template<class T>
    [[nodiscard]]
    static nlohmann::json ToJson(const T &object) {
        return serializer::ToJsonObject(object);
    }

//    template<class T>
//    static void FromJson(T &object, const nlohmann::json &jsonObject) {
//        deserializer::FromJson(object, jsonObject);
//    }
}

#endif //OPEN_JSON_OPEN_JSON_H
