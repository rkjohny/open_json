#include <gtest/gtest.h>
#include <nlohmann/json.hpp>
#include <vector>
#include <string>
#include "../../include/open_json.h"


namespace open_json_test {
    using namespace std;


    class SerializeVectorTest : public ::testing::Test {
    public:
        SerializeVectorTest() = default;

        virtual ~SerializeVectorTest() = default;

        std::vector<double *> *m_scores;
        std::vector<std::string> *m_names;
        std::vector<std::string *> *m_emails;
        std::vector<char *> m_cities;

        void SetUp() override {
            m_scores = new vector<double *>;
            m_scores->push_back(new double(9.9));
            m_scores->push_back(new double(10.01));
            m_scores->push_back(new double(10.1));
            m_scores->push_back(new double(10.4));
            m_scores->push_back(new double(10.5));

            m_names = new std::vector<std::string>();
            m_names->push_back(string("John Carry"));
            m_names->push_back(string("David Jonson"));
            m_names->push_back(string("Emma Martin"));


            m_emails = new std::vector<std::string *>();
            m_emails->push_back(new string("john@sample.com"));
            m_emails->push_back(new string("david@sample.com"));
            m_emails->push_back(new string("emma@sample.com"));

            char *p = new char[100];
            strcpy(p, "New York");
            m_cities.push_back(p);

            p = new char[100];
            strcpy(p, "Boston");
            m_cities.push_back(p);

            p = new char[100];
            strcpy(p, "Paris");
            m_cities.push_back(p);
        }

        void TearDown() override {
            for (auto p: *m_scores) {
                delete p;
            }
            delete m_scores;

            delete m_names;

            for (auto p: *m_emails) {
                delete p;
            }
            delete m_emails;

            for (auto p: m_cities) {
                delete p;
            }
        }
    };

    TEST_F(SerializeVectorTest, TestInt) {
        nlohmann::json jsonArr;
        int val = 0;
        std::vector<int> vecInt;

        vecInt.push_back(1);
        vecInt.push_back(2);
        vecInt.push_back(3);

        jsonArr = open_json::ToJson(vector<int>({1, 2, 3}));
        ASSERT_TRUE(jsonArr.is_array());
        ASSERT_TRUE(jsonArr.size() == 3);
        val = 1;
        for (auto &arrItem: jsonArr) {
            ASSERT_EQ(val++, arrItem.template get<int>());
        }

        jsonArr = open_json::ToJson(std::move(vecInt));
        ASSERT_TRUE(jsonArr.is_array());
        ASSERT_TRUE(jsonArr.size() == vecInt.size());
        auto itr1 = vecInt.begin();
        for (auto &arrItem: jsonArr) {
            ASSERT_EQ(*itr1, arrItem.template get<int>());
            ++itr1;
        }

        jsonArr = open_json::ToJson(vecInt);
        ASSERT_TRUE(jsonArr.is_array());
        ASSERT_TRUE(jsonArr.size() == vecInt.size());
        auto itr2 = vecInt.begin();
        for (auto &arrItem: jsonArr) {
            ASSERT_EQ(*itr2, arrItem.template get<int>());
            ++itr2;
        }

        jsonArr = open_json::ToJson(&vecInt);
        ASSERT_TRUE(jsonArr.is_array());
        ASSERT_TRUE(jsonArr.size() == vecInt.size());
        auto itr3 = vecInt.begin();
        for (auto &arrItem: jsonArr) {
            ASSERT_EQ(*itr3, arrItem.template get<int>());
            ++itr3;
        }
    }

    TEST_F(SerializeVectorTest, TestScore) {
        nlohmann::json jsonArr;

        jsonArr = open_json::ToJson(std::move(*m_scores));
        ASSERT_TRUE(jsonArr.is_array());
        ASSERT_TRUE(jsonArr.size() == m_scores->size());
        auto itr = m_scores->begin();
        for (auto &arrItem: jsonArr) {
            ASSERT_DOUBLE_EQ(arrItem.template get<double>(), **itr);
            ++itr;
        }

        jsonArr = open_json::ToJson(*m_scores);
        ASSERT_TRUE(jsonArr.is_array());
        ASSERT_TRUE(jsonArr.size() == m_scores->size());
        itr = m_scores->begin();
        for (auto &arrItem: jsonArr) {
            ASSERT_DOUBLE_EQ(arrItem.template get<double>(), **itr);
            ++itr;
        }

        jsonArr = open_json::ToJson(m_scores);
        ASSERT_TRUE(jsonArr.is_array());
        ASSERT_TRUE(jsonArr.size() == m_scores->size());
        itr = m_scores->begin();
        for (auto &arrItem: jsonArr) {
            ASSERT_DOUBLE_EQ(arrItem.template get<double>(), **itr);
            ++itr;
        }
    }

