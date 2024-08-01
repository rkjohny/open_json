#include <gtest/gtest.h>
#include <string>
#include "../../include/open_json.h"

using namespace std;
using namespace open_json;

namespace open_json_test {

#define A_TRUE(TYPE, OPERAND) \
    ASSERT_TRUE(OPERAND<TYPE&&>::value); \
    ASSERT_TRUE(OPERAND<TYPE&>::value); \
    ASSERT_TRUE(OPERAND<TYPE>::value); \
    ASSERT_TRUE(OPERAND<const TYPE&&>::value); \
    ASSERT_TRUE(OPERAND<const TYPE&>::value); \
    ASSERT_TRUE(OPERAND<const TYPE>::value);

#define A_FALSE(TYPE, OPERAND) \
    ASSERT_FALSE(OPERAND<TYPE&&>::value); \
    ASSERT_FALSE(OPERAND<TYPE&>::value); \
    ASSERT_FALSE(OPERAND<TYPE>::value); \
    ASSERT_FALSE(OPERAND<const TYPE&&>::value); \
    ASSERT_FALSE(OPERAND<const TYPE&>::value); \
    ASSERT_FALSE(OPERAND<const TYPE>::value);

    TEST(TypeTraitsTest, BoolTest) {
        //type: bool
        A_FALSE(bool, is_char);
        A_TRUE(bool, is_bool); //true
        A_FALSE(bool, is_int8);
        A_FALSE(bool, is_uint8);
        A_FALSE(bool, is_int16);
        A_FALSE(bool, is_uint16);
        A_FALSE(bool, is_int32);
        A_FALSE(bool, is_uint32);
        A_FALSE(bool, is_int64);
        A_FALSE(bool, is_uint64);
        A_FALSE(bool, is_integer);
        A_FALSE(bool, is_float);
        A_FALSE(bool, is_double);
        A_FALSE(bool, is_long_double);
        A_FALSE(bool, is_decimal);
        A_TRUE(bool, is_primitive); //true
        A_FALSE(bool, is_string);
        A_FALSE(bool, is_vector);
        A_FALSE(bool, open_json::is_class);
    }

    TEST(TypeTraitsTest, CharTest) {
        //type: char
        A_TRUE(char, is_char); //true
        A_FALSE(char, is_bool);
        A_FALSE(char, is_int8);
        A_FALSE(char, is_uint8);
        A_FALSE(char, is_int16);
        A_FALSE(char, is_uint16);
        A_FALSE(char, is_int32);
        A_FALSE(char, is_uint32);
        A_FALSE(char, is_int64);
        A_FALSE(char, is_uint64);
        A_FALSE(char, is_integer);
        A_FALSE(char, is_float);
        A_FALSE(char, is_double);
        A_FALSE(char, is_long_double);
        A_FALSE(char, is_decimal);
        A_TRUE(char, is_primitive); //true
        A_FALSE(char, is_string);
        A_FALSE(char, is_vector);
        A_FALSE(char, open_json::is_class);
    }

