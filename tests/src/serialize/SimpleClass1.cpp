#include <gtest/gtest.h>
#include <string>
#include "../../../include/open_json.h"

namespace open_json_test::serialize::simple_class {

    class SimpleClass1 {
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
        GETTER(SimpleClass1, int, "id", &SimpleClass1::GetId),
        GETTER(SimpleClass1, const std::string&, "name", &SimpleClass1::GetName)
        REGISTER_GETTER_END
    };

    TEST(SimpleClass1, Serialize) {
        SimpleClass1 a;
        nlohmann::json jsonObject = open_json::ToJson(a);
        ASSERT_EQ(a.GetId(), jsonObject.at("id").template get<int>());
        ASSERT_EQ(0, a.GetName().compare(jsonObject.at("name").template get<std::string>()));

        SimpleClass1 *p = new SimpleClass1();
        jsonObject = open_json::ToJson(p);
        ASSERT_EQ(p->GetId(), jsonObject.at("id").template get<int>());
        ASSERT_EQ(0, p->GetName().compare(jsonObject.at("name").template get<std::string>()));
        delete p;

        SimpleClass1 **pp = new SimpleClass1*(new SimpleClass1());
        jsonObject = open_json::ToJson(pp);
        ASSERT_EQ((*pp)->GetId(), jsonObject.at("id").template get<int>());
        ASSERT_EQ(0, (*pp)->GetName().compare(jsonObject.at("name").template get<std::string>()));
        delete *pp;
        delete pp;
    }
}