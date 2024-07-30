#include <gtest/gtest.h>
#include <math.h>
#include "../../../include/open_json.h"


namespace open_json_test::deserialize::primitive_types {

    class DeserializePrimitiveTest : public ::testing::Test {
    public:
        DeserializePrimitiveTest() = default;

        virtual ~DeserializePrimitiveTest() = default;

        void SetUp() override {
        }

        void TearDown() override {
        }

    }; // class DeserializePrimitiveTest


    TEST_F(DeserializePrimitiveTest, PremitiveInt8) {
        nlohmann::json jsonObject;

        int8_t MAX8 = static_cast<int8_t>(pow(2, 7) - 1);
        int8_t MIN8 = static_cast<int8_t>(pow(2, 7) * -1);

        uint8_t UMAX8 = static_cast<uint8_t>(pow(2, 8) - 1);
        uint8_t UMIN8 = 0;

        //std::cout << "MAX8 = " << MAX8 << " MIN8 = " << MIN8 << std::endl;
        //std::cout << "UMAX8 = " << UMAX8 << " UMIN8 = " << UMIN8 << std::endl;

        jsonObject = MIN8;
        int8_t min8 = open_json::FromJson<int8_t>(jsonObject);
        ASSERT_EQ(MIN8, min8);

        jsonObject = MAX8;
        int8_t max8 = open_json::FromJson<int8_t>(jsonObject);
        ASSERT_EQ(MAX8, max8);

        jsonObject = -1;
        int8_t *minusOne = open_json::FromJson<int8_t *>(jsonObject);
        ASSERT_EQ(-1, *minusOne);
        delete minusOne;

        jsonObject = 1;
        int8_t **plusOne = open_json::FromJson<int8_t **>(jsonObject);
        ASSERT_EQ(1, **plusOne);
        delete *plusOne;
        delete plusOne;

        jsonObject = UMIN8;
        uint8_t umin8 = open_json::FromJson<uint8_t>(jsonObject);
        ASSERT_EQ(UMIN8, umin8);

        jsonObject = UMAX8;
        uint8_t *umax8 = open_json::FromJson<uint8_t *>(jsonObject);
        ASSERT_EQ(UMAX8, *umax8);
        delete umax8;

        jsonObject = 1;
        uint8_t **uint8DoublePtr = open_json::FromJson<uint8_t **>(jsonObject);
        ASSERT_EQ(1, **uint8DoublePtr);
        delete *uint8DoublePtr;
        delete uint8DoublePtr;
    }

    TEST_F(DeserializePrimitiveTest, PremitiveInt16) {
        nlohmann::json jsonObject;

        int16_t MAX16 = static_cast<int16_t>(pow(2, 15) - 1);
        int16_t MIN16 = static_cast<int16_t>(pow(2, 15) * -1);

        uint16_t UMAX16 = static_cast<uint16_t>(pow(2, 16) - 1);
        uint16_t UMIN16 = 0;

        //std::cout << "MAX16 = " << MAX16 << " MIN16 = " << MIN16 << std::endl;
        //std::cout << "UMAX16 = " << UMAX16 << " UMIN16 = " << UMIN16 << std::endl;

        jsonObject = MIN16;
        int16_t min16 = open_json::FromJson<int16_t>(jsonObject);
        ASSERT_EQ(MIN16, min16);

        jsonObject = MAX16;
        int16_t max16 = open_json::FromJson<int16_t>(jsonObject);
        ASSERT_EQ(MAX16, max16);

        jsonObject = -1;
        int16_t *minusOne = open_json::FromJson<int16_t *>(jsonObject);
        ASSERT_EQ(-1, *minusOne);
        delete minusOne;

        jsonObject = 1;
        int16_t **plusOne = open_json::FromJson<int16_t **>(jsonObject);
        ASSERT_EQ(1, **plusOne);
        delete *plusOne;
        delete plusOne;

        jsonObject = UMIN16;
        uint16_t umin16 = open_json::FromJson<uint16_t>(jsonObject);
        ASSERT_EQ(UMIN16, umin16);

        jsonObject = UMAX16;
        uint16_t *umax16 = open_json::FromJson<uint16_t *>(jsonObject);
        ASSERT_EQ(UMAX16, *umax16);
        delete umax16;

        jsonObject = 1;
        uint16_t **uint16DoublePtr = open_json::FromJson<uint16_t **>(jsonObject);
        ASSERT_EQ(1, **uint16DoublePtr);
        delete *uint16DoublePtr;
        delete uint16DoublePtr;
    }

