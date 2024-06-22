#include <gtest/gtest.h>
//#include "nlohmann/json.hpp"
#include "../../include/open_json.h"


namespace open_json_test {

    class SerializePrimitiveTest : public ::testing::Test {
    public:
        SerializePrimitiveTest() = default;
        virtual ~SerializePrimitiveTest() = default;

        void SetUp() override {
        }

        void TearDown() override {
        }

    }; // class SerializePrimitiveTest

    TEST_F(SerializePrimitiveTest, PremitiveInt) {

        nlohmann::json jsonObject;

        //serialize integer
        jsonObject = open_json::ToJson(10);
        ASSERT_TRUE(jsonObject.is_number_integer());
        ASSERT_EQ(10, jsonObject.template get<int>());

        int intValue = 10;
        jsonObject = open_json::ToJson(intValue);
        ASSERT_EQ(intValue, jsonObject.template get<int>());

        const int32_t int32Value = -20;
        jsonObject = open_json::ToJson(int32Value);
        ASSERT_EQ(int32Value, jsonObject.template get<const int32_t>());

        unsigned int uintValue = 30;
        jsonObject = open_json::ToJson(uintValue);
        ASSERT_TRUE(jsonObject.is_number_unsigned());
        ASSERT_EQ(uintValue, jsonObject.template get<unsigned int>());

        const uint32_t uint32Value = 40;
        jsonObject = open_json::ToJson(uint32Value);
        ASSERT_EQ(uint32Value, jsonObject.template get<const uint32_t>());

        int *ptrInt = new int();
        jsonObject = open_json::ToJson(ptrInt);
        ASSERT_EQ(*ptrInt, jsonObject.template get<const int>());
        delete ptrInt;

        uint32_t *ptrUInt32 = new uint32_t;
        jsonObject = open_json::ToJson(ptrUInt32);
        ASSERT_EQ(*ptrUInt32, jsonObject.template get<const int>());
        delete ptrUInt32;

        int **ptr2Int = new int*;
        *ptr2Int = new int (-50);
        jsonObject = open_json::ToJson(ptr2Int);
        ASSERT_EQ(**ptr2Int, jsonObject.template get<int>());
        delete *ptr2Int;
        delete ptr2Int;

        const int * const  *ptr3Int = new int*(new int(60));
        jsonObject = open_json::ToJson(ptr3Int);
        ASSERT_EQ(**ptr3Int, jsonObject.template get<int>());
        delete *ptr3Int;
        delete ptr3Int;
    }

