#include <gtest/gtest.h>
#include <string>
#include "../../../include/open_json.h"

namespace open_json_test::serialize {

    class DeserializeClassB : public open_json::Serializable {
    private:
        int id = 100;
        std::string name = "Rezaul karim";

    public:
        DeserializeClassB() = default;

        int GetId() const {
            return id;
        }

        const std::string &GetName() const {
            return name;
        }

        void SetId(const int id) {
            this->id = id;
        }

        void SetName(const std::string &name) {
            this->name = name;
        }

        REGISTER_GETTER_INCLUDING_BASE_START(open_json::Serializable)
        GETTER(DeserializeClassB, int, "id", &DeserializeClassB::GetId),
        GETTER(DeserializeClassB, const std::string&, "name", &DeserializeClassB::GetName)
        REGISTER_GETTER_INCLUDING_BASE_END


        REGISTER_SETTER_INCLUDING_BASE_START(open_json::Serializable)
        SETTER(DeserializeClassB, const int, "id", &DeserializeClassB::SetId),
        SETTER(DeserializeClassB, const std::string&, "name", &DeserializeClassB::SetName)
        REGISTER_SETTER_INCLUDING_BASE_END
    };

    TEST(DeserializeClassB, Test) {
        DeserializeClassB b;
        nlohmann::json jsonObject = open_json::ToJson(b);

        ASSERT_EQ(b.GetId(), jsonObject.at("id").template get<int>());
        ASSERT_EQ(0, b.GetName().compare(jsonObject.at("name").template get<std::string>()));

        jsonObject = nlohmann::json::object();
        jsonObject["id"] = 200;
        jsonObject["name"] = "David Jonson";

        DeserializeClassB c = open_json::FromJson<DeserializeClassB>(jsonObject);
        ASSERT_EQ(jsonObject.at("id").template get<int>(), c.GetId());
        ASSERT_EQ(0, jsonObject.at("name").template get<std::string>().compare(c.GetName()));
    }
}