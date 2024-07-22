#include <gtest/gtest.h>
#include <string>
#include "../../include/open_json.h"

using namespace std;
using namespace open_json;

namespace open_json_test {

#define A_TRUE(TYPE, OPERAND) \
    ASSERT_TRUE(OPERAND<TYPE&&>::Value); \
    ASSERT_TRUE(OPERAND<TYPE&>::Value); \
    ASSERT_TRUE(OPERAND<TYPE>::Value); \
    ASSERT_TRUE(OPERAND<const TYPE&&>::Value); \
    ASSERT_TRUE(OPERAND<const TYPE&>::Value); \
    ASSERT_TRUE(OPERAND<const TYPE>::Value);

#define A_FALSE(TYPE, OPERAND) \
    ASSERT_FALSE(OPERAND<TYPE&&>::Value); \
    ASSERT_FALSE(OPERAND<TYPE&>::Value); \
    ASSERT_FALSE(OPERAND<TYPE>::Value); \
    ASSERT_FALSE(OPERAND<const TYPE&&>::Value); \
    ASSERT_FALSE(OPERAND<const TYPE&>::Value); \
    ASSERT_FALSE(OPERAND<const TYPE>::Value);

    TEST(TypeTraitsTest, BoolTest) {
        //type: bool
        A_FALSE(bool, Is_Char);
        A_TRUE(bool, Is_Bool); //true
        A_FALSE(bool, Is_Int8);
        A_FALSE(bool, Is_UInt8);
        A_FALSE(bool, Is_Int16);
        A_FALSE(bool, Is_UInt16);
        A_FALSE(bool, Is_Int32);
        A_FALSE(bool, Is_UInt32);
        A_FALSE(bool, Is_Int64);
        A_FALSE(bool, Is_UInt64);
        A_FALSE(bool, Is_Integer);
        A_FALSE(bool, Is_Float);
        A_FALSE(bool, Is_Double);
        A_FALSE(bool, Is_LongDouble);
        A_FALSE(bool, Is_Decimal);
        A_TRUE(bool, Is_Primitive); //true
        A_FALSE(bool, Is_String);
        A_FALSE(bool, Is_Vector);
        A_FALSE(bool, Is_Class);
    }

    TEST(TypeTraitsTest, CharTest) {
        //type: char
        A_TRUE(char, Is_Char); //true
        A_FALSE(char, Is_Bool);
        A_FALSE(char, Is_Int8);
        A_FALSE(char, Is_UInt8);
        A_FALSE(char, Is_Int16);
        A_FALSE(char, Is_UInt16);
        A_FALSE(char, Is_Int32);
        A_FALSE(char, Is_UInt32);
        A_FALSE(char, Is_Int64);
        A_FALSE(char, Is_UInt64);
        A_FALSE(char, Is_Integer);
        A_FALSE(char, Is_Float);
        A_FALSE(char, Is_Double);
        A_FALSE(char, Is_LongDouble);
        A_FALSE(char, Is_Decimal);
        A_TRUE(char, Is_Primitive); //true
        A_FALSE(char, Is_String);
        A_FALSE(char, Is_Vector);
        A_FALSE(char, Is_Class);
    }

