#include <gtest/gtest.h>
#include <string>
#include "../../../include/open_json.h"

namespace open_json_test::serialize::null_value {

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

        REGISTER_GETTER_START
        GETTER(ClassA, int, "id", &ClassA::GetId),
        GETTER(ClassA, const std::string&, "name", &ClassA::GetName),
        GETTER(ClassA, int *, "age", &ClassA::GetAge)
        REGISTER_GETTER_END
    };

    TEST(ClassA, Test) {
        ClassA a;
        a.SetName("Rrzaul Karim");
        // id has default value, age is null

        nlohmann::json jsonObject = open_json::ToJson(a);

        ASSERT_EQ(jsonObject.at("id").template get<int>(), -1);
        ASSERT_EQ(0, jsonObject.at("name").template get<std::string>().compare(a.GetName()));
        ASSERT_FALSE(jsonObject.contains("age"));
    }
}