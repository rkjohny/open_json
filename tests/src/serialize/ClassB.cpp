#include <gtest/gtest.h>
#include <string>
#include "../../../include/open_json.h"

namespace open_json_test::serialize {

    class SerializeClassB : public open_json::Serializable {
    private:
        int id = 100;
        std::string name = "Rezaul karim";

    public:
        SerializeClassB() = default;

        int GetId() const {
            return id;
        }

        const std::string &GetName() const {
            return name;
        }

        [[nodiscard]]
        const nlohmann::json ToJson() override {
            return open_json::serializer::ToJsonObject(this);
        }

        REGISTER_GETTER_INCLUDING_BASE_START(open_json::Serializable)
        GETTER(SerializeClassB, int, "id", &SerializeClassB::GetId),
        GETTER(SerializeClassB, const std::string&, "name", &SerializeClassB::GetName)
        REGISTER_GETTER_INCLUDING_BASE_END
    };

    TEST(SerializeClassB, Test) {
        SerializeClassB b;
        nlohmann::json jsonObject = b.ToJson();

        ASSERT_EQ(b.GetId(), jsonObject.at("id").template get<int>());
        ASSERT_EQ(0, b.GetName().compare(jsonObject.at("name").template get<std::string>()));
    }
}