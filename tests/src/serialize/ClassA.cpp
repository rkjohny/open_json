#include <gtest/gtest.h>
#include <string>
#include "../../../include/open_json.h"

namespace open_json_test::serialize {

    class SerializeClassA {
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

        REGISTER_GETTER_START
        GETTER(SerializeClassA, int, "id", &SerializeClassA::GetId),
        GETTER(SerializeClassA, const std::string&, "name", &SerializeClassA::GetName)
        REGISTER_GETTER_END
    };

    TEST(SerializeClassA, Serialize) {
        SerializeClassA a;
        nlohmann::json jsonObject = open_json::ToJson(a);

        ASSERT_EQ(a.GetId(), jsonObject.at("id").template get<int>());
        ASSERT_EQ(0, a.GetName().compare(jsonObject.at("name").template get<std::string>()));
    }
}