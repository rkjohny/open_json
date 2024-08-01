#include <gtest/gtest.h>
#include <string>
#include "../../../include/open_json.h"

namespace open_json_test::serialize::shared_ptr {

    class SerializeWeakPtr {
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
        GETTER(SerializeWeakPtr, int, "id", &SerializeWeakPtr::GetId),
        GETTER(SerializeWeakPtr, const std::string&, "name", &SerializeWeakPtr::GetName)
        REGISTER_GETTER_END
    };

    TEST(SerializeWeakPtr, Serialize) {

        std::shared_ptr<SerializeWeakPtr> sp = std::make_shared<SerializeWeakPtr>();
        sp->SetName("Rezaul Karim");
        sp->SetId(100);

        std::weak_ptr<SerializeWeakPtr> wp = sp;

        nlohmann::json jsonObject = open_json::ToJson(wp);

        ASSERT_TRUE(sp.use_count() == 1);

        ASSERT_EQ(sp->GetId(), jsonObject.at("id").template get<int>());
        ASSERT_EQ(0, sp->GetName().compare(jsonObject.at("name").template get<std::string>()));
    }
}