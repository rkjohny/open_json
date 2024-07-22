#include <gtest/gtest.h>
#include <vector>
#include <string>
#include "../../../include/open_json.h"


namespace open_json_test {
    namespace serialize {

        class SerializeVectorTest : public ::testing::Test {
        public:
            SerializeVectorTest() = default;

            virtual ~SerializeVectorTest() = default;

            std::vector<double *> *m_scores;
            std::vector<std::string> *m_names;
            std::vector<std::string *> *m_emails;
            std::vector<std::string *> **m_cities;

            void SetUp() override {
                m_scores = new std::vector<double *>;
                m_scores->push_back(new double(9.9));
                m_scores->push_back(new double(10.01));
                m_scores->push_back(new double(10.1));
                m_scores->push_back(new double(10.4));
                m_scores->push_back(new double(10.5));

                m_names = new std::vector<std::string>();
                m_names->push_back(std::string("John Carry"));
                m_names->push_back(std::string("David Jonson"));
                m_names->push_back(std::string("Emma Martin"));


                m_emails = new std::vector<std::string *>();
                m_emails->push_back(new std::string("john@sample.com"));
                m_emails->push_back(new std::string("david@sample.com"));
                m_emails->push_back(new std::string("emma@sample.com"));

                m_cities = new std::vector<std::string *> *(new std::vector<std::string *>());


                std::string *p = new std::string("New York");
                (*m_cities)->push_back(p);

                p = new std::string("Boston, USA");
                (*m_cities)->push_back(p);

                p = new std::string("Paris");
                (*m_cities)->push_back(p);
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

                for (auto p: **m_cities) {
                    delete p;
                }
                delete *m_cities;
                delete m_cities;
            }
        };