    TEST_F(DeserializePrimitiveTest, Premitive32) {
        nlohmann::json jsonObject;

        int32_t MAX32 = static_cast<int32_t>(pow(2, 31) - 1);
        int32_t MIN32 = static_cast<int32_t>(pow(2, 31) * -1);

        uint32_t UMAX32 = static_cast<uint32_t>(pow(2, 32) - 1);
        uint32_t UMIN32 = 0;

        //std::cout << "MAX32 = " << MAX32 << " MIN32 = " << MIN32 << std::endl;
        //std::cout << "UMAX32 = " << UMAX32 << " UMIN32 = " << UMIN32 << std::endl;

        jsonObject = MIN32;
        int32_t min32 = open_json::FromJson<int32_t>(jsonObject);
        ASSERT_EQ(MIN32, min32);

        jsonObject = MAX32;
        int32_t max32 = open_json::FromJson<int32_t>(jsonObject);
        ASSERT_EQ(MAX32, max32);

        jsonObject = -1;
        int32_t *minusOne = open_json::FromJson<int32_t *>(jsonObject);
        ASSERT_EQ(-1, *minusOne);
        delete minusOne;

        jsonObject = 1;
        int32_t **plusOne = open_json::FromJson<int32_t **>(jsonObject);
        ASSERT_EQ(1, **plusOne);
        delete *plusOne;
        delete plusOne;

        jsonObject = UMIN32;
        uint32_t umin32 = open_json::FromJson<uint32_t>(jsonObject);
        ASSERT_EQ(UMIN32, umin32);

        jsonObject = UMAX32;
        uint32_t *umax32 = open_json::FromJson<uint32_t *>(jsonObject);
        ASSERT_EQ(UMAX32, *umax32);
        delete umax32;

        jsonObject = 1;
        uint32_t **uint32DoublePtr = open_json::FromJson<uint32_t **>(jsonObject);
        ASSERT_EQ(1, **uint32DoublePtr);
        delete *uint32DoublePtr;
        delete uint32DoublePtr;
    }

    TEST_F(DeserializePrimitiveTest, PremitiveInt64) {
        nlohmann::json jsonObject;

        int64_t MAX64 = static_cast<int64_t>(pow(2, 63) - 1);
        int64_t MIN64 = static_cast<int64_t>(pow(2, 63) * -1);

        uint64_t UMAX64 = static_cast<uint64_t>(pow(2, 64) - 1);
        uint64_t UMIN64 = 0;

        //std::cout << "MAX64 = " << MAX64 << " MIN64 = " << MIN64 << std::endl;
        //std::cout << "UMAX64 = " << UMAX64 << " UMIN64 = " << UMIN64 << std::endl;


        jsonObject = MIN64;
        int64_t min64 = open_json::FromJson<int64_t>(jsonObject);
        ASSERT_EQ(MIN64, min64);

        jsonObject = MAX64;
        int64_t max64 = open_json::FromJson<int64_t>(jsonObject);
        ASSERT_EQ(MAX64, max64);

        jsonObject = -1;
        int64_t *minusOne = open_json::FromJson<int64_t *>(jsonObject);
        ASSERT_EQ(-1, *minusOne);
        delete minusOne;

        jsonObject = 1;
        int64_t **plusOne = open_json::FromJson<int64_t **>(jsonObject);
        ASSERT_EQ(1, **plusOne);
        delete *plusOne;
        delete plusOne;

        jsonObject = UMIN64;
        uint64_t umin64 = open_json::FromJson<uint64_t>(jsonObject);
        ASSERT_EQ(UMIN64, umin64);

        jsonObject = UMAX64;
        uint64_t *umax64 = open_json::FromJson<uint64_t *>(jsonObject);
        ASSERT_EQ(UMAX64, *umax64);
        delete umax64;

        jsonObject = 1;
        uint64_t **uint64DoublePtr = open_json::FromJson<uint64_t **>(jsonObject);
        ASSERT_EQ(1, **uint64DoublePtr);
        delete *uint64DoublePtr;
        delete uint64DoublePtr;
    }

    TEST_F(DeserializePrimitiveTest, PremitiveBool) {
        nlohmann::json jsonObject;

        jsonObject = true;
        bool bTrue = open_json::FromJson<bool>(jsonObject);
        ASSERT_TRUE(bTrue);

        jsonObject = true;
        bool *bTruePtr = open_json::FromJson<bool *>(jsonObject);
        ASSERT_TRUE(*bTruePtr);
        delete bTruePtr;

        jsonObject = true;
        bool **bTrueDPtr = open_json::FromJson<bool **>(jsonObject);
        ASSERT_TRUE(**bTrueDPtr);
        delete *bTrueDPtr;
        delete bTrueDPtr;

        jsonObject = false;
        bool bFalse = open_json::FromJson<bool>(jsonObject);
        ASSERT_FALSE(bFalse);

        jsonObject = false;
        bool *bFalsePtr = open_json::FromJson<bool *>(jsonObject);
        ASSERT_FALSE(*bFalsePtr);
        delete bFalsePtr;

        jsonObject = false;
        bool **bFalseDoublePtr = open_json::FromJson<bool **>(jsonObject);
        ASSERT_FALSE(**bFalseDoublePtr);
        delete *bFalseDoublePtr;
        delete bFalseDoublePtr;
    }

