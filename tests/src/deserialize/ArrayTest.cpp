#include <gtest/gtest.h>
#include <string>
#include "../../include/CommonDef.h"
#include "../../../include/open_json.h"

namespace open_json_test::deserialize::array_test {

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

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmismatched-new-delete"

    TEST(ArrayTest, Test) {
        nlohmann::json jsonObject = nlohmann::json::array();
        jsonObject[0]["id"] = 100;
        jsonObject[0]["name"] = "David Jonson";

        jsonObject[1]["id"] = 200;
        jsonObject[1]["name"] = "Rezaul Karim";

        jsonObject[2]["id"] = 300;
        jsonObject[2]["name"] = "Mr. xyz";

        ClassA *a = open_json::FromJson<ClassA*>(jsonObject, jsonObject.size());

        for( int i = 0; i<3; i++) {
            ASSERT_EQ(jsonObject[i].at("id").template get<int>(), a[i].GetId());
            ASSERT_EQ(0, jsonObject[i].at("name").template get<std::string>().compare(a[i].GetName()));
        }
        delete [] (a);
    }
#pragma GCC diagnostic pop
}