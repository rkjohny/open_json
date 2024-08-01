#include <gtest/gtest.h>
#include <string>
#include "../../../include/open_json.h"

namespace open_json_test::serialize::unique_ptr {

    class SerializeUniquePtr {
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

        REGISTER_GETTER_START
        GETTER(SerializeUniquePtr, int, "id", &SerializeUniquePtr::GetId),
        GETTER(SerializeUniquePtr, const std::string&, "name", &SerializeUniquePtr::GetName)
        REGISTER_GETTER_END
    };

    TEST(SerializeUniquePtr, Serialize) {

        std::unique_ptr<SerializeUniquePtr> ptr = std::make_unique<SerializeUniquePtr>();
        ptr->SetName("Rezaul Karim");
        ptr->SetId(100);

        nlohmann::json jsonObject = open_json::ToJson(ptr);

        ASSERT_EQ(ptr->GetId(), jsonObject.at("id").template get<int>());
        ASSERT_EQ(0, ptr->GetName().compare(jsonObject.at("name").template get<std::string>()));
    }
}