    TEST_F(DeserializePrimitiveTest, PremitiveFloat) {
        nlohmann::json jsonObject;

        jsonObject = 10.5F;
        float floatValue = open_json::FromJson<float>(jsonObject);
        ASSERT_EQ(10.5F, floatValue);

        jsonObject = 10.1F;
        float *floatPtr = open_json::FromJson<float *>(jsonObject);
        ASSERT_EQ(10.1F, *floatPtr);
        delete floatPtr;

        jsonObject = 10.9F;
        float **floatDoublePtr = open_json::FromJson<float **>(jsonObject);
        ASSERT_EQ(10.9F, **floatDoublePtr);
        delete *floatDoublePtr;
        delete floatDoublePtr;
    }

    TEST_F(DeserializePrimitiveTest, PremitiveDouble) {
        nlohmann::json jsonObject;

        jsonObject = 10.5F;
        double doubleValue = open_json::FromJson<double>(jsonObject);
        ASSERT_EQ(10.5F, doubleValue);

        jsonObject = 10.1F;
        double *doublePtr = open_json::FromJson<double *>(jsonObject);
        ASSERT_EQ(10.1F, *doublePtr);
        delete doublePtr;

        jsonObject = 10.9F;
        double **doubleDoublePtr = open_json::FromJson<double **>(jsonObject);
        ASSERT_EQ(10.9F, **doubleDoublePtr);
        delete *doubleDoublePtr;
        delete doubleDoublePtr;
    }

    TEST_F(DeserializePrimitiveTest, PremitiveLongDouble) {
        nlohmann::json jsonObject;

        jsonObject = 10.5F;
        long double doubleValue = open_json::FromJson<long double>(jsonObject);
        ASSERT_EQ(10.5F, doubleValue);

        jsonObject = 10.1F;
        long double *doublePtr = open_json::FromJson<long double *>(jsonObject);
        ASSERT_EQ(10.1F, *doublePtr);
        delete doublePtr;

        jsonObject = 10.9F;
        long double **doubleDoublePtr = open_json::FromJson<long double **>(jsonObject);
        ASSERT_EQ(10.9F, **doubleDoublePtr);
        delete *doubleDoublePtr;
        delete doubleDoublePtr;
    }


    TEST_F(DeserializePrimitiveTest, PremitiveChar) {
        nlohmann::json jsonObject;
        int IntValue = 'A';
        signed char CharValue = 'A';
        unsigned char UCharValue = 'Z';

        jsonObject = CharValue;
        char charValue = open_json::FromJson<char>(jsonObject);
        ASSERT_EQ(IntValue, charValue);
        ASSERT_EQ(CharValue, charValue);

        jsonObject = CharValue;
        char *charPtr = open_json::FromJson<char *>(jsonObject);
        ASSERT_EQ(IntValue, *charPtr);
        ASSERT_EQ(CharValue, *charPtr);
        delete charPtr;

        jsonObject = CharValue;
        char **charDoublePtr = open_json::FromJson<char **>(jsonObject);
        ASSERT_EQ(IntValue, **charDoublePtr);
        ASSERT_EQ(CharValue, **charDoublePtr);
        delete *charDoublePtr;
        delete charDoublePtr;

        jsonObject = UCharValue;
        unsigned char uCharValue = open_json::FromJson<unsigned char>(jsonObject);
        ASSERT_EQ(UCharValue, uCharValue);

        jsonObject = UCharValue;
        unsigned char *uCharPtr = open_json::FromJson<unsigned char *>(jsonObject);
        ASSERT_EQ(UCharValue, *uCharPtr);
        delete uCharPtr;

        jsonObject = UCharValue;
        unsigned char **uCharDoublePtr = open_json::FromJson<unsigned char **>(jsonObject);
        ASSERT_EQ(UCharValue, **uCharDoublePtr);
        delete *uCharDoublePtr;
        delete uCharDoublePtr;
    }

    TEST_F(DeserializePrimitiveTest, STLString) {
        nlohmann::json jsonObject;
        std::string STR = "Hello World!";

        jsonObject = STR;
        std::string str = open_json::FromJson<std::string>(jsonObject);
        ASSERT_EQ(0, STR.compare(str));

        jsonObject = STR;
        std::string *strPtr = open_json::FromJson<std::string *>(jsonObject);
        ASSERT_EQ(0, STR.compare(*strPtr));
        delete strPtr;

        jsonObject = STR;
        std::string **strDoublePtr = open_json::FromJson<std::string **>(jsonObject);
        ASSERT_EQ(0, STR.compare(**strDoublePtr));
        delete *strDoublePtr;
        delete strDoublePtr;
    }
}
