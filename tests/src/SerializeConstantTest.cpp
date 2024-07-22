#include <gtest/gtest.h>
#include <nlohmann/json.hpp>
#include <vector>
#include <string>
#include "../../include/open_json.h"


//deserializing an object containing constant data

namespace open_json_test {

    class SerializeConstantTest : public ::testing::Test {
    public:
        SerializeConstantTest() = default;

        virtual ~SerializeConstantTest() = default;

        const std::string *const *name;
        std::vector<const double *const *> *m_scores;
        std::vector<const std::string *> *m_emails;
        const int id = 100;
        const int &refId = id;

        void SetUp() override {
            name = new std::string *(new std::string("Rezaul karim"));

            m_scores = new std::vector<const double *const *>();
            m_scores->push_back(new double *(new double(9.9)));
            m_scores->push_back(new double *(new double(10.01)));
            m_scores->push_back(new double *(new double(10.1)));

            m_emails = new std::vector<const std::string *>();
            m_emails->push_back(new std::string("reza@gmail.com"));
            m_emails->push_back(new std::string("john@gmail.com"));
            m_emails->push_back(new std::string("david@gmail.com"));
        }

        void TearDown() override {
            for (auto p: *m_scores) {
                delete *p;
                delete p;
            }
            delete m_scores;

            for (auto p: *m_emails) {
                delete p;
            }
            delete m_emails;
        }
    };

    TEST_F(SerializeConstantTest, TestInt) {
        nlohmann::json jsonObject;
        const std::vector<int> vecInt({1, 2, 3});

        jsonObject = open_json::ToJson(std::move(vecInt));
        ASSERT_TRUE(jsonObject.is_array());
        ASSERT_TRUE(jsonObject.size() == vecInt.size());
        auto itr = vecInt.begin();
        for (auto &arrItem: jsonObject) {
            ASSERT_EQ(*itr, arrItem.template get<int>());
            ++itr;
        }

        jsonObject = open_json::ToJson(vecInt);
        ASSERT_TRUE(jsonObject.is_array());
        ASSERT_TRUE(jsonObject.size() == vecInt.size());
        itr = vecInt.begin();
        for (auto &arrItem: jsonObject) {
            ASSERT_EQ(*itr, arrItem.template get<int>());
            ++itr;
        }

        jsonObject = open_json::ToJson(&vecInt);
        ASSERT_TRUE(jsonObject.is_array());
        ASSERT_TRUE(jsonObject.size() == vecInt.size());
        itr = vecInt.begin();
        for (auto &arrItem: jsonObject) {
            ASSERT_EQ(*itr, arrItem.template get<int>());
            ++itr;
        }
    }

    TEST_F(SerializeConstantTest, TestScore) {
        nlohmann::json jsonObject;

        const std::vector<const double *const *> *const ptr = m_scores;
        const std::vector<const double *const *> *const *ptr2 = &m_scores;

        jsonObject = open_json::ToJson(std::move(*ptr));
        ASSERT_TRUE(jsonObject.is_array());
        ASSERT_TRUE(jsonObject.size() == m_scores->size());
        auto itr = m_scores->begin();
        for (auto &arrItem: jsonObject) {
            ASSERT_DOUBLE_EQ(***itr, arrItem.template get<double>());
            ++itr;
        }

        jsonObject = open_json::ToJson(ptr);
        ASSERT_TRUE(jsonObject.size() == m_scores->size());
        itr = m_scores->begin();
        for (auto &arrItem: jsonObject) {
            ASSERT_DOUBLE_EQ(***itr, arrItem.template get<double>());
            ++itr;
        }

        jsonObject = open_json::ToJson(ptr2);
        ASSERT_TRUE(jsonObject.size() == m_scores->size());
        itr = m_scores->begin();
        for (auto &arrItem: jsonObject) {
            ASSERT_DOUBLE_EQ(***itr, arrItem.template get<double>());
            ++itr;
        }
    }

    TEST_F(SerializeConstantTest, TestEmails) {
        nlohmann::json jsonObject;
        const std::vector<const std::string *> *const vecPtr = m_emails;
        const std::vector<const std::string *> *const *vecPtr2 = &m_emails;

        jsonObject = open_json::ToJson(std::vector<const std::string *>(*vecPtr));
        ASSERT_TRUE(jsonObject.is_array());
        ASSERT_TRUE(jsonObject.size() == vecPtr->size());
        auto itr = vecPtr->begin();
        for (auto &arrItem: jsonObject) {
            ASSERT_EQ(0, (**itr).compare(arrItem.template get<std::string>()));
            ++itr;
        }

        jsonObject = open_json::ToJson(std::move(vecPtr));
        ASSERT_TRUE(jsonObject.is_array());
        ASSERT_TRUE(jsonObject.size() == vecPtr->size());
        itr = vecPtr->begin();
        for (auto &arrItem: jsonObject) {
            ASSERT_EQ(0, (**itr).compare(arrItem.template get<std::string>()));
            ++itr;
        }

        jsonObject = open_json::ToJson(std::move(vecPtr2));
        ASSERT_TRUE(jsonObject.is_array());
        ASSERT_TRUE(jsonObject.size() == vecPtr->size());
        itr = vecPtr->begin();
        for (auto &arrItem: jsonObject) {
            ASSERT_EQ(0, (**itr).compare(arrItem.template get<std::string>()));
            ++itr;
        }
    }

    TEST_F(SerializeConstantTest, NameAndID) {
        nlohmann::json jsonObject = open_json::ToJson(name);
        ASSERT_EQ(0, (**name).compare(jsonObject.template get<std::string>()));

        jsonObject = open_json::ToJson(id);
        ASSERT_EQ(id, jsonObject.template get<int>());

        jsonObject = open_json::ToJson(refId);
        ASSERT_EQ(refId, jsonObject.template get<int>());
    }

} // namespace SerializingTest
