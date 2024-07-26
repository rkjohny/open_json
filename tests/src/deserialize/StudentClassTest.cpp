#include <iostream>
#include <gtest/gtest.h>
#include <vector>
#include <string>
#include <tuple>
#include "../../../include/open_json.h"


namespace open_json_test::deserialize::student {

    class Student {
    private:
        std::string m_name;
        long m_id;
        std::vector<std::string> m_subjects;

    public:
        Student() {
            m_name = "Rezaul Karim";
            m_id = 100;
            m_subjects.push_back("Math");
            m_subjects.push_back("Calculus");
            m_subjects.push_back("Geometry");
        }

        virtual ~Student() = default;

        const std::string &GetName() const {
            return m_name;
        }

        void SetName(const std::string &name) {
            this->m_name = name;
        }

        long GetId() const {
            return m_id;
        }

        void SetId(const long &id) {
            this->m_id = id;
        }

        const std::vector<std::string> &GetSubjects() const {
            return m_subjects;
        }

        void SetSubjects(const std::vector<std::string> &subjects) {
            m_subjects = subjects;
        }

        REGISTER_GETTER_START
        GETTER(Student, const std::string &, "name", &Student::GetName),
        GETTER(Student, long, "id", &Student::GetId),
        GETTER(Student, const std::vector<std::string>&, "subjects", &Student::GetSubjects)
        REGISTER_GETTER_END


        REGISTER_SETTER_START
        SETTER(Student, const std::string &, "name", &Student::SetName),
        SETTER(Student, const long&, "id", &Student::SetId),
        SETTER(Student, const std::vector<std::string>&, "subjects", &Student::SetSubjects)
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
        nlohmann::json jsonObject;

        jsonObject = open_json::ToJson(student);
        ASSERT_TRUE(jsonObject.is_object());
        ASSERT_EQ(0, student.GetName().compare(jsonObject.at("name").template get<std::string>()));
        ASSERT_EQ(student.GetId(), jsonObject.at("id").template get<long>());
        ASSERT_TRUE(jsonObject.at("subjects").is_array());
        auto itr = student.GetSubjects().begin();
        for (auto &arrItem: jsonObject.at("subjects")) {
            ASSERT_EQ(0, itr->compare(arrItem.template get<std::string>()));
            ++itr;
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

//        std::cout << student.GetSubjects()[0] << std::endl;
//        std::cout << student.GetSubjects()[1] << std::endl;
//        std::cout << student.GetSubjects()[2] << std::endl;

        ASSERT_EQ(0, std::string("Physics").compare(student.GetSubjects()[0]));
        ASSERT_EQ(0, std::string("Chemistry").compare(student.GetSubjects()[1]));
        ASSERT_EQ(0, std::string("Biology").compare(student.GetSubjects()[2]));
    }
}