    TEST_F(SerializeVectorTest, TestNames) {
        nlohmann::json jsonArr;

        jsonArr = open_json::ToJson(vector<string>(*m_names));
        ASSERT_TRUE(jsonArr.is_array());
        ASSERT_TRUE(jsonArr.size() == m_names->size());
        auto itr = m_names->begin();
        for (auto &arrItem: jsonArr) {
            ASSERT_EQ(0, (*itr).compare(arrItem.template get<string>()));
            ++itr;
        }

        jsonArr = open_json::ToJson(std::move(*m_names));
        ASSERT_TRUE(jsonArr.is_array());
        ASSERT_TRUE(jsonArr.size() == m_names->size());
        itr = m_names->begin();
        for (auto &arrItem: jsonArr) {
            ASSERT_EQ(0, (*itr).compare(arrItem.template get<string>()));
            ++itr;
        }

        jsonArr = open_json::ToJson(*m_names);
        ASSERT_TRUE(jsonArr.is_array());
        ASSERT_TRUE(jsonArr.size() == m_names->size());
        itr = m_names->begin();
        for (auto &arrItem: jsonArr) {
            ASSERT_EQ(0, (*itr).compare(arrItem.template get<string>()));
            ++itr;
        }

        jsonArr = open_json::ToJson(m_names);
        ASSERT_TRUE(jsonArr.is_array());
        ASSERT_TRUE(jsonArr.size() == m_names->size());
        itr = m_names->begin();
        for (auto &arrItem: jsonArr) {
            ASSERT_EQ(0, (*itr).compare(arrItem.template get<string>()));
            ++itr;
        }
    }

    TEST_F(SerializeVectorTest, TestEmails) {
        nlohmann::json jsonArr;

        jsonArr = open_json::ToJson(vector<string *>(*m_emails));
        ASSERT_TRUE(jsonArr.is_array());
        ASSERT_TRUE(jsonArr.size() == m_emails->size());
        auto itr = m_emails->begin();
        for (auto &arrItem: jsonArr) {
            ASSERT_EQ(0, (**itr).compare(arrItem.template get<string>()));
            ++itr;
        }

        jsonArr = open_json::ToJson(std::move(*m_emails));
        ASSERT_TRUE(jsonArr.is_array());
        ASSERT_TRUE(jsonArr.size() == m_emails->size());
        itr = m_emails->begin();
        for (auto &arrItem: jsonArr) {
            ASSERT_EQ(0, (**itr).compare(arrItem.template get<string>()));
            ++itr;
        }

        jsonArr = open_json::ToJson(*m_emails);
        ASSERT_TRUE(jsonArr.is_array());
        ASSERT_TRUE(jsonArr.size() == m_emails->size());
        itr = m_emails->begin();
        for (auto &arrItem: jsonArr) {
            ASSERT_EQ(0, (**itr).compare(arrItem.template get<string>()));
            ++itr;
        }

        jsonArr = open_json::ToJson(m_emails);
        ASSERT_TRUE(jsonArr.is_array());
        ASSERT_TRUE(jsonArr.size() == m_emails->size());
        itr = m_emails->begin();
        for (auto &arrItem: jsonArr) {
            ASSERT_EQ(0, (**itr).compare(arrItem.template get<string>()));
            ++itr;
        }
    }

    TEST_F(SerializeVectorTest, TestCities) {
        nlohmann::json jsonArr;

        jsonArr = open_json::ToJson(std::vector<char *>(m_cities));
        ASSERT_TRUE(jsonArr.is_array());
        ASSERT_TRUE(jsonArr.size() == m_cities.size());
        auto itr = m_cities.begin();
        for (auto &arrItem: jsonArr) {
            ASSERT_EQ(0, std::string(*itr).compare(arrItem.template get<string>()));
            ++itr;
        }

        jsonArr = open_json::ToJson(std::move(m_cities));
        ASSERT_TRUE(jsonArr.is_array());
        ASSERT_TRUE(jsonArr.size() == m_cities.size());
        itr = m_cities.begin();
        for (auto &arrItem: jsonArr) {
            ASSERT_EQ(0, std::string(*itr).compare(arrItem.template get<string>()));
            ++itr;
        }

        jsonArr = open_json::ToJson(m_cities);
        ASSERT_TRUE(jsonArr.is_array());
        ASSERT_TRUE(jsonArr.size() == m_cities.size());
        itr = m_cities.begin();
        for (auto &arrItem: jsonArr) {
            ASSERT_EQ(0, std::string(*itr).compare(arrItem.template get<string>()));
            ++itr;
        }

        jsonArr = open_json::ToJson(&m_cities);
        ASSERT_TRUE(jsonArr.is_array());
        ASSERT_TRUE(jsonArr.size() == m_cities.size());
        itr = m_cities.begin();
        for (auto &arrItem: jsonArr) {
            ASSERT_EQ(0, std::string(*itr).compare(arrItem.template get<string>()));
            ++itr;
        }
    }
}