#include <iostream>

#include <gtest/gtest.h>
#include <vector>
#include <string>
#include <tuple>
#include "../../../include/open_json.h"


namespace open_json_test::deserialize::person {

    class Person {
    private:
        std::string m_name;
        int m_age;
        std::vector<double> m_scores;

    public:
        Person() {
            m_name = "Rezaul Karim";
            m_age = 43;
            m_scores.push_back(10.5);
            m_scores.push_back(20.1);
            m_scores.push_back(30.9);
        }

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

        static constexpr std::tuple getters = std::make_tuple(
                open_json::Getter<Person, const std::string &>(&Person::GetName, "name"),
                open_json::Getter<Person, int>(&Person::GetAge, "age"),
                open_json::Getter<Person, const std::vector<double> &>(&Person::GetScores, "scores")
        );

        static constexpr std::tuple setters = std::make_tuple(
                open_json::Setter<Person, const std::string &>(&Person::SetName, "name"),
                open_json::Setter<Person, const int &>(&Person::SetAge, "age"),
                open_json::Setter<Person, const std::vector<double> &>(&Person::SetScores, "scores")
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

        jsonObject = open_json::ToJson(person);
        ASSERT_TRUE(jsonObject.is_object());
        ASSERT_EQ(0, person.GetName().compare(jsonObject.at("name").template get<std::string>()));
        ASSERT_EQ(person.GetAge(), jsonObject.at("age").template get<int>());
        ASSERT_TRUE(jsonObject.at("scores").is_array());
        auto itr = person.GetScores().begin();
        for (auto &arrItem: jsonObject.at("scores")) {
            ASSERT_DOUBLE_EQ(*itr, arrItem.template get<double>());
            ++itr;
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

        Person person = open_json::FromJson<Person>(jsonObject);
        ASSERT_EQ(0, std::string("Leonel Messi").compare(person.GetName()));
        ASSERT_EQ(36, person.GetAge());
        ASSERT_TRUE(person.GetScores().size() == 3);
        ASSERT_DOUBLE_EQ(90.5, person.GetScores()[0]);
        ASSERT_DOUBLE_EQ(90.1, person.GetScores()[1]);
        ASSERT_DOUBLE_EQ(90.9, person.GetScores()[2]);
    }
}