    TEST(TypeTraitsTest, Int8Test) {
        //type: signed char = uint8_t
        A_FALSE(int8_t, is_char);
        A_FALSE(int8_t, is_bool);
        A_TRUE(int8_t, is_int8); //true
        A_FALSE(int8_t, is_uint8);
        A_FALSE(int8_t, is_int16);
        A_FALSE(int8_t, is_uint16);
        A_FALSE(int8_t, is_int32);
        A_FALSE(int8_t, is_uint32);
        A_FALSE(int8_t, is_int64);
        A_FALSE(int8_t, is_uint64);
        A_TRUE(int8_t, is_integer); //true
        A_FALSE(int8_t, is_float);
        A_FALSE(int8_t, is_double);
        A_FALSE(int8_t, is_long_double);
        A_FALSE(int8_t, is_decimal);
        A_TRUE(int8_t, is_primitive); //true
        A_FALSE(int8_t, is_string);
        A_FALSE(int8_t, is_vector);
        A_FALSE(int8_t, open_json::is_class);

        //type: unsigned char = uint8_t
        A_FALSE(uint8_t, is_char);
        A_FALSE(uint8_t, is_bool);
        A_FALSE(uint8_t, is_int8);
        A_TRUE(uint8_t, is_uint8); //true
        A_FALSE(uint8_t, is_int16);
        A_FALSE(uint8_t, is_uint16);
        A_FALSE(uint8_t, is_int32);
        A_FALSE(uint8_t, is_uint32);
        A_FALSE(uint8_t, is_int64);
        A_FALSE(uint8_t, is_uint64);
        A_TRUE(uint8_t, is_integer); //true
        A_FALSE(uint8_t, is_float);
        A_FALSE(uint8_t, is_double);
        A_FALSE(uint8_t, is_long_double);
        A_FALSE(uint8_t, is_decimal);
        A_TRUE(uint8_t, is_primitive); //true
        A_FALSE(uint8_t, is_string);
        A_FALSE(uint8_t, is_vector);
        A_FALSE(uint8_t, open_json::is_class);
    }

    TEST(TypeTraitsTest, Int16Test) {
        //type: signed short int = int16_t
        A_FALSE(int16_t, is_char);
        A_FALSE(int16_t, is_bool);
        A_FALSE(int16_t, is_int8);
        A_FALSE(int16_t, is_uint8);
        A_TRUE(int16_t, is_int16); //true
        A_FALSE(int16_t, is_uint16);
        A_FALSE(int16_t, is_int32);
        A_FALSE(int16_t, is_uint32);
        A_FALSE(int16_t, is_int64);
        A_FALSE(int16_t, is_uint64);
        A_TRUE(int16_t, is_integer); //true
        A_FALSE(int16_t, is_float);
        A_FALSE(int16_t, is_double);
        A_FALSE(int16_t, is_long_double);
        A_FALSE(int16_t, is_decimal);
        A_TRUE(int16_t, is_primitive); //true
        A_FALSE(int16_t, is_string);
        A_FALSE(int16_t, is_vector);
        A_FALSE(int16_t, open_json::is_class);

        //type: unsigned short int = uint16_t
        A_FALSE(uint16_t, is_char);
        A_FALSE(uint16_t, is_bool);
        A_FALSE(uint16_t, is_int8);
        A_FALSE(uint16_t, is_uint8);
        A_FALSE(uint16_t, is_int16);
        A_TRUE(uint16_t, is_uint16); //true
        A_FALSE(uint16_t, is_int32);
        A_FALSE(uint16_t, is_uint32);
        A_FALSE(uint16_t, is_int64);
        A_FALSE(uint16_t, is_uint64);
        A_TRUE(uint16_t, is_integer); //true
        A_FALSE(uint16_t, is_float);
        A_FALSE(uint16_t, is_double);
        A_FALSE(uint16_t, is_long_double);
        A_FALSE(uint16_t, is_decimal);
        A_TRUE(uint16_t, is_primitive); //true
        A_FALSE(uint16_t, is_string);
        A_FALSE(uint16_t, is_vector);
        A_FALSE(uint16_t, open_json::is_class);
    }

