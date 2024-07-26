#include <gtest/gtest.h>
#include <vector>
#include <string>
#include "../../../include/open_json.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmaybe-uninitialized"

namespace open_json_test::deserialize::vector_test::primitive {

    class DeserializeVectorTest : public ::testing::Test {
    public:
        DeserializeVectorTest() = default;

        virtual ~DeserializeVectorTest() = default;

        void SetUp() override {
        }

        void TearDown() override {
        }
    };

    TEST_F(DeserializeVectorTest, TestInt) {
        nlohmann::json jsonArr = nlohmann::json::array();
        jsonArr.push_back(10);
        jsonArr.push_back(20);
        jsonArr.push_back(30);

        std::vector<int> intVec = open_json::FromJson<std::vector<int>>(jsonArr);
        ASSERT_TRUE(intVec.size() == 3);
        ASSERT_EQ(10, intVec[0]);
        ASSERT_EQ(20, intVec[1]);
        ASSERT_EQ(30, intVec[2]);

        std::vector<long> longVec = open_json::FromJson< std::vector<long>>(jsonArr);
        ASSERT_TRUE(longVec.size() == 3);
        ASSERT_EQ(10L, longVec[0]);
        ASSERT_EQ(20L, longVec[1]);
        ASSERT_EQ(30L, longVec[2]);

        std::vector<long long> longLongVec = open_json::FromJson< std::vector<long long>>(jsonArr);
        ASSERT_TRUE(longLongVec.size() == 3);
        ASSERT_EQ(10L, longLongVec[0]);
        ASSERT_EQ(20L, longLongVec[1]);
        ASSERT_EQ(30L, longLongVec[2]);


        std::vector<unsigned long> unsignedLongVec = open_json::FromJson< std::vector<unsigned long>>(jsonArr);
        ASSERT_TRUE(unsignedLongVec.size() == 3);
        ASSERT_EQ(10L, unsignedLongVec[0]);
        ASSERT_EQ(20L, unsignedLongVec[1]);
        ASSERT_EQ(30L, unsignedLongVec[2]);


        std::vector<unsigned long long> unsignedLongLongVec = open_json::FromJson< std::vector<unsigned long long>>(jsonArr);
        ASSERT_TRUE(unsignedLongLongVec.size() == 3);
        ASSERT_EQ(10L, unsignedLongLongVec[0]);
        ASSERT_EQ(20L, unsignedLongLongVec[1]);
        ASSERT_EQ(30L, unsignedLongLongVec[2]);
    }

    TEST_F(DeserializeVectorTest, TestDouble) {
        nlohmann::json jsonArr = nlohmann::json::array();
        jsonArr.push_back(10.1);
        jsonArr.push_back(20.5);
        jsonArr.push_back(30.9);

        std::vector<double> vec = open_json::FromJson<std::vector<double>>(jsonArr);
        ASSERT_TRUE(vec.size() == 3);
        ASSERT_DOUBLE_EQ(10.1, vec[0]);
        ASSERT_DOUBLE_EQ(20.5, vec[1]);
        ASSERT_DOUBLE_EQ(30.9, vec[2]);

        std::vector<long double> longDouble = open_json::FromJson<std::vector<long double>>(jsonArr);
        ASSERT_TRUE(longDouble.size() == 3);
        ASSERT_DOUBLE_EQ(10.1, longDouble[0]);
        ASSERT_DOUBLE_EQ(20.5, longDouble[1]);
        ASSERT_DOUBLE_EQ(30.9, longDouble[2]);

        std::vector<double> **vecDoublePtr = open_json::FromJson< std::vector<double> **>(jsonArr);
        ASSERT_TRUE((*vecDoublePtr)->size() == 3);
        ASSERT_DOUBLE_EQ(10.1, (**vecDoublePtr)[0]);
        ASSERT_DOUBLE_EQ(20.5, (**vecDoublePtr)[1]);
        ASSERT_DOUBLE_EQ(30.9, (**vecDoublePtr)[2]);
        delete *vecDoublePtr;
        delete vecDoublePtr;

        std::vector<double*> ptrVec = open_json::FromJson< std::vector<double*>>(jsonArr);
        ASSERT_TRUE(ptrVec.size() == 3);
        ASSERT_DOUBLE_EQ(10.1, *ptrVec[0]);
        ASSERT_DOUBLE_EQ(20.5, *ptrVec[1]);
        ASSERT_DOUBLE_EQ(30.9, *ptrVec[2]);
        for (auto p : ptrVec) {
            delete p;
        }

        std::vector<double*> *ptrVecPtr = open_json::FromJson< std::vector<double*>*>(jsonArr);
        ASSERT_TRUE(ptrVecPtr->size() == 3);
        ASSERT_DOUBLE_EQ(10.1, *(*ptrVecPtr)[0]);
        ASSERT_DOUBLE_EQ(20.5, *(*ptrVecPtr)[1]);
        ASSERT_DOUBLE_EQ(30.9, *(*ptrVecPtr)[2]);
        for (auto p : *ptrVecPtr) {
            delete p;
        }
        delete ptrVecPtr;
    }