    TEST(TypeTraitsTest, Int8Test) {
        //type: signed char = uint8_t
        A_FALSE(int8_t, Is_Char);
        A_FALSE(int8_t, Is_Bool);
        A_TRUE(int8_t, Is_Int8); //true
        A_FALSE(int8_t, Is_UInt8);
        A_FALSE(int8_t, Is_Int16);
        A_FALSE(int8_t, Is_UInt16);
        A_FALSE(int8_t, Is_Int32);
        A_FALSE(int8_t, Is_UInt32);
        A_FALSE(int8_t, Is_Int64);
        A_FALSE(int8_t, Is_UInt64);
        A_TRUE(int8_t, Is_Integer); //true
        A_FALSE(int8_t, Is_Float);
        A_FALSE(int8_t, Is_Double);
        A_FALSE(int8_t, Is_LongDouble);
        A_FALSE(int8_t, Is_Decimal);
        A_TRUE(int8_t, Is_Primitive); //true
        A_FALSE(int8_t, Is_String);
        A_FALSE(int8_t, Is_Vector);
        A_FALSE(int8_t, Is_Class);

        //type: unsigned char = uint8_t
        A_FALSE(uint8_t, Is_Char);
        A_FALSE(uint8_t, Is_Bool);
        A_FALSE(uint8_t, Is_Int8);
        A_TRUE(uint8_t, Is_UInt8); //true
        A_FALSE(uint8_t, Is_Int16);
        A_FALSE(uint8_t, Is_UInt16);
        A_FALSE(uint8_t, Is_Int32);
        A_FALSE(uint8_t, Is_UInt32);
        A_FALSE(uint8_t, Is_Int64);
        A_FALSE(uint8_t, Is_UInt64);
        A_TRUE(uint8_t, Is_Integer); //true
        A_FALSE(uint8_t, Is_Float);
        A_FALSE(uint8_t, Is_Double);
        A_FALSE(uint8_t, Is_LongDouble);
        A_FALSE(uint8_t, Is_Decimal);
        A_TRUE(uint8_t, Is_Primitive); //true
        A_FALSE(uint8_t, Is_String);
        A_FALSE(uint8_t, Is_Vector);
        A_FALSE(uint8_t, Is_Class);
    }

    TEST(TypeTraitsTest, Int16Test) {
        //type: signed short int = int16_t
        A_FALSE(int16_t, Is_Char);
        A_FALSE(int16_t, Is_Bool);
        A_FALSE(int16_t, Is_Int8);
        A_FALSE(int16_t, Is_UInt8);
        A_TRUE(int16_t, Is_Int16); //true
        A_FALSE(int16_t, Is_UInt16);
        A_FALSE(int16_t, Is_Int32);
        A_FALSE(int16_t, Is_UInt32);
        A_FALSE(int16_t, Is_Int64);
        A_FALSE(int16_t, Is_UInt64);
        A_TRUE(int16_t, Is_Integer); //true
        A_FALSE(int16_t, Is_Float);
        A_FALSE(int16_t, Is_Double);
        A_FALSE(int16_t, Is_LongDouble);
        A_FALSE(int16_t, Is_Decimal);
        A_TRUE(int16_t, Is_Primitive); //true
        A_FALSE(int16_t, Is_String);
        A_FALSE(int16_t, Is_Vector);
        A_FALSE(int16_t, Is_Class);

        //type: unsigned short int = uint16_t
        A_FALSE(uint16_t, Is_Char);
        A_FALSE(uint16_t, Is_Bool);
        A_FALSE(uint16_t, Is_Int8);
        A_FALSE(uint16_t, Is_UInt8);
        A_FALSE(uint16_t, Is_Int16);
        A_TRUE(uint16_t, Is_UInt16); //true
        A_FALSE(uint16_t, Is_Int32);
        A_FALSE(uint16_t, Is_UInt32);
        A_FALSE(uint16_t, Is_Int64);
        A_FALSE(uint16_t, Is_UInt64);
        A_TRUE(uint16_t, Is_Integer); //true
        A_FALSE(uint16_t, Is_Float);
        A_FALSE(uint16_t, Is_Double);
        A_FALSE(uint16_t, Is_LongDouble);
        A_FALSE(uint16_t, Is_Decimal);
        A_TRUE(uint16_t, Is_Primitive); //true
        A_FALSE(uint16_t, Is_String);
        A_FALSE(uint16_t, Is_Vector);
        A_FALSE(uint16_t, Is_Class);
    }

