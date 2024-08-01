#include <gtest/gtest.h>
#include <string>
#include "../../../include/open_json.h"

namespace open_json_test::deserialize::null_value {

    class ClassA {
    private:
        int id = -1;
        std::string name;
        int *age = nullptr;

    public:
        ClassA() = default;

        virtual ~ClassA() {
            if(age) delete age;
        };

        ClassA(const ClassA &obj) {
            this->id = obj.id;
            this->name = obj.name;
            if (obj.age) {
                this->age = new int (*obj.age);
            }
        }

        ClassA(ClassA &&obj) {
            this->id = std::move(obj.id);
            this->name = std::move(obj.name);
            if (obj.age) {
                this->age = new int (std::move(*obj.age));
            }
        }

        ClassA &operator=(const ClassA &obj) {
            this->id = obj.id;
            this->name = obj.name;
            if (obj.age) {
                this->age = new int (*obj.age);
            }
            return *this;
        }

        ClassA &operator=(const ClassA &&obj) {
            this->id = std::move(obj.id);
            this->name = std::move(obj.name);
            if (obj.age) {
                this->age = new int (std::move(*obj.age));
            }
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

        int * GetAge() const {
            return age;
        }

        void SetAge(int *a) {
            this->age = a;
        }

        REGISTER_SETTER_START
        SETTER(ClassA, const int, "id", &ClassA::SetId),
        SETTER(ClassA, const std::string&, "name", &ClassA::SetName),
        SETTER(ClassA, int *, "age", &ClassA::SetAge)
        REGISTER_GETTER_END
    };

    TEST(ClassA, Test) {
        nlohmann::json jsonObject = nlohmann::json::object();
        jsonObject["id"] = 200;
        jsonObject["name"] = "David Jonson";
        // age is null

        ClassA a = open_json::FromJson<ClassA>(jsonObject);
        ASSERT_EQ(jsonObject.at("id").template get<int>(), a.GetId());
        ASSERT_EQ(0, jsonObject.at("name").template get<std::string>().compare(a.GetName()));
        ASSERT_TRUE(a.GetAge() == nullptr);

        jsonObject = nlohmann::json::object();
        jsonObject["age"] = 20;
        jsonObject["name"] = "David Jonson";
        // id is null

        a = open_json::FromJson<ClassA>(jsonObject);
        ASSERT_EQ(jsonObject.at("age").template get<int>(), *a.GetAge());
        ASSERT_EQ(0, jsonObject.at("name").template get<std::string>().compare(a.GetName()));
        ASSERT_TRUE(a.GetId() == -1); // default value -1
    }
}