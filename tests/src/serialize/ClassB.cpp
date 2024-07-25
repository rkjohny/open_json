#include <gtest/gtest.h>
#include <string>
#include "../../../include/open_json.h"

namespace open_json_test::serialize::simple_class {

    class ClassB : public open_json::Serializable {
    private:
        int id = 100;
        std::string name = "Rezaul karim";

    public:
        ClassB() = default;

        int GetId() const {
            return id;
        }

        const std::string &GetName() const {
            return name;
        }


        REGISTER_GETTER_INCLUDING_BASE_START(open_json::Serializable)
        GETTER(ClassB, int, "id", &ClassB::GetId),
        GETTER(ClassB, const std::string&, "name", &ClassB::GetName)
        REGISTER_GETTER_INCLUDING_BASE_END
    };

    TEST(ClassB, Test) {
        ClassB b;
        nlohmann::json jsonObject = open_json::ToJson(b);
        ASSERT_EQ(b.GetId(), jsonObject.at("id").template get<int>());
        ASSERT_EQ(0, b.GetName().compare(jsonObject.at("name").template get<std::string>()));

        ClassB *p = new ClassB();
        jsonObject = open_json::ToJson(p);
        ASSERT_EQ(p->GetId(), jsonObject.at("id").template get<int>());
        ASSERT_EQ(0, p->GetName().compare(jsonObject.at("name").template get<std::string>()));
        delete p;

        ClassB **pp = new ClassB*(new ClassB());
        jsonObject = open_json::ToJson(pp);
        ASSERT_EQ((*pp)->GetId(), jsonObject.at("id").template get<int>());
        ASSERT_EQ(0, (*pp)->GetName().compare(jsonObject.at("name").template get<std::string>()));
        delete *pp;
        delete pp;
    }
}