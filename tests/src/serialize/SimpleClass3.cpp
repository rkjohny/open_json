#include <gtest/gtest.h>
#include <string>
#include "../../../include/open_json.h"

namespace open_json_test::serialize::simple_class {

    class SimpleClass3 {
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
                open_json::Getter<SimpleClass3, int>(&SimpleClass3::GetId, "id"),
                open_json::Getter<SimpleClass3, const std::string &>(&SimpleClass3::GetName, "name")
        );
    };

    TEST(SimpleClass3, Test) {
        SimpleClass3 c;
        nlohmann::json jsonObject = open_json::ToJson(c);
        ASSERT_EQ(c.GetId(), jsonObject.at("id").template get<int>());
        ASSERT_EQ(0, c.GetName().compare(jsonObject.at("name").template get<std::string>()));

        SimpleClass3 *p = new SimpleClass3();
        jsonObject = open_json::ToJson(p);
        ASSERT_EQ(p->GetId(), jsonObject.at("id").template get<int>());
        ASSERT_EQ(0, p->GetName().compare(jsonObject.at("name").template get<std::string>()));
        delete p;

        SimpleClass3 **pp = new SimpleClass3 *(new SimpleClass3());
        jsonObject = open_json::ToJson(pp);
        ASSERT_EQ((*pp)->GetId(), jsonObject.at("id").template get<int>());
        ASSERT_EQ(0, (*pp)->GetName().compare(jsonObject.at("name").template get<std::string>()));
        delete *pp;
        delete pp;
    }
}