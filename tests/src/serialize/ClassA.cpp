#include <gtest/gtest.h>
#include <string>
#include "../../../include/open_json.h"

namespace open_json_test::serialize::simple_class {

    class ClassA {
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
        GETTER(ClassA, int, "id", &ClassA::GetId),
        GETTER(ClassA, const std::string&, "name", &ClassA::GetName)
        REGISTER_GETTER_END
    };

    TEST(ClassA, Serialize) {
        ClassA a;
        nlohmann::json jsonObject = open_json::ToJson(a);
        ASSERT_EQ(a.GetId(), jsonObject.at("id").template get<int>());
        ASSERT_EQ(0, a.GetName().compare(jsonObject.at("name").template get<std::string>()));

        ClassA *p = new ClassA();
        jsonObject = open_json::ToJson(p);
        ASSERT_EQ(p->GetId(), jsonObject.at("id").template get<int>());
        ASSERT_EQ(0, p->GetName().compare(jsonObject.at("name").template get<std::string>()));
        delete p;

        ClassA **pp = new ClassA*(new ClassA());
        jsonObject = open_json::ToJson(pp);
        ASSERT_EQ((*pp)->GetId(), jsonObject.at("id").template get<int>());
        ASSERT_EQ(0, (*pp)->GetName().compare(jsonObject.at("name").template get<std::string>()));
        delete *pp;
        delete pp;
    }
}