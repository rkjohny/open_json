#ifndef OPEN_JSON_SERIALIZABLE_H
#define OPEN_JSON_SERIALIZABLE_H

#include <nlohmann/json.hpp>
#include "GetterSetterDef.h"

namespace open_json {

    class Serializable {
    public:
        Serializable() = default;

        virtual ~Serializable() = default;

        [[nodiscard]]
        virtual const nlohmann::json ToJson() = 0;

//        virtual void FromJson(const nlohmann::json &) = 0;


        REGISTER_GETTER_START
        REGISTER_GETTER_END

//        REGISTER_SETTER_START
//        REGISTER_SETTER_END
    };

}

#endif //OPEN_JSON_SERIALIZABLE_H