    TEST_F(DeserializeVectorTest, TestString) {
        std::string FIRST_STR = "Hi there!";
        std::string SECOND_STR = "How do you like my work?";
        std::string THIRD_STR = "Is everything working";

        nlohmann::json jsonArr = nlohmann::json::array();
        jsonArr.push_back(FIRST_STR);
        jsonArr.push_back(SECOND_STR);
        jsonArr.push_back(THIRD_STR);

        std::vector<std::string> vec = open_json::FromJson<std::vector<std::string>>(jsonArr);
        ASSERT_TRUE(vec.size() == 3);
        ASSERT_EQ(0, std::string(FIRST_STR).compare(vec[0]));
        ASSERT_EQ(0, std::string(SECOND_STR).compare(vec[1]));
        ASSERT_EQ(0, std::string(THIRD_STR).compare(vec[2]));

        std::vector<std::string> *vecPtr = open_json::FromJson< std::vector<std::string> *>(jsonArr);
        ASSERT_TRUE(vecPtr->size() == 3);
        ASSERT_EQ(0, std::string(FIRST_STR).compare((*vecPtr)[0]));
        ASSERT_EQ(0, std::string(SECOND_STR).compare((*vecPtr)[1]));
        ASSERT_EQ(0, std::string(THIRD_STR).compare((*vecPtr)[2]));
        delete vecPtr;

        std::vector<std::string> **vecDoublePtr = open_json::FromJson< std::vector<std::string> **>(jsonArr);
        ASSERT_TRUE((*vecDoublePtr)->size() == 3);
        ASSERT_EQ(0, std::string(FIRST_STR).compare((**vecDoublePtr)[0]));
        ASSERT_EQ(0, std::string(SECOND_STR).compare((**vecDoublePtr)[1]));
        ASSERT_EQ(0, std::string(THIRD_STR).compare((**vecDoublePtr)[2]));
        delete *vecDoublePtr;
        delete vecDoublePtr;

        std::vector<std::string*> ptrVec = open_json::FromJson< std::vector<std::string*>>(jsonArr);
        ASSERT_TRUE(ptrVec.size() == 3);
        ASSERT_EQ(0, std::string(FIRST_STR).compare(*ptrVec[0]));
        ASSERT_EQ(0, std::string(SECOND_STR).compare(*ptrVec[1]));
        ASSERT_EQ(0, std::string(THIRD_STR).compare(*ptrVec[2]));
        for (auto p : ptrVec) {
            delete p;
        }

        std::vector<std::string*> *ptrVecPtr = open_json::FromJson< std::vector<std::string*>*>(jsonArr);
        ASSERT_TRUE(ptrVecPtr->size() == 3);
        ASSERT_EQ(0, std::string(FIRST_STR).compare(*(*ptrVecPtr)[0]));
        ASSERT_EQ(0, std::string(SECOND_STR).compare(*(*ptrVecPtr)[1]));
        ASSERT_EQ(0, std::string(THIRD_STR).compare(*(*ptrVecPtr)[2]));
        for (auto p : *ptrVecPtr) {
            delete p;
        }
        delete ptrVecPtr;
    }
}
#pragma GCC diagnostic pop
