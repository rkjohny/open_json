#ifndef OPEN_JSON_SERIALIZABLE_H
#define OPEN_JSON_SERIALIZABLE_H

#include <nlohmann/json.hpp>
#include "AbstractSerializable.h"
#include "Serializer.h"
#include "Deserializer.h"

namespace open_json {

    template<class T>
    class Serializable : public AbstractSerializable {
    public:
        Serializable() = default;

        virtual ~Serializable() = default;

        [[nodiscard]]
        const nlohmann::json ToJson() override {
            return  serializer::ToJson<T>(reinterpret_cast<const T *>(this));
        }

        void FromJson(const nlohmann::json &jsonObject) override {
            deserializer::FromJson<T>(reinterpret_cast<T *> (this), jsonObject);
        }


        REGISTER_GETTER_INCLUDING_BASE_START(AbstractSerializable)
        REGISTER_GETTER_INCLUDING_BASE_END

        REGISTER_SETTER_INCLUDING_BASE_START(AbstractSerializable)
        REGISTER_SETTER_INCLUDING_BASE_END
    };

}

#endif //OPEN_JSON_SERIALIZABLE_H
