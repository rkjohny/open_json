#include <gtest/gtest.h>
#include <string>
#include "../../include/CommonDef.h"
#include "../../../include/open_json.h"

namespace open_json_test::deserialize::simple_class {

    class ClassD {
    private:
        int id;
        std::string name;
        int *code;

    public:
        ClassD() {
            std::cout << "inside ClassD()" << std::endl;
            id = 100;
            name = "Rezaul karim";
        }

        virtual ~ClassD() {
            delete code;
        }

        ClassD(ClassD &obj) {
            std::cout << "inside ClassD(ClassD &obj)" << std::endl;
            id = obj.id;
            name = obj.name;
            code = new int();
            *code = *obj.code;
        }

        ClassD(ClassD &&obj) {
            std::cout << "inside ClassD(ClassD &&obj)" << std::endl;
            id = std::move(obj.id);
            name = std::move(obj.name);
            code = new int();
            *code = std::move(*obj.code);
        }

        ClassD& operator=(ClassD &obj) {
            std::cout << "inside ClassD& operator=(ClassD &obj)" << std::endl;
            id = obj.id;
            name = obj.name;
            code = new int();
            *code = *obj.code;
            return *this;
        }

        ClassD& operator=(ClassD &&obj) {
            std::cout << "inside ClassD& operator=(ClassD &&obj)" << std::endl;
            id = std::move(obj.id);
            name = std::move(obj.name);
            code = new int();
            *code = std::move(*obj.code);
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

        int *GetCode() const {
            return code;
        }

        void SetCode(int *c) {
            code = c;
        }

        REGISTER_SETTER_START
        SETTER(ClassD, const int, "id", &ClassD::SetId),
        SETTER(ClassD, const std::string&, "name", &ClassD::SetName),
        SETTER(ClassD, int *, "code", &ClassD::SetCode)
        REGISTER_GETTER_END
    };

    TEST(ClassD, Test) {
        nlohmann::json jsonObject = nlohmann::json::object();
        jsonObject["id"] = 200;
        jsonObject["name"] = "David Jonson";
        jsonObject["code"] = 100;

        ClassD a = open_json::FromJson<ClassD>(jsonObject);
        ASSERT_EQ(jsonObject.at("id").template get<int>(), a.GetId());
        ASSERT_EQ(0, jsonObject.at("name").template get<std::string>().compare(a.GetName()));
        ASSERT_EQ(100, *a.GetCode());

        ClassD *p = open_json::FromJson<ClassD*>(jsonObject);
        ASSERT_EQ(jsonObject.at("id").template get<int>(), p->GetId());
        ASSERT_EQ(0, jsonObject.at("name").template get<std::string>().compare(p->GetName()));
        ASSERT_EQ(100, *p->GetCode());
        delete p;

        ClassD **pp = open_json::FromJson<ClassD**>(jsonObject);
        ASSERT_EQ(jsonObject.at("id").template get<int>(), (*pp)->GetId());
        ASSERT_EQ(0, jsonObject.at("name").template get<std::string>().compare((*pp)->GetName()));
        ASSERT_EQ(100, *(*pp)->GetCode());
        delete *pp;
        delete pp;
    }
}