#include <gtest/gtest.h>
#include <string>
#include "../../../include/open_json.h"

namespace open_json_test {

    class ClassD : public open_json::Serializable {
    private:
        int id = 100;
        std::string name = "Rezaul karim";

    public:
        ClassD() = default;

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

        REGISTER_GETTER_START
        GETTER(ClassD, int, "id", &ClassD::GetId),
        GETTER(ClassD, const std::string&, "name", &ClassD::GetName)
        REGISTER_GETTER_END
    };

    TEST(ClassD, Test) {
        ClassD b;
        nlohmann::json jsonObject = b.ToJson();

        ASSERT_EQ(b.GetId(), jsonObject.at("id").template get<int>());
        ASSERT_EQ(0, b.GetName().compare(jsonObject.at("name").template get<std::string>()));
    }
}