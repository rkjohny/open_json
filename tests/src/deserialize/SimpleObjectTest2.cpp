#include <gtest/gtest.h>
#include <string>
#include "../../../include/open_json.h"

namespace open_json_test::deserialize::simple_class2 {

    class ClassB : public open_json::Serializable {
    private:
        int id;
        std::string name;

    public:
        ClassB() {
            id = 100;
            name = "Rezaul karim";
        };

        virtual ~ClassB() = default;

        ClassB(const ClassB &obj) {
            this->id = obj.id;
            this->name = obj.name;
        }

        ClassB(ClassB &&obj) {
            this->id = std::move(obj.id);
            this->name = std::move(obj.name);
        }

        ClassB &operator=(const ClassB &obj) {
            this->id = obj.id;
            this->name = obj.name;
            return *this;
        }

        ClassB &operator=(const ClassB &&obj) {
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

        REGISTER_GETTER_INCLUDING_BASE_START(open_json::Serializable)
        GETTER(ClassB, int, "id", &ClassB::GetId),
        GETTER(ClassB, const std::string&, "name", &ClassB::GetName)
        REGISTER_GETTER_INCLUDING_BASE_END


        REGISTER_SETTER_INCLUDING_BASE_START(open_json::Serializable)
        SETTER(ClassB, const int, "id", &ClassB::SetId),
        SETTER(ClassB, const std::string&, "name", &ClassB::SetName)
        REGISTER_SETTER_INCLUDING_BASE_END
    };

    TEST(SimpleObjectTest2, Test) {
        ClassB b;
        nlohmann::json jsonObject = open_json::ToJson(b);
        ASSERT_EQ(b.GetId(), jsonObject.at("id").template get<int>());
        ASSERT_EQ(0, b.GetName().compare(jsonObject.at("name").template get<std::string>()));

        jsonObject = nlohmann::json::object();
        jsonObject["id"] = 200;
        jsonObject["name"] = "David Jonson";

        ClassB b2 = open_json::FromJson<ClassB>(jsonObject);
        ASSERT_EQ(jsonObject.at("id").template get<int>(), b2.GetId());
        ASSERT_EQ(0, jsonObject.at("name").template get<std::string>().compare(b2.GetName()));

        ClassB *p = open_json::FromJson<ClassB *>(jsonObject);
        ASSERT_EQ(jsonObject.at("id").template get<int>(), p->GetId());
        ASSERT_EQ(0, jsonObject.at("name").template get<std::string>().compare(p->GetName()));
        delete p;

        ClassB **pp = open_json::FromJson<ClassB **>(jsonObject);
        ASSERT_EQ(jsonObject.at("id").template get<int>(), (*pp)->GetId());
        ASSERT_EQ(0, jsonObject.at("name").template get<std::string>().compare((*pp)->GetName()));
        delete *pp;
        delete pp;

    }
}