        TEST_F(SerializeVectorTest, TestInt) {
            nlohmann::json jsonArr;
            int val = 0;
            std::vector<int> vecInt;

            vecInt.push_back(1);
            vecInt.push_back(2);
            vecInt.push_back(3);

            jsonArr = open_json::ToJson<std::vector<int>>(std::vector<int>({1, 2, 3}));
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

        TEST_F(SerializeVectorTest, TestLong) {
            nlohmann::json jsonArr;
            int val = 0;
            std::vector<long *> vecLongPtr;

            vecLongPtr.push_back(new long(0));
            vecLongPtr.push_back(new long(1));
            vecLongPtr.push_back(new long(3));

            jsonArr = open_json::ToJson(std::move(vecLongPtr));
            ASSERT_TRUE(jsonArr.is_array());
            ASSERT_TRUE(jsonArr.size() == vecLongPtr.size());
            auto itr1 = vecLongPtr.begin();
            for (auto &arrItem: jsonArr) {
                ASSERT_EQ(**itr1, arrItem.template get<long>());
                ++itr1;
            }

            jsonArr = open_json::ToJson(vecLongPtr);
            ASSERT_TRUE(jsonArr.is_array());
            ASSERT_TRUE(jsonArr.size() == vecLongPtr.size());
            auto itr2 = vecLongPtr.begin();
            for (auto &arrItem: jsonArr) {
                ASSERT_EQ(**itr2, arrItem.template get<long>());
                ++itr2;
            }

            jsonArr = open_json::ToJson(&vecLongPtr);
            ASSERT_TRUE(jsonArr.is_array());
            ASSERT_TRUE(jsonArr.size() == vecLongPtr.size());
            auto itr3 = vecLongPtr.begin();
            for (auto &arrItem: jsonArr) {
                ASSERT_EQ(**itr3, arrItem.template get<long>());
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

            jsonArr = open_json::ToJson(std::vector<std::string>(*m_names));
            ASSERT_TRUE(jsonArr.is_array());
            ASSERT_TRUE(jsonArr.size() == m_names->size());
            auto itr = m_names->begin();
            for (auto &arrItem: jsonArr) {
                ASSERT_EQ(0, (*itr).compare(arrItem.template get<std::string>()));
                ++itr;
            }

            jsonArr = open_json::ToJson(std::move(*m_names));
            ASSERT_TRUE(jsonArr.is_array());
            ASSERT_TRUE(jsonArr.size() == m_names->size());
            itr = m_names->begin();
            for (auto &arrItem: jsonArr) {
                ASSERT_EQ(0, (*itr).compare(arrItem.template get<std::string>()));
                ++itr;
            }

            jsonArr = open_json::ToJson(*m_names);
            ASSERT_TRUE(jsonArr.is_array());
            ASSERT_TRUE(jsonArr.size() == m_names->size());
            itr = m_names->begin();
            for (auto &arrItem: jsonArr) {
                ASSERT_EQ(0, (*itr).compare(arrItem.template get<std::string>()));
                ++itr;
            }

            jsonArr = open_json::ToJson(m_names);
            ASSERT_TRUE(jsonArr.is_array());
            ASSERT_TRUE(jsonArr.size() == m_names->size());
            itr = m_names->begin();
            for (auto &arrItem: jsonArr) {
                ASSERT_EQ(0, (*itr).compare(arrItem.template get<std::string>()));
                ++itr;
            }
        }

        TEST_F(SerializeVectorTest, TestEmails) {
            nlohmann::json jsonArr;

            jsonArr = open_json::ToJson(std::vector<std::string *>(*m_emails));
            ASSERT_TRUE(jsonArr.is_array());
            ASSERT_TRUE(jsonArr.size() == m_emails->size());
            auto itr = m_emails->begin();
            for (auto &arrItem: jsonArr) {
                ASSERT_EQ(0, (**itr).compare(arrItem.template get<std::string>()));
                ++itr;
            }

            jsonArr = open_json::ToJson(std::move(*m_emails));
            ASSERT_TRUE(jsonArr.is_array());
            ASSERT_TRUE(jsonArr.size() == m_emails->size());
            itr = m_emails->begin();
            for (auto &arrItem: jsonArr) {
                ASSERT_EQ(0, (**itr).compare(arrItem.template get<std::string>()));
                ++itr;
            }

            jsonArr = open_json::ToJson(*m_emails);
            ASSERT_TRUE(jsonArr.is_array());
            ASSERT_TRUE(jsonArr.size() == m_emails->size());
            itr = m_emails->begin();
            for (auto &arrItem: jsonArr) {
                ASSERT_EQ(0, (**itr).compare(arrItem.template get<std::string>()));
                ++itr;
            }

            jsonArr = open_json::ToJson(m_emails);
            ASSERT_TRUE(jsonArr.is_array());
            ASSERT_TRUE(jsonArr.size() == m_emails->size());
            itr = m_emails->begin();
            for (auto &arrItem: jsonArr) {
                ASSERT_EQ(0, (**itr).compare(arrItem.template get<std::string>()));
                ++itr;
            }
        }

        TEST_F(SerializeVectorTest, TestCities) {
            nlohmann::json jsonArr;

            jsonArr = open_json::ToJson(std::vector<std::string *>(**m_cities));
            ASSERT_TRUE(jsonArr.is_array());
            ASSERT_TRUE(jsonArr.size() == (**m_cities).size());
            auto itr = (**m_cities).begin();
            for (auto &arrItem: jsonArr) {
                ASSERT_EQ(0, std::string(**itr).compare(arrItem.template get<std::string>()));
                ++itr;
            }

            jsonArr = open_json::ToJson(m_cities);
            ASSERT_TRUE(jsonArr.is_array());
            ASSERT_TRUE(jsonArr.size() == (**m_cities).size());
            itr = (**m_cities).begin();
            for (auto &arrItem: jsonArr) {
                ASSERT_EQ(0, std::string(**itr).compare(arrItem.template get<std::string>()));
                ++itr;
            }

            jsonArr = open_json::ToJson(&m_cities);
            ASSERT_TRUE(jsonArr.is_array());
            ASSERT_TRUE(jsonArr.size() == (**m_cities).size());
            itr = (**m_cities).begin();
            for (auto &arrItem: jsonArr) {
                ASSERT_EQ(0, std::string(**itr).compare(arrItem.template get<std::string>()));
                ++itr;
            }
        }
    }
}