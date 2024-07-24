#include <iostream>
#include <gtest/gtest.h>
#include <vector>
#include <string>
#include <tuple>
#include "../../../include/open_json.h"


namespace open_json_test::serialize {

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

        long GetId() const {
            return m_id;
        }

        const std::vector<std::string> &GetSubjects() const {
            return m_subjects;
        }

        REGISTER_GETTER_START
        GETTER(Student, const std::string &, "name", &Student::GetName),
        GETTER(Student, long, "id", &Student::GetId),
        GETTER(Student, const std::vector<std::string>&, "subjects", &Student::GetSubjects)
        REGISTER_GETTER_END
    };

    class SerializeStudentTest : public ::testing::Test {
    public:
        SerializeStudentTest() = default;

        ~SerializeStudentTest() = default;

        void SetUp() override {
        }

        void TearDown() override {
        }
    };

    TEST_F(SerializeStudentTest, StudentClassTest) {
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
}