    TEST(TypeTraitsTest, Int32Test) {
        //type: signed int = int32_t
        A_FALSE(int32_t, is_char);
        A_FALSE(int32_t, is_bool);
        A_FALSE(int32_t, is_int8);
        A_FALSE(int32_t, is_uint8);
        A_FALSE(int32_t, is_int16);
        A_FALSE(int32_t, is_uint16);
        A_TRUE(int32_t, is_int32); //true
        A_FALSE(int32_t, is_uint32);
        A_FALSE(int32_t, is_int64);
        A_FALSE(int32_t, is_uint64);
        A_TRUE(int32_t, is_integer); //true
        A_FALSE(int32_t, is_float);
        A_FALSE(int32_t, is_double);
        A_FALSE(int32_t, is_long_double);
        A_FALSE(int32_t, is_decimal);
        A_TRUE(int32_t, is_primitive); //true
        A_FALSE(int32_t, is_string);
        A_FALSE(int32_t, is_vector);
        A_FALSE(int32_t, open_json::is_class);

        //type: unsigned int = uint32_t
        A_FALSE(uint32_t, is_char);
        A_FALSE(uint32_t, is_bool);
        A_FALSE(uint32_t, is_int8);
        A_FALSE(uint32_t, is_uint8);
        A_FALSE(uint32_t, is_int16);
        A_FALSE(uint32_t, is_uint16);
        A_FALSE(uint32_t, is_int32);
        A_TRUE(uint32_t, is_uint32); // true
        A_FALSE(uint32_t, is_int64);
        A_FALSE(uint32_t, is_uint64);
        A_TRUE(uint32_t, is_integer); //true
        A_FALSE(uint32_t, is_float);
        A_FALSE(uint32_t, is_double);
        A_FALSE(uint32_t, is_long_double);
        A_FALSE(uint32_t, is_decimal);
        A_TRUE(uint32_t, is_primitive); //true
        A_FALSE(uint32_t, is_string);
        A_FALSE(uint32_t, is_vector);
        A_FALSE(uint32_t, open_json::is_class);
    }



    TEST(TypeTraitsTest, Int64Test) {
        /**
         * type: in 64 bit WORD SIZE signed long int = int64_t
         * in 32 bit WORD SIZE signed long long int = int64_t
         */
        A_FALSE(int64_t, is_char);
        A_FALSE(int64_t, is_bool);
        A_FALSE(int64_t, is_int8);
        A_FALSE(int64_t, is_uint8);
        A_FALSE(int64_t, is_int16);
        A_FALSE(int64_t, is_uint16);
        A_FALSE(int64_t, is_int32);
        A_FALSE(int64_t, is_uint32);
        A_TRUE(int64_t, is_int64); //true
        A_FALSE(int64_t, is_uint64);
        A_TRUE(int64_t, is_integer); //true
        A_FALSE(int64_t, is_float);
        A_FALSE(int64_t, is_double);
        A_FALSE(int64_t, is_long_double);
        A_FALSE(int64_t, is_decimal);
        A_TRUE(int64_t, is_primitive); //true
        A_FALSE(int64_t, is_string);
        A_FALSE(int64_t, is_vector);
        A_FALSE(int64_t, open_json::is_class);

        /**
         * type: in 64 bit WORD SIZE unsigned long int = uint64_t
         * in 32 bit WORD SIZE unsigned long long int = uint64_t
         */
        A_FALSE(uint64_t, is_char);
        A_FALSE(uint64_t, is_bool);
        A_FALSE(uint64_t, is_int8);
        A_FALSE(uint64_t, is_uint8);
        A_FALSE(uint64_t, is_int16);
        A_FALSE(uint64_t, is_uint16);
        A_FALSE(uint64_t, is_int32);
        A_FALSE(uint64_t, is_uint32);
        A_FALSE(uint64_t, is_int64);
        A_TRUE(uint64_t, is_uint64); //true
        A_TRUE(uint64_t, is_integer); //true
        A_FALSE(uint64_t, is_float);
        A_FALSE(uint64_t, is_double);
        A_FALSE(uint64_t, is_long_double);
        A_FALSE(uint64_t, is_decimal);
        A_TRUE(uint64_t, is_primitive); //true
        A_FALSE(uint64_t, is_string);
        A_FALSE(uint64_t, is_vector);
        A_FALSE(uint64_t, open_json::is_class);
    }

