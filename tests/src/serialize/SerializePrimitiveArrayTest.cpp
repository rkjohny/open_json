#include <gtest/gtest.h>
#include "../../../include/open_json.h"


namespace open_json_test::serialize::array_of_primitive_type {

    class SerializePrimitiveArrayTest : public ::testing::Test {
    public:
        SerializePrimitiveArrayTest() = default;

        virtual ~SerializePrimitiveArrayTest() = default;

        void SetUp() override {
        }

        void TearDown() override {
        }

    }; // class SerializePrimitiveArrayTest

    TEST_F(SerializePrimitiveArrayTest, IntArray) {
        nlohmann::json jsonObject;

        int intArr[] = {10, 20, 30, 40};

        jsonObject = open_json::ToJson(intArr, 4);
        ASSERT_TRUE(jsonObject.is_array());
        ASSERT_TRUE(jsonObject.size() == 4);
        int i = 0;
        for (auto &arrItem: intArr) {
            ASSERT_EQ(arrItem, jsonObject[i++].template get<int>());
        }

        int *intPtr = new int[]{10, 20, 30, 40};

        jsonObject = open_json::ToJson(intPtr, 4);
        ASSERT_TRUE(jsonObject.is_array());
        i = 0;
        for (auto &arrItem: jsonObject) {
            ASSERT_EQ(intPtr[i++], arrItem.template get<int>());
        }
        delete[] intPtr;

        int **intPtrArray = new int *[4]{new int(10), new int(20), new int(30), new int(4)};
        jsonObject = open_json::ToJson(intPtrArray, 4);
        ASSERT_TRUE(jsonObject.is_array());
        ASSERT_TRUE(jsonObject.size() == 4);
        i = 0;
        for (auto &arrItem: jsonObject) {
            ASSERT_EQ(*(intPtrArray[i++]), arrItem.template get<int>());
        }
        delete[] intPtrArray;

        int *intArrayPtr[4] = {new int(10), new int(20), new int(30), new int(4)};
        jsonObject = open_json::ToJson(intArrayPtr, 4);
        ASSERT_TRUE(jsonObject.is_array());
        ASSERT_TRUE(jsonObject.size() == 4);
        i = 0;
        for (auto &arrItem: jsonObject) {
            ASSERT_EQ(*(intArrayPtr[i++]), arrItem.template get<int>());
        }
        for (auto p: intArrayPtr) {
            delete p;
        }
    }

    TEST_F(SerializePrimitiveArrayTest, ChaArray) {
        nlohmann::json jsonObject;

        // string literal will be treated as character array;
        char *charPtr = "Hello World!";
        jsonObject = open_json::ToJson(charPtr, strlen(charPtr));
        ASSERT_TRUE(jsonObject.is_array());
        ASSERT_TRUE(jsonObject.size() == strlen(charPtr));
        int i = 0;
        for (auto &arrItem: jsonObject) {
            ASSERT_EQ(charPtr[i++], arrItem.template get<char>());
        }

        char charArr[] = {'a', 'b', 'c', 'd'};
        jsonObject = open_json::ToJson(charArr, 4);
        ASSERT_TRUE(jsonObject.is_array());
        ASSERT_TRUE(jsonObject.size() == 4);
        i = 0;
        for (auto &arrItem: jsonObject) {
            ASSERT_EQ(charArr[i++], arrItem.template get<char>());
        }
    }

    TEST_F(SerializePrimitiveArrayTest, StringArray) {
        nlohmann::json jsonObject;

        std::string strArray[] = {"Hi there!", "How are you?", "How is going?"};

        jsonObject = open_json::ToJson(strArray, 3);
        ASSERT_TRUE(jsonObject.is_array());
        ASSERT_TRUE(jsonObject.size() == 3);
        int i = 0;
        for (auto &arrItem: jsonObject) {
            ASSERT_EQ(0, strArray[i++].compare(arrItem.template get<std::string>()));
        }

        std::string *strPtr = new std::string[]{"Hi there!", "How are you?", "How is going?"};

        jsonObject = open_json::ToJson(strPtr, 3);
        ASSERT_TRUE(jsonObject.is_array());
        ASSERT_TRUE(jsonObject.size() == 3);
        i = 0;
        for (auto &arrItem: jsonObject) {
            ASSERT_EQ(0, strPtr[i++].compare(arrItem.template get<std::string>()));
        }
        delete[] strPtr;


        std::string *strPtrArray[] = {new std::string("Hi there!"), new std::string("How are you?"),
                                      new std::string("How is going?")};
        jsonObject = open_json::ToJson(strArray, 3);
        ASSERT_TRUE(jsonObject.is_array());
        ASSERT_TRUE(jsonObject.size() == 3);
        i = 0;
        for (auto &arrItem: jsonObject) {
            ASSERT_EQ(0, strPtrArray[i++]->compare(arrItem.template get<std::string>()));
        }
        for (auto p: strPtrArray) {
            delete p;
        }

        std::string **strArrayPtr = new std::string *[]{new std::string("Hi there!"), new std::string("How are you?"),
                                                        new std::string("How is going?")};
        jsonObject = open_json::ToJson(strArray, 3);
        ASSERT_TRUE(jsonObject.is_array());
        ASSERT_TRUE(jsonObject.size() == 3);
        i = 0;
        for (auto &arrItem: jsonObject) {
            ASSERT_EQ(0, strArrayPtr[i++]->compare(arrItem.template get<std::string>()));
        }
        delete[] strArrayPtr;
    }
}