    TEST(TypeTraitsTest, Int32Test) {
        //type: signed int = int32_t
        A_FALSE(int32_t, Is_Char);
        A_FALSE(int32_t, Is_Bool);
        A_FALSE(int32_t, Is_Int8);
        A_FALSE(int32_t, Is_UInt8);
        A_FALSE(int32_t, Is_Int16);
        A_FALSE(int32_t, Is_UInt16);
        A_TRUE(int32_t, Is_Int32); //true
        A_FALSE(int32_t, Is_UInt32);
        A_FALSE(int32_t, Is_Int64);
        A_FALSE(int32_t, Is_UInt64);
        A_TRUE(int32_t, Is_Integer); //true
        A_FALSE(int32_t, Is_Float);
        A_FALSE(int32_t, Is_Double);
        A_FALSE(int32_t, Is_LongDouble);
        A_FALSE(int32_t, Is_Decimal);
        A_TRUE(int32_t, Is_Primitive); //true
        A_FALSE(int32_t, Is_String);
        A_FALSE(int32_t, Is_Vector);
        A_FALSE(int32_t, Is_Class);

        //type: unsigned int = uint32_t
        A_FALSE(uint32_t, Is_Char);
        A_FALSE(uint32_t, Is_Bool);
        A_FALSE(uint32_t, Is_Int8);
        A_FALSE(uint32_t, Is_UInt8);
        A_FALSE(uint32_t, Is_Int16);
        A_FALSE(uint32_t, Is_UInt16);
        A_FALSE(uint32_t, Is_Int32);
        A_TRUE(uint32_t, Is_UInt32); // true
        A_FALSE(uint32_t, Is_Int64);
        A_FALSE(uint32_t, Is_UInt64);
        A_TRUE(uint32_t, Is_Integer); //true
        A_FALSE(uint32_t, Is_Float);
        A_FALSE(uint32_t, Is_Double);
        A_FALSE(uint32_t, Is_LongDouble);
        A_FALSE(uint32_t, Is_Decimal);
        A_TRUE(uint32_t, Is_Primitive); //true
        A_FALSE(uint32_t, Is_String);
        A_FALSE(uint32_t, Is_Vector);
        A_FALSE(uint32_t, Is_Class);
    }



    TEST(TypeTraitsTest, Int64Test) {
        /**
         * type: in 64 bit WORD SIZE signed long int = int64_t
         * in 32 bit WORD SIZE signed long long int = int64_t
         */
        A_FALSE(int64_t, Is_Char);
        A_FALSE(int64_t, Is_Bool);
        A_FALSE(int64_t, Is_Int8);
        A_FALSE(int64_t, Is_UInt8);
        A_FALSE(int64_t, Is_Int16);
        A_FALSE(int64_t, Is_UInt16);
        A_FALSE(int64_t, Is_Int32);
        A_FALSE(int64_t, Is_UInt32);
        A_TRUE(int64_t, Is_Int64); //true
        A_FALSE(int64_t, Is_UInt64);
        A_TRUE(int64_t, Is_Integer); //true
        A_FALSE(int64_t, Is_Float);
        A_FALSE(int64_t, Is_Double);
        A_FALSE(int64_t, Is_LongDouble);
        A_FALSE(int64_t, Is_Decimal);
        A_TRUE(int64_t, Is_Primitive); //true
        A_FALSE(int64_t, Is_String);
        A_FALSE(int64_t, Is_Vector);
        A_FALSE(int64_t, Is_Class);

        /**
         * type: in 64 bit WORD SIZE unsigned long int = uint64_t
         * in 32 bit WORD SIZE unsigned long long int = uint64_t
         */
        A_FALSE(uint64_t, Is_Char);
        A_FALSE(uint64_t, Is_Bool);
        A_FALSE(uint64_t, Is_Int8);
        A_FALSE(uint64_t, Is_UInt8);
        A_FALSE(uint64_t, Is_Int16);
        A_FALSE(uint64_t, Is_UInt16);
        A_FALSE(uint64_t, Is_Int32);
        A_FALSE(uint64_t, Is_UInt32);
        A_FALSE(uint64_t, Is_Int64);
        A_TRUE(uint64_t, Is_UInt64); //true
        A_TRUE(uint64_t, Is_Integer); //true
        A_FALSE(uint64_t, Is_Float);
        A_FALSE(uint64_t, Is_Double);
        A_FALSE(uint64_t, Is_LongDouble);
        A_FALSE(uint64_t, Is_Decimal);
        A_TRUE(uint64_t, Is_Primitive); //true
        A_FALSE(uint64_t, Is_String);
        A_FALSE(uint64_t, Is_Vector);
        A_FALSE(uint64_t, Is_Class);
    }