    TEST(TypeTraitsTest, LongTest) {
        /**
         * type: in 64 bit WORD SIZE signed long int = int64_t
         * in 32 bit WORD SIZE signed long long int = int64_t and long int = int32_t
         */
#if WORD_SIZE == 64

        A_FALSE(long long, is_char);
        A_FALSE(long long, is_bool);
        A_FALSE(long long, is_int8);
        A_FALSE(long long, is_uint8);
        A_FALSE(long long, is_int16);
        A_FALSE(long long, is_uint16);
        A_FALSE(long long, is_int32);
        A_FALSE(long long, is_uint32);
        A_TRUE(long long, is_int64); // true
        A_FALSE(long long, is_uint64);
        A_TRUE(long long, is_integer); //true
        A_FALSE(long long, is_float);
        A_FALSE(long long, is_double);
        A_FALSE(long long, is_long_double);
        A_FALSE(long long, is_decimal);
        A_TRUE(long long, is_primitive); //true
        A_FALSE(long long, is_string);
        A_FALSE(long long, is_vector);
        A_FALSE(long long, open_json::is_class);


        A_FALSE(unsigned long long, is_char);
        A_FALSE(unsigned long long, is_bool);
        A_FALSE(unsigned long long, is_int8);
        A_FALSE(unsigned long long, is_uint8);
        A_FALSE(unsigned long long, is_int16);
        A_FALSE(unsigned long long, is_uint16);
        A_FALSE(unsigned long long, is_int32);
        A_FALSE(unsigned long long, is_uint32);
        A_FALSE(unsigned long long, is_int64);
        A_TRUE(unsigned long long, is_uint64); //true
        A_TRUE(unsigned long long, is_integer); //true
        A_FALSE(unsigned long long, is_float);
        A_FALSE(unsigned long long, is_double);
        A_FALSE(unsigned long long, is_long_double);
        A_FALSE(unsigned long long, is_decimal);
        A_TRUE(unsigned long long, is_primitive); //true
        A_FALSE(unsigned long long, is_string);
        A_FALSE(unsigned long long, is_vector);
        A_FALSE(unsigned long long, open_json::is_class);

#elif WORD_SIZE == 32

        A_FALSE(long, is_char);
        A_FALSE(long, is_bool);
        A_FALSE(long, is_int8);
        A_FALSE(long, is_uint8);
        A_FALSE(long, is_int16);
        A_FALSE(long, is_uint16);
        A_TRUE(long, is_int32); //true
        A_FALSE(long, is_uint32);
        A_FALSE(long, is_int64);
        A_FALSE(long, is_uint64);
        A_TRUE(long, is_integer); //true
        A_FALSE(long, is_float);
        A_FALSE(long, is_double);
        A_FALSE(long, is_long_double);
        A_FALSE(long, is_decimal);
        A_TRUE(long, is_primitive); //true
        A_FALSE(long, is_string);
        A_FALSE(long, is_vector);
        A_FALSE(long, open_json::is_class);

        A_FALSE(unsigned long, is_char);
        A_FALSE(unsigned long, is_bool);
        A_FALSE(unsigned long, is_int8);
        A_FALSE(unsigned long, is_uint8);
        A_FALSE(unsigned long, is_int16);
        A_FALSE(unsigned long, is_uint16);
        A_FALSE(unsigned long, is_int32);
        A_TRUE(unsigned long, is_uint32); //true
        A_FALSE(unsigned long, is_int64);
        A_FALSE(unsigned long, is_uint64);
        A_TRUE(unsigned long, is_integer); //true
        A_FALSE(unsigned long, is_float);
        A_FALSE(unsigned long, is_double);
        A_FALSE(unsigned long, is_long_double);
        A_FALSE(unsigned long, is_decimal);
        A_TRUE(unsigned long, is_primitive); //true
        A_FALSE(unsigned long, is_string);
        A_FALSE(unsigned long, is_vector);
        A_FALSE(unsigned long long, open_json::is_class);

#endif
    }

