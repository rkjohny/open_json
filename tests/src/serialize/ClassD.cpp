#include <gtest/gtest.h>
#include <string>
#include "../../../include/open_json.h"

namespace open_json_test::serialize {

    class SerializeClassD : public open_json::Serializable {
    private:
        int id = 100;
        std::string name = "Rezaul karim";

    public:
        SerializeClassD() = default;

        int GetId() const {
            return id;
        }

        const std::string &GetName() const {
            return name;
        }


        REGISTER_GETTER_START
        GETTER(SerializeClassD, int, "id", &SerializeClassD::GetId),
        GETTER(SerializeClassD, const std::string&, "name", &SerializeClassD::GetName)
        REGISTER_GETTER_END
    };

    TEST(SerializeClassD, Test) {
        SerializeClassD b;
        nlohmann::json jsonObject = open_json::ToJson(b);

        ASSERT_EQ(b.GetId(), jsonObject.at("id").template get<int>());
        ASSERT_EQ(0, b.GetName().compare(jsonObject.at("name").template get<std::string>()));
    }
}