#include <iostream>

#include <gtest/gtest.h>
#include <vector>
#include <string>
#include <tuple>
#include "../../include/CommonDef.h"
#include "../../../include/open_json.h"


namespace open_json_test::deserialize::person::constant {

    class Person {
    private:
        std::string m_name;
        int m_age;
        std::vector<double> m_scores;
        std::vector<std::string> m_subjects;

    public:
        // Using default copy_constructor, move_constructor, copy_assignment and move_assignment operator

        Person() = default;

        virtual ~Person() = default;

        const std::string &GetName() const {
            return m_name;
        }

        void SetName(const std::string &name) {
            m_name = name;
        }

        int GetAge() const {
            return m_age;
        }

        void SetAge(const int &age) {
            m_age = age;
        }

        const std::vector<double> &GetScores() const {
            return m_scores;
        }

        void SetScores(const std::vector<double> &scores) {
            m_scores = scores;
        }

        const std::vector<std::string> &GetSubjects() const {
            return m_subjects;
        };

        void SetSubjects(const std::vector<std::string> &subjects) {
            m_subjects = subjects;
        }

        static constexpr std::tuple getters = std::make_tuple(
                open_json::Getter<Person, const std::string &>(&Person::GetName, "name"),
                open_json::Getter<Person, int>(&Person::GetAge, "age"),
                open_json::Getter<Person, const std::vector<double> &>(&Person::GetScores, "scores"),
                open_json::Getter<Person, const std::vector<std::string> &>(&Person::GetSubjects, "subjects")
        );

        static constexpr std::tuple setters = std::make_tuple(
                open_json::Setter<Person, const std::string &>(&Person::SetName, "name"),
                open_json::Setter<Person, const int &>(&Person::SetAge, "age"),
                open_json::Setter<Person, const std::vector<double> &>(&Person::SetScores, "scores"),
                open_json::Setter<Person, const std::vector<std::string> &>(&Person::SetSubjects, "subjects")
        );
    };

    class DeserializePersonObjectTest : public ::testing::Test {
    public:
        DeserializePersonObjectTest() = default;

        ~DeserializePersonObjectTest() = default;

        void SetUp() override {
        }

        void TearDown() override {
        }
    };

    TEST_F(DeserializePersonObjectTest, SerializePersonClassTest) {
        Person person;
        nlohmann::json jsonObject;

        person.SetName("Rezaul Karim");
        person.SetAge(43);
        person.SetScores({10.5, 20.1, 30.9});
        person.SetSubjects({"Math", "Calculus", "Geometry"});

        jsonObject = open_json::ToJson(person);
        ASSERT_TRUE(jsonObject.is_object());
        ASSERT_EQ(0, person.GetName().compare(jsonObject.at("name").template get<std::string>()));
        ASSERT_EQ(person.GetAge(), jsonObject.at("age").template get<int>());

        ASSERT_TRUE(jsonObject.at("scores").is_array());
        ASSERT_TRUE(jsonObject.at("scores").size() == 3);
        auto itr = person.GetScores().begin();
        for (auto &arrItem: jsonObject.at("scores")) {
            ASSERT_DOUBLE_EQ(*itr, arrItem.template get<double>());
            ++itr;
        }

        ASSERT_TRUE(jsonObject.at("subjects").is_array());
        ASSERT_TRUE(jsonObject.at("subjects").size() == 3);
        auto itr2 = person.GetSubjects().begin();
        for (auto &arrItem: jsonObject.at("subjects")) {
            ASSERT_EQ(0, itr2->compare(arrItem.template get<std::string>()));
            ++itr2;
        }
    }

    TEST_F(DeserializePersonObjectTest, DeserializePersonClassTest) {
        nlohmann::json jsonObject;

        jsonObject["name"] = "Leonel Messi";
        jsonObject["age"] = 36;
        jsonObject["scores"] = nlohmann::json::array();
        jsonObject["scores"].push_back(90.5);
        jsonObject["scores"].push_back(90.1);
        jsonObject["scores"].push_back(90.9);

        jsonObject["subjects"] = nlohmann::json::array();
        jsonObject["subjects"].push_back("Bengali");
        jsonObject["subjects"].push_back("English");
        jsonObject["subjects"].push_back("Medicine");

        Person person = open_json::FromJson<Person>(jsonObject);
        ASSERT_EQ(0, std::string("Leonel Messi").compare(person.GetName()));
        ASSERT_EQ(36, person.GetAge());

        ASSERT_TRUE(person.GetScores().size() == 3);
        ASSERT_DOUBLE_EQ(90.5, person.GetScores()[0]);
        ASSERT_DOUBLE_EQ(90.1, person.GetScores()[1]);
        ASSERT_DOUBLE_EQ(90.9, person.GetScores()[2]);

        ASSERT_TRUE(person.GetSubjects().size() == 3);
        ASSERT_EQ(0, person.GetSubjects()[0].compare("Bengali"));
        ASSERT_EQ(0, person.GetSubjects()[1].compare("English"));
        ASSERT_EQ(0, person.GetSubjects()[2].compare("Medicine"));
    }
}