    TEST(TypeTraitsTest, LongTest) {
        /**
         * type: in 64 bit WORD SIZE signed long int = int64_t
         * in 32 bit WORD SIZE signed long long int = int64_t and long int = int32_t
         */
#if WORD_SIZE == 64

        A_FALSE(long long, Is_Char);
        A_FALSE(long long, Is_Bool);
        A_FALSE(long long, Is_Int8);
        A_FALSE(long long, Is_UInt8);
        A_FALSE(long long, Is_Int16);
        A_FALSE(long long, Is_UInt16);
        A_FALSE(long long, Is_Int32);
        A_FALSE(long long, Is_UInt32);
        A_TRUE(long long, Is_Int64); // true
        A_FALSE(long long, Is_UInt64);
        A_TRUE(long long, Is_Integer); //true
        A_FALSE(long long, Is_Float);
        A_FALSE(long long, Is_Double);
        A_FALSE(long long, Is_LongDouble);
        A_FALSE(long long, Is_Decimal);
        A_TRUE(long long, Is_Primitive); //true
        A_FALSE(long long, Is_String);
        A_FALSE(long long, Is_Vector);
        A_FALSE(long long, Is_Class);


        A_FALSE(unsigned long long, Is_Char);
        A_FALSE(unsigned long long, Is_Bool);
        A_FALSE(unsigned long long, Is_Int8);
        A_FALSE(unsigned long long, Is_UInt8);
        A_FALSE(unsigned long long, Is_Int16);
        A_FALSE(unsigned long long, Is_UInt16);
        A_FALSE(unsigned long long, Is_Int32);
        A_FALSE(unsigned long long, Is_UInt32);
        A_FALSE(unsigned long long, Is_Int64);
        A_TRUE(unsigned long long, Is_UInt64); //true
        A_TRUE(unsigned long long, Is_Integer); //true
        A_FALSE(unsigned long long, Is_Float);
        A_FALSE(unsigned long long, Is_Double);
        A_FALSE(unsigned long long, Is_LongDouble);
        A_FALSE(unsigned long long, Is_Decimal);
        A_TRUE(unsigned long long, Is_Primitive); //true
        A_FALSE(unsigned long long, Is_String);
        A_FALSE(unsigned long long, Is_Vector);
        A_FALSE(unsigned long long, Is_Class);

#elif WORD_SIZE == 32

        A_FALSE(long, Is_Char);
        A_FALSE(long, Is_Bool);
        A_FALSE(long, Is_Int8);
        A_FALSE(long, Is_UInt8);
        A_FALSE(long, Is_Int16);
        A_FALSE(long, Is_UInt16);
        A_TRUE(long, Is_Int32); //true
        A_FALSE(long, Is_UInt32);
        A_FALSE(long, Is_Int64);
        A_FALSE(long, Is_UInt64);
        A_TRUE(long, Is_Integer); //true
        A_FALSE(long, Is_Float);
        A_FALSE(long, Is_Double);
        A_FALSE(long, Is_LongDouble);
        A_FALSE(long, Is_Decimal);
        A_TRUE(long, Is_Primitive); //true
        A_FALSE(long, Is_String);
        A_FALSE(long, Is_Vector);
        A_FALSE(long, Is_Class);

        A_FALSE(unsigned long, Is_Char);
        A_FALSE(unsigned long, Is_Bool);
        A_FALSE(unsigned long, Is_Int8);
        A_FALSE(unsigned long, Is_UInt8);
        A_FALSE(unsigned long, Is_Int16);
        A_FALSE(unsigned long, Is_UInt16);
        A_FALSE(unsigned long, Is_Int32);
        A_TRUE(unsigned long, Is_UInt32); //true
        A_FALSE(unsigned long, Is_Int64);
        A_FALSE(unsigned long, Is_UInt64);
        A_TRUE(unsigned long, Is_Integer); //true
        A_FALSE(unsigned long, Is_Float);
        A_FALSE(unsigned long, Is_Double);
        A_FALSE(unsigned long, Is_LongDouble);
        A_FALSE(unsigned long, Is_Decimal);
        A_TRUE(unsigned long, Is_Primitive); //true
        A_FALSE(unsigned long, Is_String);
        A_FALSE(unsigned long, Is_Vector);
        A_FALSE(unsigned long long, Is_Class);

#endif
    }

