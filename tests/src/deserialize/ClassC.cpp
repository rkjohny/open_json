#include <gtest/gtest.h>
#include <string>
#include "../../../include/open_json.h"

namespace open_json_test::deserialize::simple_class {

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

        void SetId(int &id) {
            this->id = id;
        }

        void SetName(std::string name) {
            this->name = name;
        }

        static constexpr std::tuple setters = std::make_tuple(
                open_json::Setter<ClassC, int &>(&ClassC::SetId, "id"),
                open_json::Setter<ClassC, std::string>(&ClassC::SetName, "name")
        );
    };

    TEST(ClassC, Test) {
        nlohmann::json jsonObject = nlohmann::json::object();
        jsonObject["id"] = 300;
        jsonObject["name"] = "David Backham";

        ClassC c = open_json::FromJson<ClassC>(jsonObject);
        ASSERT_EQ(jsonObject.at("id").template get<int>(), c.GetId());
        ASSERT_EQ(0, jsonObject.at("name").template get<std::string>().compare(c.GetName()));

        ClassC *p = open_json::FromJson<ClassC*>(jsonObject);
        ASSERT_EQ(jsonObject.at("id").template get<int>(), p->GetId());
        ASSERT_EQ(0, jsonObject.at("name").template get<std::string>().compare(p->GetName()));
        delete p;

        ClassC **pp = open_json::FromJson<ClassC**>(jsonObject);
        ASSERT_EQ(jsonObject.at("id").template get<int>(), (*pp)->GetId());
        ASSERT_EQ(0, jsonObject.at("name").template get<std::string>().compare((*pp)->GetName()));
        delete *pp;
        delete pp;
    }
}