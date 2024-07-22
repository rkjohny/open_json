#include <gtest/gtest.h>
#include <string>
#include "../../../include/open_json.h"

namespace open_json_test {

    class ClassC {
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

        static constexpr std::tuple getters = std::make_tuple(
                open_json::Getter<ClassC, int>(&ClassC::GetId, "id"),
                open_json::Getter<ClassC, const std::string &>(&ClassC::GetName, "name")
        );
    };

    TEST(ClassC, Test) {
    ClassC c;
    nlohmann::json jsonObject = open_json::ToJson(c);

    ASSERT_EQ(c.GetId(), jsonObject.at("id").template get<int>());
    ASSERT_EQ(0, c.GetName().compare(jsonObject.at("name").template get<std::string>()));
}
}