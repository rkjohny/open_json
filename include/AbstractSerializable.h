
#ifndef OPEN_JSON_ABSTRACTSERIALIZABLE_H
#define OPEN_JSON_ABSTRACTSERIALIZABLE_H

#include <nlohmann/json.hpp>
#include "GetterSetterDef.h"


namespace open_json {

    class AbstractSerializable {
    public:
        AbstractSerializable() = default;

        virtual ~AbstractSerializable() = default;

        [[nodiscard]]
        virtual const std::string ToJson() = 0;


        virtual void FromJson(const std::string &) = 0;


        REGISTER_GETTER_START
        REGISTER_GETTER_END

        REGISTER_SETTER_START
        REGISTER_SETTER_END
    };

}

#endif //OPEN_JSON_ABSTRACTSERIALIZABLE_H
