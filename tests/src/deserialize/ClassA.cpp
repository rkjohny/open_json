#include <gtest/gtest.h>
#include <string>
#include "../../../include/open_json.h"

namespace open_json_test::deserialize {

    class DeserializeClassA {
    private:
        int id = 100;
        std::string name = "Rezaul karim";

    public:
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

        REGISTER_SETTER_START
        SETTER(DeserializeClassA, const int, "id", &DeserializeClassA::SetId),
        SETTER(DeserializeClassA, const std::string&, "name", &DeserializeClassA::SetName)
        REGISTER_GETTER_END
    };

    TEST(DeserializeClassA, Test) {
        nlohmann::json jsonObject = nlohmann::json::object();
        jsonObject["id"] = 200;
        jsonObject["name"] = "David Jonson";

        DeserializeClassA a = open_json::FromJson<DeserializeClassA>(jsonObject);
        ASSERT_EQ(jsonObject.at("id").template get<int>(), a.GetId());
        ASSERT_EQ(0, jsonObject.at("name").template get<std::string>().compare(a.GetName()));
    }
}