    TEST(TypeTraitsTest, FloatTest) {
        // type = float
        A_FALSE(float, Is_Char);
        A_FALSE(float, Is_Bool);
        A_FALSE(float, Is_Int8);
        A_FALSE(float, Is_UInt8);
        A_FALSE(float, Is_Int16);
        A_FALSE(float, Is_UInt16);
        A_FALSE(float, Is_Int32);
        A_FALSE(float, Is_UInt32);
        A_FALSE(float, Is_Int64);
        A_FALSE(float, Is_UInt64);
        A_FALSE(float, Is_Integer);
        A_TRUE(float, Is_Float); //true
        A_FALSE(float, Is_Double);
        A_FALSE(float, Is_LongDouble);
        A_TRUE(float, Is_Decimal); //true
        A_TRUE(float, Is_Primitive); //true
        A_FALSE(float, Is_String);
        A_FALSE(float, Is_Vector);
        A_FALSE(float, Is_Class);
    }

    TEST(TypeTraitsTest, DoubleTest) {
        // type = double
        A_FALSE(double, Is_Char);
        A_FALSE(double, Is_Bool);
        A_FALSE(double, Is_Int8);
        A_FALSE(double, Is_UInt8);
        A_FALSE(double, Is_Int16);
        A_FALSE(double, Is_UInt16);
        A_FALSE(double, Is_Int32);
        A_FALSE(double, Is_UInt32);
        A_FALSE(double, Is_Int64);
        A_FALSE(double, Is_UInt64);
        A_FALSE(double, Is_Integer);
        A_FALSE(double, Is_Float);
        A_TRUE(double, Is_Double); //true
        A_FALSE(double, Is_LongDouble);
        A_TRUE(double, Is_Decimal); //true
        A_TRUE(double, Is_Primitive); //true
        A_FALSE(double, Is_String);
        A_FALSE(double, Is_Vector);
        A_FALSE(double, Is_Class);
    }

    TEST(TypeTraitsTest, LongDoubleTest) {
        // type = long double
        A_FALSE(long double, Is_Char);
        A_FALSE(long double, Is_Bool);
        A_FALSE(long double, Is_Int8);
        A_FALSE(long double, Is_UInt8);
        A_FALSE(long double, Is_Int16);
        A_FALSE(long double, Is_UInt16);
        A_FALSE(long double, Is_Int32);
        A_FALSE(long double, Is_UInt32);
        A_FALSE(long double, Is_Int64);
        A_FALSE(long double, Is_UInt64);
        A_FALSE(long double, Is_Integer);
        A_FALSE(long double, Is_Float);
        A_FALSE(long double, Is_Double);
        A_TRUE(long double, Is_LongDouble); //true
        A_TRUE(long double, Is_Decimal); //true
        A_TRUE(long double, Is_Primitive); //true
        A_FALSE(long double, Is_String);
        A_FALSE(long double, Is_Vector);
        A_FALSE(long double, Is_Class);
    }

    TEST(TypeTraitsTest, StringTest) {
        // type = std::string
        A_FALSE(std::string, Is_Char);
        A_FALSE(std::string, Is_Bool);
        A_FALSE(std::string, Is_Int8);
        A_FALSE(std::string, Is_UInt8);
        A_FALSE(std::string, Is_Int16);
        A_FALSE(std::string, Is_UInt16);
        A_FALSE(std::string, Is_Int32);
        A_FALSE(std::string, Is_UInt32);
        A_FALSE(std::string, Is_Int64);
        A_FALSE(std::string, Is_UInt64);
        A_FALSE(std::string, Is_Integer);
        A_FALSE(std::string, Is_Float);
        A_FALSE(std::string, Is_Double);
        A_FALSE(std::string, Is_LongDouble);
        A_FALSE(std::string, Is_Decimal);
        A_FALSE(std::string, Is_Primitive);
        A_TRUE(std::string, Is_String); //true
        A_FALSE(std::string, Is_Vector);
        A_FALSE(std::string, Is_Class); //false since std::string has been treaded as primitive
    }

    TEST(TypeTraitsTest, VectorTest) {
        //TODO: Not implemented
    }

    TEST(TypeTraitsTest, ObjectTest) {
        //TODO: Not implemented
    }
} //namespace CmarshalTest