#include <iostream>

#include <gtest/gtest.h>
#include <vector>
#include <string>
#include <tuple>
#include "../../../include/open_json.h"


namespace open_json_test::serialize::person {

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

        int GetAge() const {
            return m_age;
        }

        const std::vector<double> &GetScores() const {
            return m_scores;
        }

        static constexpr std::tuple getters = std::make_tuple(
                open_json::Getter<Person, const std::string &>(&Person::GetName, "name"),
                open_json::Getter<Person, int>(&Person::GetAge, "age"),
                open_json::Getter<Person, const std::vector<double> &>(&Person::GetScores, "scores")
        );
    };

    class SerializePersonObjectTest : public ::testing::Test {
    public:
        SerializePersonObjectTest() = default;

        ~SerializePersonObjectTest() = default;

        void SetUp() override {
        }

        void TearDown() override {
        }
    };

    TEST_F(SerializePersonObjectTest, PersonClassTest) {
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
}

