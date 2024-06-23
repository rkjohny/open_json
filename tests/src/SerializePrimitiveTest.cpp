#include <gtest/gtest.h>
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

        int **ptr2Int = new int*(new int(-50));
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

        const long longValue = 20;
        jsonObject = open_json::ToJson(longValue);
        ASSERT_EQ(longValue, jsonObject.template get<const long>());

        unsigned long ulongVal = 30;
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
        delete *longPtr4;
        delete longPtr4;
    }

    TEST_F(SerializePrimitiveTest, PremitiveLongLong) {
        nlohmann::json jsonObject;

        jsonObject = open_json::ToJson(10L);
        ASSERT_TRUE(jsonObject.is_number());
        ASSERT_EQ(10L,  jsonObject.template get<long long>());

        const long long longValue = 20;
        jsonObject = open_json::ToJson(longValue);
        ASSERT_EQ(longValue, jsonObject.template get<const long long>());

        unsigned long long ulongVal = 30;
        jsonObject = open_json::ToJson(ulongVal);
        ASSERT_TRUE(jsonObject.is_number_unsigned());
        ASSERT_EQ(ulongVal, jsonObject.template get<unsigned long long>());

        const unsigned long long &ulongVal2 = ulongVal;
        jsonObject = open_json::ToJson(ulongVal2);
        ASSERT_EQ(ulongVal2, jsonObject.template get<const unsigned long long>());

        const long long *longPtr = &longValue;
        jsonObject = open_json::ToJson(longPtr);
        ASSERT_EQ(*longPtr, jsonObject.template get<const long long>());

        long long const *longPtr2 = &longValue;
        jsonObject = open_json::ToJson(longPtr2);
        ASSERT_EQ(*longPtr2, jsonObject.template get<const long long>());

        const long long * const longPtr3 = &longValue;
        jsonObject = open_json::ToJson(longPtr3);
        ASSERT_EQ(*longPtr3, jsonObject.template get<const long long>());

        const long long * const *longPtr4 = new long long*(new long long(-40L));
        jsonObject = open_json::ToJson(longPtr4);
        ASSERT_EQ(**longPtr4, jsonObject.template get<const long long>());
        delete *longPtr4;
        delete longPtr4;
    }

    TEST_F(SerializePrimitiveTest, PremitiveBool) {
        nlohmann::json jsonObject;

        jsonObject = open_json::ToJson(true);
        ASSERT_TRUE(jsonObject.is_boolean());
        ASSERT_EQ(true, jsonObject.template get<bool>());

        jsonObject = open_json::ToJson(false);
        ASSERT_TRUE(jsonObject.is_boolean());
        ASSERT_EQ(false, jsonObject.template get<bool>());

        bool boolVal = true;
        jsonObject = open_json::ToJson(boolVal);
        ASSERT_EQ(boolVal, jsonObject.template get<bool>());

        bool &boolVal2 = boolVal;
        jsonObject = open_json::ToJson(boolVal2);
        ASSERT_EQ(boolVal2, jsonObject.template get<bool>());

        bool *boolPtr = &boolVal;
        jsonObject = open_json::ToJson(boolPtr);
        ASSERT_EQ(*boolPtr, jsonObject.template get<bool>());

        bool **boolPtr2 = new bool*(new bool(false));
        jsonObject = open_json::ToJson(boolPtr2);
        ASSERT_EQ(**boolPtr2, jsonObject.template get<bool>());
        delete *boolPtr2;
        delete boolPtr2;
    }

    TEST_F(SerializePrimitiveTest, PremitiveFloat) {
        nlohmann::json jsonObject;

        jsonObject = open_json::ToJson(10.51F);
        ASSERT_TRUE(jsonObject.is_number_float());
        ASSERT_FLOAT_EQ(10.51, jsonObject.template get<float>());

        float decimalVal = 20.51;
        jsonObject = open_json::ToJson(decimalVal);
        ASSERT_FLOAT_EQ(decimalVal, jsonObject.template get<float>());

        const float &decimalVal2 = decimalVal;
        jsonObject = open_json::ToJson(decimalVal2);
        ASSERT_FLOAT_EQ(decimalVal2, jsonObject.template get<float>());

        const float *decimalPtr = &decimalVal;
        jsonObject = open_json::ToJson(decimalPtr);
        ASSERT_FLOAT_EQ(*decimalPtr, jsonObject.template get<float>());

        const float * const *decimalPtr2 = new float*(new float(-30.51F));
        jsonObject = open_json::ToJson(decimalPtr2);
        ASSERT_FLOAT_EQ(**decimalPtr2, jsonObject.template get<float>());
        delete *decimalPtr2;
        delete decimalPtr2;
    }

    TEST_F(SerializePrimitiveTest, PremitiveDouble) {
        nlohmann::json jsonObject;

        jsonObject = open_json::ToJson(10.51);
        ASSERT_DOUBLE_EQ(10.51, jsonObject.template get<double>());

        jsonObject = open_json::ToJson(double(10.51));
        ASSERT_DOUBLE_EQ(10.51, jsonObject.template get<double>());

        double decimalVal = 10.51;
        jsonObject = open_json::ToJson(decimalVal);
        ASSERT_DOUBLE_EQ(decimalVal, jsonObject.template get<double>());

        const double decimalVal2 = -20.51;
        jsonObject = open_json::ToJson(decimalVal2);
        ASSERT_DOUBLE_EQ(decimalVal2, jsonObject.template get<const double>());

        double &decimalVal3 = decimalVal;
        jsonObject = open_json::ToJson(decimalVal3);
        ASSERT_DOUBLE_EQ(decimalVal3, jsonObject.template get<double>());

        const double &decimalVal4 = decimalVal2;
        jsonObject = open_json::ToJson(decimalVal4);
        ASSERT_DOUBLE_EQ(decimalVal4, jsonObject.template get<const double>());

        double const &decimalValue5 = decimalVal;
        jsonObject = open_json::ToJson(decimalValue5);
        ASSERT_DOUBLE_EQ(decimalValue5, jsonObject.template get<const double>());

        double *decimalPtr = &decimalVal;
        jsonObject = open_json::ToJson(decimalPtr);
        ASSERT_DOUBLE_EQ(*decimalPtr, jsonObject.template get<double>());

        const double *decialPtr2 = &decimalVal;
        jsonObject = open_json::ToJson(decialPtr2);
        ASSERT_DOUBLE_EQ(*decialPtr2, jsonObject.template get<double>());

        double *const decimalPtr3 = &decimalVal;
        jsonObject = open_json::ToJson(decimalPtr3);
        ASSERT_DOUBLE_EQ(*decimalPtr3, jsonObject.template get<double>());

        const double *const decimalPtr4 = &decimalVal;
        jsonObject = open_json::ToJson(decimalPtr4);
        ASSERT_DOUBLE_EQ(*decimalPtr4, jsonObject.template get<double>());

        const double * const *decimalPtr5 = new double*(new double(-30.51));
        jsonObject = open_json::ToJson(decimalPtr5);
        ASSERT_DOUBLE_EQ(**decimalPtr5, jsonObject.template get<double>());
        delete *decimalPtr5;
        delete decimalPtr5;
    }

    TEST_F(SerializePrimitiveTest, PremitiveLongDouble) {
        nlohmann::json jsonObject;

        jsonObject = open_json::ToJson(10.51);
        ASSERT_DOUBLE_EQ(10.51, jsonObject.template get<double>());

        jsonObject = open_json::ToJson((long double)10.51);
        ASSERT_DOUBLE_EQ(10.51, jsonObject.template get<double>());

        long double decimalVal = 10.51;
        jsonObject = open_json::ToJson(decimalVal);
        ASSERT_DOUBLE_EQ(decimalVal, jsonObject.template get<long double>());

        const long double decimalVal2 = -20.51;
        jsonObject = open_json::ToJson(decimalVal2);
        ASSERT_DOUBLE_EQ(decimalVal2, jsonObject.template get<const long double>());

        long double &decimalVal3 = decimalVal;
        jsonObject = open_json::ToJson(decimalVal3);
        ASSERT_DOUBLE_EQ(decimalVal3, jsonObject.template get<long double>());

        const long double &decimalVal4 = decimalVal2;
        jsonObject = open_json::ToJson(decimalVal4);
        ASSERT_DOUBLE_EQ(decimalVal4, jsonObject.template get<const long double>());

        long double const &decimalValue5 = decimalVal;
        jsonObject = open_json::ToJson(decimalValue5);
        ASSERT_DOUBLE_EQ(decimalValue5, jsonObject.template get<const long double>());

        long double *decimalPtr = &decimalVal;
        jsonObject = open_json::ToJson(decimalPtr);
        ASSERT_DOUBLE_EQ(*decimalPtr, jsonObject.template get<long double>());

        const long double *decialPtr2 = &decimalVal;
        jsonObject = open_json::ToJson(decialPtr2);
        ASSERT_DOUBLE_EQ(*decialPtr2, jsonObject.template get<long double>());

        long double *const decimalPtr3 = &decimalVal;
        jsonObject = open_json::ToJson(decimalPtr3);
        ASSERT_DOUBLE_EQ(*decimalPtr3, jsonObject.template get<long double>());

        const long double *const decimalPtr4 = &decimalVal;
        jsonObject = open_json::ToJson(decimalPtr4);
        ASSERT_DOUBLE_EQ(*decimalPtr4, jsonObject.template get<long double>());

        const long double * const *decimalPtr5 = new long double*(new long double(-30.51));
        jsonObject = open_json::ToJson(decimalPtr5);
        ASSERT_DOUBLE_EQ(**decimalPtr5, jsonObject.template get<long double>());
        delete *decimalPtr5;
        delete decimalPtr5;
    }

    TEST_F(SerializePrimitiveTest, PremitiveChar) {
        nlohmann::json jsonObject;
        int intVal = 'A';
        char charValue = 'A';

        jsonObject = open_json::ToJson('A');
        ASSERT_EQ(65, jsonObject.template get<int>());
        ASSERT_EQ('A', jsonObject.template get<char>());

        jsonObject = open_json::ToJson(char('A'));
        ASSERT_EQ(65, jsonObject.template get<int>());
        ASSERT_EQ('A', jsonObject.template get<char>());

        jsonObject = open_json::ToJson(charValue);
        ASSERT_EQ(intVal, jsonObject.template get<int>());
        ASSERT_EQ(charValue, jsonObject.template get<char>());

        unsigned char ucharVal = 'A';
        jsonObject = open_json::ToJson(ucharVal);
        ASSERT_EQ(intVal, jsonObject.template get<int>());
        ASSERT_EQ(ucharVal, jsonObject.template get<unsigned char>());

        char *ptr1 = "Hello world!";
        jsonObject = open_json::ToJson(ptr1);
        ASSERT_EQ(ptr1, jsonObject.template get<std::string>());

        char **ptr2 = &ptr1;
        jsonObject = open_json::ToJson(ptr2);
        ASSERT_EQ(*ptr2, jsonObject.template get<std::string>());
    }

    TEST_F(SerializePrimitiveTest, PremitiveCharPtr) {
        nlohmann::json jsonObject;
        char *charPtr = "You are awsome!";

        jsonObject = open_json::ToJson("Hello World!");
        ASSERT_TRUE(jsonObject.is_string());
        ASSERT_EQ(0, std::string("Hello World!").compare(jsonObject.template get<std::string>()));

        jsonObject = open_json::ToJson(charPtr);
        ASSERT_EQ(0, std::string(charPtr).compare(jsonObject.template get<std::string>()));

        jsonObject = open_json::ToJson(std::move(charPtr));
        ASSERT_EQ(0, std::string(charPtr).compare(jsonObject.template get<std::string>()));

        const char *charPtr2 = charPtr;
        jsonObject = open_json::ToJson(charPtr2);
        ASSERT_EQ(0, std::string(charPtr2).compare(jsonObject.template get<std::string>()));

        jsonObject = open_json::ToJson(std::move(charPtr2));
        ASSERT_EQ(0, std::string(charPtr2).compare(jsonObject.template get<std::string>()));

        char *const charPtr3 = charPtr;
        jsonObject = open_json::ToJson(charPtr3);
        ASSERT_EQ(0, std::string(charPtr3).compare(jsonObject.template get<std::string>()));

        jsonObject = open_json::ToJson(std::move(charPtr3));
        ASSERT_EQ(0, std::string(charPtr3).compare(jsonObject.template get<std::string>()));

        const char *const charPtr4 = charPtr;
        jsonObject = open_json::ToJson(charPtr4);
        ASSERT_EQ(0, std::string(charPtr4).compare(jsonObject.template get<std::string>()));

        jsonObject = open_json::ToJson(std::move(charPtr4));
        ASSERT_EQ(0, std::string(charPtr4).compare(jsonObject.template get<std::string>()));;


        jsonObject = open_json::ToJson(*charPtr4);
        ASSERT_EQ(*charPtr4, jsonObject.template get<char>());
        ASSERT_EQ((int)*charPtr4, jsonObject.template get<int>());

        jsonObject = open_json::ToJson(std::move(*charPtr4));
        ASSERT_TRUE(*charPtr4 == jsonObject.template get<char>());
        ASSERT_TRUE((int) *charPtr4 == jsonObject.template get<int>());
    }

    TEST_F(SerializePrimitiveTest, STLString) {
        nlohmann::json jsonObject;
        std::string strVal;

        std::string str = "Hello World!";
        jsonObject = open_json::ToJson(std::move(str));
        ASSERT_EQ(0, str.compare(jsonObject.template get<std::string>()));

        jsonObject = open_json::ToJson(str);
        ASSERT_EQ(0, str.compare(jsonObject.template get<std::string>()));

        const std::string str2 = "C++ is awsome!";
        jsonObject = open_json::ToJson(std::move(str2));
        ASSERT_EQ(0, str2.compare(jsonObject.template get<std::string>()));

        jsonObject = open_json::ToJson(str2);
        ASSERT_EQ(0, str2.compare(jsonObject.template get<std::string>()));

        std::string *str3 = &str;
        jsonObject = open_json::ToJson(str3);
        ASSERT_EQ(0, str3->compare(jsonObject.template get<std::string>()));

        const std::string *str4 = &str;
        jsonObject = open_json::ToJson(str4);
        ASSERT_EQ(0, str4->compare(jsonObject.template get<std::string>()));

        std::string *const str5 = &str;
        jsonObject = open_json::ToJson(str5);
        ASSERT_EQ(0, str5->compare(jsonObject.template get<std::string>()));

        const std::string *const str6 = &str;
        jsonObject = open_json::ToJson(str6);
        ASSERT_EQ(0, str6->compare(jsonObject.template get<std::string>()));

        std::string **str7 = new std::string*(new std::string("Hi there!"));
        jsonObject = open_json::ToJson(str7);
        ASSERT_EQ(0, (*str7)->compare(jsonObject.template get<std::string>()));
        delete *str7;
        delete str7;
    }
}