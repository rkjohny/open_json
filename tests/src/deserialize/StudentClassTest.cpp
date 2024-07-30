#include <iostream>
#include <gtest/gtest.h>
#include <vector>
#include <string>
#include <tuple>
#include "../../include/CommonDef.h"
#include "../../../include/open_json.h"


namespace open_json_test::deserialize::student::no_constant {

    class Student {
    private:
        std::string m_name;
        long m_id;
        std::vector<std::string> m_subjects;

    public:
        Student() = default;

        virtual ~Student() = default;

        Student(const Student &obj) {
            this->m_name = obj.m_name;
            this->m_id = obj.m_id;
            this->m_subjects = obj.m_subjects;
        }

        Student(Student &&obj) {
            this->m_name = std::move(obj.m_name);
            this->m_id = std::move(obj.m_id);
            this->m_subjects = std::move(obj.m_subjects);
        }

        Student &operator=(const Student &obj) {
            this->m_name = obj.m_name;
            this->m_id = obj.m_id;
            this->m_subjects = obj.m_subjects;
            return *this;
        }

        Student &operator=(const Student &&obj) {
            this->m_name = std::move(obj.m_name);
            this->m_id = std::move(obj.m_id);
            this->m_subjects = std::move(obj.m_subjects);
            return *this;
        }


        std::string GetName() const {
            return m_name;
        }

        void SetName(std::string name) {
            this->m_name = name;
        }

        long GetId() const {
            return m_id;
        }

        void SetId(long id) {
            this->m_id = id;
        }

        std::vector<std::string> GetSubjects() const {
            return m_subjects;
        }

        void SetSubjects(std::vector<std::string> subjects) {
            m_subjects = subjects;
        }

        REGISTER_GETTER_START
        GETTER(Student, std::string, "name", &Student::GetName),
        GETTER(Student, long, "id", &Student::GetId),
        GETTER(Student, std::vector<std::string>, "subjects", &Student::GetSubjects)
        REGISTER_GETTER_END


        REGISTER_SETTER_START
        SETTER(Student, std::string, "name", &Student::SetName),
        SETTER(Student, long, "id", &Student::SetId),
        SETTER(Student, std::vector<std::string>, "subjects", &Student::SetSubjects)
        REGISTER_SETTER_END
    };

    class DeserializeStudentTest : public ::testing::Test {
    public:
        DeserializeStudentTest() = default;

        ~DeserializeStudentTest() = default;

        void SetUp() override {
        }

        void TearDown() override {
        }
    };

    TEST_F(DeserializeStudentTest, SerializeStudentClassTest) {
        Student student;
        student.SetName("Rezaul Karim");
        student.SetId(100);
        std::vector<std::string> sub;
        student.SetSubjects({"Math", "Calculus", "Geometry"});

        nlohmann::json jsonObject;

        jsonObject = open_json::ToJson(student);
        ASSERT_TRUE(jsonObject.is_object());
        ASSERT_EQ(0, student.GetName().compare(jsonObject.at("name").template get<std::string>()));
        ASSERT_EQ(student.GetId(), jsonObject.at("id").template get<long>());

        ASSERT_TRUE(jsonObject.at("subjects").is_array());
        auto v = student.GetSubjects();
        auto itr2 = v.begin();
        for (auto &arrItem: jsonObject.at("subjects")) {
            ASSERT_EQ(0, itr2->compare(arrItem.template get<std::string>()));
            ++itr2;
        }
    }

    TEST_F(DeserializeStudentTest, DeserializeStudentClassTest) {
        nlohmann::json jsonObject;

        jsonObject["id"] = 200;
        jsonObject["name"] = "David Jonson";
        jsonObject["subjects"] = nlohmann::json::array();
        jsonObject["subjects"].push_back("Physics");
        jsonObject["subjects"].push_back("Chemistry");
        jsonObject["subjects"].push_back("Biology");

        Student student = open_json::FromJson<Student>(jsonObject);
        ASSERT_EQ(200, student.GetId());
        ASSERT_EQ(0, std::string("David Jonson").compare(student.GetName()));
        ASSERT_TRUE(student.GetSubjects().size() == 3);

        ASSERT_EQ(0, std::string("Physics").compare(student.GetSubjects()[0]));
        ASSERT_EQ(0, std::string("Chemistry").compare(student.GetSubjects()[1]));
        ASSERT_EQ(0, std::string("Biology").compare(student.GetSubjects()[2]));
    }
}

