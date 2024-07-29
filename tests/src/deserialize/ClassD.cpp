#include <gtest/gtest.h>
#include <string>
#include "../../include/CommonDef.h"
#include "../../../include/open_json.h"

namespace open_json_test::deserialize::simple_class {

    class ClassD {
    private:
        int *id;
        std::string *name;
        int *code;
        int **age;

    public:
        virtual ~ClassD() {
            delete id;
            delete name;
            delete code;
            delete *age;
            delete age;
        }

        int* GetId() const {
            return id;
        }

        const std::string *GetName() const {
            return name;
        }

        void SetId(const int *id) {
            this->id = const_cast<int*>(id);
        }

        void SetName(const std::string *name) {
            this->name = const_cast<std::string*>(name);
        }

        int *GetCode() const {
            return code;
        }

        void SetCode(const int *c) {
            code = const_cast<int*>(c);
        }

        int **GetAge() const {
            return age;
        }

        void SetAge(const int * const * a) {
            age = const_cast<int **>(a);
        }

        REGISTER_SETTER_START
        SETTER(ClassD, const int*, "id", &ClassD::SetId),
        SETTER(ClassD, const std::string*, "name", &ClassD::SetName),
        SETTER(ClassD, const int *, "code", &ClassD::SetCode),
        SETTER(ClassD, const int * const*, "age", &ClassD::SetAge)
        REGISTER_GETTER_END
    };

    TEST(ClassD, Test) {
        nlohmann::json jsonObject = nlohmann::json::object();
        jsonObject["id"] = 200;
        jsonObject["name"] = "David Jonson";
        jsonObject["code"] = 100;
        jsonObject["age"] = 50;

        ClassD a = open_json::FromJson<ClassD>(jsonObject);
        ASSERT_EQ(jsonObject.at("id").template get<int>(), *a.GetId());
        ASSERT_EQ(0, jsonObject.at("name").template get<std::string>().compare(*a.GetName()));
        ASSERT_EQ(100, *a.GetCode());
        ASSERT_EQ(50, **a.GetAge());

        ClassD *p = open_json::FromJson<ClassD*>(jsonObject);
        ASSERT_EQ(jsonObject.at("id").template get<int>(), *p->GetId());
        ASSERT_EQ(0, jsonObject.at("name").template get<std::string>().compare(*p->GetName()));
        ASSERT_EQ(100, *p->GetCode());
        ASSERT_EQ(50, **p->GetAge());
        delete p;

        ClassD **pp = open_json::FromJson<ClassD**>(jsonObject);
        ASSERT_EQ(jsonObject.at("id").template get<int>(), *(*pp)->GetId());
        ASSERT_EQ(0, jsonObject.at("name").template get<std::string>().compare(*(*pp)->GetName()));
        ASSERT_EQ(100, *(*pp)->GetCode());
        ASSERT_EQ(50, **(*pp)->GetAge());
        delete *pp;
        delete pp;
    }
}