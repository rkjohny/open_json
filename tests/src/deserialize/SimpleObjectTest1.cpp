#include <gtest/gtest.h>
#include <string>
#include "../../include/CommonDef.h"
#include "../../../include/open_json.h"

namespace open_json_test::deserialize::simple_class1 {

    class ClassA {
    private:
        int id;
        std::string name;

    public:
        ClassA() = default;

        virtual ~ClassA() = default;

        ClassA(const ClassA &obj) {
            this->id = obj.id;
            this->name = obj.name;
        }

        ClassA(ClassA &&obj) {
            this->id = std::move(obj.id);
            this->name = std::move(obj.name);
        }

        ClassA &operator=(const ClassA &obj) {
            this->id = obj.id;
            this->name = obj.name;
            return *this;
        }

        ClassA &operator=(const ClassA &&obj) {
            this->id = std::move(obj.id);
            this->name = std::move(obj.name);
            return *this;
        }

        int GetId() const {
            return id;
        }

        const std::string &GetName() const {
            return name;
        }

        void SetId(const int id) {
            this->id = id;
        }

        void SetName(const std::string &name) {
            this->name = name;
        }

        REGISTER_SETTER_START
        SETTER(ClassA, const int, "id", &ClassA::SetId),
        SETTER(ClassA, const std::string&, "name", &ClassA::SetName)
        REGISTER_GETTER_END
    };

    TEST(SimpleObjectTest1, Test) {
        nlohmann::json jsonObject = nlohmann::json::object();
        jsonObject["id"] = 200;
        jsonObject["name"] = "David Jonson";

        ClassA a = open_json::FromJson<ClassA>(jsonObject);
        ASSERT_EQ(jsonObject.at("id").template get<int>(), a.GetId());
        ASSERT_EQ(0, jsonObject.at("name").template get<std::string>().compare(a.GetName()));

        ClassA *p = open_json::FromJson<ClassA *>(jsonObject);
        ASSERT_EQ(jsonObject.at("id").template get<int>(), p->GetId());
        ASSERT_EQ(0, jsonObject.at("name").template get<std::string>().compare(p->GetName()));
        delete p;

        ClassA **pp = open_json::FromJson<ClassA **>(jsonObject);
        ASSERT_EQ(jsonObject.at("id").template get<int>(), (*pp)->GetId());
        ASSERT_EQ(0, jsonObject.at("name").template get<std::string>().compare((*pp)->GetName()));
        delete *pp;
        delete pp;
    }
}