    TEST_F(SerializePrimitiveTest, PremitiveLong) {
        nlohmann::json jsonObject;

        jsonObject = open_json::ToJson(10L);
        ASSERT_TRUE(jsonObject.is_number());
        ASSERT_EQ(10L,  jsonObject.template get<long>());

        const long  longValue = 20L;
        jsonObject = open_json::ToJson(longValue);
        ASSERT_EQ(longValue, jsonObject.template get<const long>());

        unsigned long ulongVal = 30L;
        jsonObject = open_json::ToJson(ulongVal);
        ASSERT_TRUE(jsonObject.is_number_unsigned());
        ASSERT_EQ(ulongVal, jsonObject.template get<unsigned long>());

        const unsigned long &ulongVal2 = ulongVal;
        jsonObject = open_json::ToJson(ulongVal2);
        ASSERT_EQ(ulongVal2, jsonObject.template get<const unsigned long>());

        const long *longPtr = &longValue;
        jsonObject = open_json::ToJson(longPtr);
        ASSERT_EQ(*longPtr, jsonObject.template get<const long>());

        long const *longPtr2 = &longValue;
        jsonObject = open_json::ToJson(longPtr2);
        ASSERT_EQ(*longPtr2, jsonObject.template get<const long>());

        const long * const longPtr3 = &longValue;
        jsonObject = open_json::ToJson(longPtr3);
        ASSERT_EQ(*longPtr3, jsonObject.template get<const long>());

        const long * const *longPtr4 = new long*(new long(-40L));
        jsonObject = open_json::ToJson(longPtr4);
        ASSERT_EQ(**longPtr4, jsonObject.template get<const long>());
    }
/*
    TEST_F(SerializePremitiveTest, PremitiveBool) {
        nlohmann::json jsonObject;
        bool boolVal = true;

        jsonObject = open_json::ToJson(true);
        ASSERT_EQ(true, jsonObject.as_bool());
        jsonObject = open_json::ToJson(bool(true));
        ASSERT_EQ(true, jsonObject.as_bool());
        jsonObject = open_json::ToJson(std::move(boolVal));
        ASSERT_EQ(boolVal, jsonObject.as_bool());

        jsonObject = open_json::ToJson(boolVal);
        ASSERT_EQ(boolVal, jsonObject.as_bool());
        const bool boolVal2 = true;
        jsonObject = open_json::ToJson(boolVal2);
        ASSERT_EQ(boolVal2, jsonObject.as_bool());
        bool &boolVal3 = boolVal;
        jsonObject = open_json::ToJson(boolVal3);
        ASSERT_EQ(boolVal3, jsonObject.as_bool());
        const bool &boolVal4 = boolVal2;
        jsonObject = open_json::ToJson(boolVal4);
        ASSERT_EQ(boolVal4, jsonObject.as_bool());
        bool const &boolValue5 = boolVal;
        jsonObject = open_json::ToJson(boolValue5);
        ASSERT_EQ(boolValue5, jsonObject.as_bool());

        bool *boolPtr = &boolVal;
        jsonObject = open_json::ToJson(boolPtr);
        ASSERT_EQ(*boolPtr, jsonObject.as_bool());
        const bool *boolPtr2 = &boolVal;
        jsonObject = open_json::ToJson(boolPtr2);
        ASSERT_EQ(*boolPtr2, jsonObject.as_bool());
        bool *const boolPtr3 = &boolVal;
        jsonObject = open_json::ToJson(boolPtr3);
        ASSERT_EQ(*boolPtr3, jsonObject.as_bool());
        const bool *const boolPtr4 = &boolVal;
        jsonObject = open_json::ToJson(boolPtr4);
        ASSERT_EQ(*boolPtr4, jsonObject.as_bool());
    }

    TEST_F(SerializePremitiveTest, PremitiveFloat) {
        nlohmann::json jsonObject;
        float decimalVal = 10.51;

        jsonObject = open_json::ToJson(10.51);
        ASSERT_FLOAT_EQ(10.51, jsonObject.as_double());
        jsonObject = open_json::ToJson(float(10.51));
        ASSERT_FLOAT_EQ(10.51, jsonObject.as_double());
        jsonObject = open_json::ToJson(std::move(decimalVal));
        ASSERT_FLOAT_EQ(decimalVal, jsonObject.as_double());

        jsonObject = open_json::ToJson(decimalVal);
        ASSERT_FLOAT_EQ(decimalVal, jsonObject.as_double());
        const float decimalVal2 = 10.51;
        jsonObject = open_json::ToJson(decimalVal2);
        ASSERT_FLOAT_EQ(decimalVal2, jsonObject.as_double());
        float &decimalVal3 = decimalVal;
        jsonObject = open_json::ToJson(decimalVal3);
        ASSERT_FLOAT_EQ(decimalVal3, jsonObject.as_double());
        const float &decimalVal4 = decimalVal2;
        jsonObject = open_json::ToJson(decimalVal4);
        ASSERT_FLOAT_EQ(decimalVal4, jsonObject.as_double());
        float const &decimalValue5 = decimalVal;
        jsonObject = open_json::ToJson(decimalValue5);
        ASSERT_FLOAT_EQ(decimalValue5, jsonObject.as_double());

        float *decimalPtr = &decimalVal;
        jsonObject = open_json::ToJson(decimalPtr);
        ASSERT_FLOAT_EQ(*decimalPtr, jsonObject.as_double());
        const float *decialPtr2 = &decimalVal;
        jsonObject = open_json::ToJson(decialPtr2);
        ASSERT_FLOAT_EQ(*decialPtr2, jsonObject.as_double());
        float *const decimalPtr3 = &decimalVal;
        jsonObject = open_json::ToJson(decimalPtr3);
        ASSERT_FLOAT_EQ(*decimalPtr3, jsonObject.as_double());
        const float *const decimalPtr4 = &decimalVal;
        jsonObject = open_json::ToJson(decimalPtr4);
        ASSERT_FLOAT_EQ(*decimalPtr4, jsonObject.as_double());
    }

    TEST_F(SerializePremitiveTest, PremitiveDouble) {
        nlohmann::json jsonObject;
        double decimalVal = 10.51;

        jsonObject = open_json::ToJson(10.51);
        ASSERT_DOUBLE_EQ(10.51, jsonObject.as_double());
        jsonObject = open_json::ToJson(double(10.51));
        ASSERT_DOUBLE_EQ(10.51, jsonObject.as_double());
        jsonObject = open_json::ToJson(std::move(decimalVal));
        ASSERT_DOUBLE_EQ(decimalVal, jsonObject.as_double());

        jsonObject = open_json::ToJson(decimalVal);
        ASSERT_DOUBLE_EQ(decimalVal, jsonObject.as_double());
        const double decimalVal2 = 10.51;
        jsonObject = open_json::ToJson(decimalVal2);
        ASSERT_DOUBLE_EQ(decimalVal2, jsonObject.as_double());
        double &decimalVal3 = decimalVal;
        jsonObject = open_json::ToJson(decimalVal3);
        ASSERT_DOUBLE_EQ(decimalVal3, jsonObject.as_double());
        const double &decimalVal4 = decimalVal2;
        jsonObject = open_json::ToJson(decimalVal4);
        ASSERT_DOUBLE_EQ(decimalVal4, jsonObject.as_double());
        double const &decimalValue5 = decimalVal;
        jsonObject = open_json::ToJson(decimalValue5);
        ASSERT_DOUBLE_EQ(decimalValue5, jsonObject.as_double());

        double *decimalPtr = &decimalVal;
        jsonObject = open_json::ToJson(decimalPtr);
        ASSERT_DOUBLE_EQ(*decimalPtr, jsonObject.as_double());
        const double *decialPtr2 = &decimalVal;
        jsonObject = open_json::ToJson(decialPtr2);
        ASSERT_DOUBLE_EQ(*decialPtr2, jsonObject.as_double());
        double *const decimalPtr3 = &decimalVal;
        jsonObject = open_json::ToJson(decimalPtr3);
        ASSERT_DOUBLE_EQ(*decimalPtr3, jsonObject.as_double());
        const double *const decimalPtr4 = &decimalVal;
        jsonObject = open_json::ToJson(decimalPtr4);
        ASSERT_DOUBLE_EQ(*decimalPtr4, jsonObject.as_double());
    }

    TEST_F(SerializePremitiveTest, PremitiveChar) {
        nlohmann::json jsonObject;
        int intVal = 'A';
        char charValue = 'A';

        jsonObject = open_json::ToJson('A');
        ASSERT_EQ(65, jsonObject.as_integer());
        jsonObject = open_json::ToJson(char('A'));
        ASSERT_EQ(65, jsonObject.as_integer());
        jsonObject = open_json::ToJson(std::move(charValue));
        ASSERT_EQ(intVal, jsonObject.as_integer());

        jsonObject = open_json::ToJson(charValue);
        ASSERT_TRUE(jsonObject.is_number());
        ASSERT_TRUE(jsonObject.as_number().is_int32());
        ASSERT_TRUE(jsonObject.as_number().to_int32() == intVal);
        ASSERT_EQ(intVal, jsonObject.as_integer());

        unsigned char ucharVal = 'A';
        jsonObject = open_json::ToJson(ucharVal);
        ASSERT_TRUE(jsonObject.is_number());
        ASSERT_TRUE(jsonObject.as_number().is_int32());
        ASSERT_TRUE(jsonObject.as_number().to_int32() == intVal);
        ASSERT_EQ(intVal, jsonObject.as_integer());

        const char charVal2 = 'A';
        jsonObject = open_json::ToJson(charVal2);
        ASSERT_EQ(intVal, jsonObject.as_integer());
        char &charVal3 = charValue;
        jsonObject = open_json::ToJson(charVal3);
        ASSERT_EQ(intVal, jsonObject.as_integer());
        const char &charVal4 = charVal2;
        jsonObject = open_json::ToJson(charVal4);
        ASSERT_EQ(intVal, jsonObject.as_integer());
        char const &charValue5 = intVal;
        jsonObject = open_json::ToJson(charValue5);
        ASSERT_EQ(intVal, jsonObject.as_integer());
    }

    TEST_F(SerializePremitiveTest, PremitiveCharPtr) {
        nlohmann::json jsonObject;
        std::string strVal;
        char *charPtr = strPtr;

        jsonObject = open_json::ToJson("Hello World!");
        strVal = utility::conversions::to_utf8string(jsonObject.as_string());
        ASSERT_EQ(0, std::string("Hello World!").compare(strVal));

        jsonObject = open_json::ToJson(std::move(charPtr));
        strVal = utility::conversions::to_utf8string(jsonObject.as_string());
        ASSERT_EQ(0, std::string(charPtr).compare(strVal));

        jsonObject = open_json::ToJson(charPtr);
        strVal = utility::conversions::to_utf8string(jsonObject.as_string());
        ASSERT_EQ(0, std::string(charPtr).compare(strVal));

        const char *charPtr2 = strPtr;
        jsonObject = open_json::ToJson(std::move(charPtr2));
        strVal = utility::conversions::to_utf8string(jsonObject.as_string());
        ASSERT_EQ(0, std::string(charPtr2).compare(strVal));

        jsonObject = open_json::ToJson(charPtr2);
        strVal = utility::conversions::to_utf8string(jsonObject.as_string());
        ASSERT_EQ(0, std::string(charPtr2).compare(strVal));

        char *const charPtr3 = strPtr;
        jsonObject = open_json::ToJson(std::move(charPtr3));
        strVal = utility::conversions::to_utf8string(jsonObject.as_string());
        ASSERT_EQ(0, std::string(charPtr3).compare(strVal));

        jsonObject = open_json::ToJson(charPtr3);
        strVal = utility::conversions::to_utf8string(jsonObject.as_string());
        ASSERT_EQ(0, std::string(charPtr3).compare(strVal));

        const char *const charPtr4 = strPtr;
        jsonObject = open_json::ToJson(std::move(charPtr4));
        strVal = utility::conversions::to_utf8string(jsonObject.as_string());
        ASSERT_EQ(0, std::string(charPtr4).compare(strVal));

        jsonObject = open_json::ToJson(charPtr4);
        strVal = utility::conversions::to_utf8string(jsonObject.as_string());
        ASSERT_EQ(0, std::string(charPtr4).compare(strVal));

        jsonObject = open_json::ToJson(*charPtr4);
        ASSERT_TRUE((int) *charPtr4 == jsonObject.as_integer());

        jsonObject = open_json::ToJson(std::move(*charPtr4));
        ASSERT_TRUE((int) *charPtr4 == jsonObject.as_integer());
    }

    TEST_F(SerializePremitiveTest, STLString) {
        nlohmann::json jsonObject;
        std::string strVal;

        std::string str = "hello world";
        jsonObject = open_json::ToJson(std::move(str));
        strVal = utility::conversions::to_utf8string(jsonObject.as_string());
        ASSERT_EQ(0, str.compare(strVal));

        jsonObject = open_json::ToJson(str);
        strVal = utility::conversions::to_utf8string(jsonObject.as_string());
        ASSERT_EQ(0, str.compare(strVal));

        const std::string str2 = "hello world";
        jsonObject = open_json::ToJson(std::move(str2));
        strVal = utility::conversions::to_utf8string(jsonObject.as_string());
        ASSERT_EQ(0, str2.compare(strVal));

        jsonObject = open_json::ToJson(str2);
        strVal = utility::conversions::to_utf8string(jsonObject.as_string());
        ASSERT_EQ(0, str2.compare(strVal));

        std::string *str3 = &str;
        jsonObject = open_json::ToJson(str3);
        strVal = utility::conversions::to_utf8string(jsonObject.as_string());
        ASSERT_EQ(0, str3->compare(strVal));

        const std::string *str4 = &str;
        jsonObject = open_json::ToJson(str4);
        strVal = utility::conversions::to_utf8string(jsonObject.as_string());
        ASSERT_EQ(0, str4->compare(strVal));

        std::string *const str5 = &str;
        jsonObject = open_json::ToJson(str5);
        strVal = utility::conversions::to_utf8string(jsonObject.as_string());
        ASSERT_EQ(0, str5->compare(strVal));

        const std::string *const str6 = &str;
        jsonObject = open_json::ToJson(str6);
        strVal = utility::conversions::to_utf8string(jsonObject.as_string());
        ASSERT_EQ(0, str6->compare(strVal));
    }
    */
}