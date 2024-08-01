#include <gtest/gtest.h>
#include <nlohmann/json.hpp>
#include <string>
#include "../../../include/open_json.h"

namespace open_json_test::deserialize::rvalue_reference {
    class RvalueReference {
    public:
        // Using default copy_constructor, move_constructor, copy_assignment and move_assignment operator

        int id;
        std::string name;

        void SetId(int &&id) {
            this->id = std::move(id);
        }

        void SetName(std::string &&name) {
            this->name = std::move(name);
        }

        REGISTER_SETTER_START
        SETTER(RvalueReference, int &&, "id", &RvalueReference::SetId),
        SETTER(RvalueReference, std::string &&, "name", &RvalueReference::SetName)
        REGISTER_SETTER_END
    };

    TEST(RvalueReferenceTest, TestDeserialize) {
        nlohmann::json jsonObject = nlohmann::json::object();
        jsonObject["id"] = 10;
        jsonObject["name"] = "Rezaul Karim";

        RvalueReference obj = open_json::FromJson<RvalueReference>(jsonObject);
        ASSERT_TRUE(obj.id == 10);
        ASSERT_TRUE(obj.name.compare("Rezaul Karim") == 0);
    }
}