    TEST(TypeTraitsTest, FloatTest) {
        // type = float
        A_FALSE(float, is_char);
        A_FALSE(float, is_bool);
        A_FALSE(float, is_int8);
        A_FALSE(float, is_uint8);
        A_FALSE(float, is_int16);
        A_FALSE(float, is_uint16);
        A_FALSE(float, is_int32);
        A_FALSE(float, is_uint32);
        A_FALSE(float, is_int64);
        A_FALSE(float, is_uint64);
        A_FALSE(float, is_integer);
        A_TRUE(float, is_float); //true
        A_FALSE(float, is_double);
        A_FALSE(float, is_long_double);
        A_TRUE(float, is_decimal); //true
        A_TRUE(float, is_primitive); //true
        A_FALSE(float, is_string);
        A_FALSE(float, is_vector);
        A_FALSE(float, open_json::is_class);
    }

    TEST(TypeTraitsTest, DoubleTest) {
        // type = double
        A_FALSE(double, is_char);
        A_FALSE(double, is_bool);
        A_FALSE(double, is_int8);
        A_FALSE(double, is_uint8);
        A_FALSE(double, is_int16);
        A_FALSE(double, is_uint16);
        A_FALSE(double, is_int32);
        A_FALSE(double, is_uint32);
        A_FALSE(double, is_int64);
        A_FALSE(double, is_uint64);
        A_FALSE(double, is_integer);
        A_FALSE(double, is_float);
        A_TRUE(double, is_double); //true
        A_FALSE(double, is_long_double);
        A_TRUE(double, is_decimal); //true
        A_TRUE(double, is_primitive); //true
        A_FALSE(double, is_string);
        A_FALSE(double, is_vector);
        A_FALSE(double, open_json::is_class);
    }

    TEST(TypeTraitsTest, LongDoubleTest) {
        // type = long double
        A_FALSE(long double, is_char);
        A_FALSE(long double, is_bool);
        A_FALSE(long double, is_int8);
        A_FALSE(long double, is_uint8);
        A_FALSE(long double, is_int16);
        A_FALSE(long double, is_uint16);
        A_FALSE(long double, is_int32);
        A_FALSE(long double, is_uint32);
        A_FALSE(long double, is_int64);
        A_FALSE(long double, is_uint64);
        A_FALSE(long double, is_integer);
        A_FALSE(long double, is_float);
        A_FALSE(long double, is_double);
        A_TRUE(long double, is_long_double); //true
        A_TRUE(long double, is_decimal); //true
        A_TRUE(long double, is_primitive); //true
        A_FALSE(long double, is_string);
        A_FALSE(long double, is_vector);
        A_FALSE(long double, open_json::is_class);
    }

    TEST(TypeTraitsTest, StringTest) {
        // type = std::string
        A_FALSE(std::string, is_char);
        A_FALSE(std::string, is_bool);
        A_FALSE(std::string, is_int8);
        A_FALSE(std::string, is_uint8);
        A_FALSE(std::string, is_int16);
        A_FALSE(std::string, is_uint16);
        A_FALSE(std::string, is_int32);
        A_FALSE(std::string, is_uint32);
        A_FALSE(std::string, is_int64);
        A_FALSE(std::string, is_uint64);
        A_FALSE(std::string, is_integer);
        A_FALSE(std::string, is_float);
        A_FALSE(std::string, is_double);
        A_FALSE(std::string, is_long_double);
        A_FALSE(std::string, is_decimal);
        A_FALSE(std::string, is_primitive);
        A_TRUE(std::string, is_string); //true
        A_FALSE(std::string, is_vector);
        A_FALSE(std::string, open_json::is_class); //false since std::string has been treaded as primitive
    }

    TEST(TypeTraitsTest, VectorTest) {
        //TODO: Not implemented
    }

    TEST(TypeTraitsTest, ObjectTest) {
        //TODO: Not implemented
    }
}