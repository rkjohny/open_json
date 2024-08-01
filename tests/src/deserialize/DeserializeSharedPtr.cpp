#include <gtest/gtest.h>
#include <string>
#include "../../../include/open_json.h"

namespace open_json_test::deserialize::unique_ptr {

    class DeserializeSharedPtr {
    private:
        int id;
        std::string name;

    public:
        int GetId() const {
            return id;
        }

        void SetId(const int &id) {
            this->id = id;
        }

        const std::string &GetName() const {
            return name;
        }

        void SetName(const std::string &name) {
            this->name = name;
        }

        REGISTER_SETTER_START
        SETTER(DeserializeSharedPtr, const int&, "id", &DeserializeSharedPtr::SetId),
        SETTER(DeserializeSharedPtr, const std::string&, "name", &DeserializeSharedPtr::SetName)
        REGISTER_SETTER_END
    };

    TEST(DeserializeSharedPtr, Serialize) {
        nlohmann::json jsonObject;

        jsonObject["id"] = 100;
        jsonObject["name"] = "Rezaul karim";

        std::shared_ptr<DeserializeSharedPtr> ptr = open_json::FromJson<std::shared_ptr<DeserializeSharedPtr>>(jsonObject);

        ASSERT_EQ(ptr->GetId(), jsonObject.at("id").template get<int>());
        ASSERT_EQ(0, ptr->GetName().compare(jsonObject.at("name").template get<std::string>()));
    }
}