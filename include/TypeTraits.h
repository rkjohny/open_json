#ifndef OPEN_JSON_TYPETRAITS_H
#define OPEN_JSON_TYPETRAITS_H


#include <stdint.h>
#include <type_traits>
#include <string>
#include <vector>


namespace open_json {

    template<class T>
    struct Remove_CV {
        typedef typename std::remove_cv<T>::type Type;
    };

    template<class T>
    struct Remove_CVR {
        typedef typename std::remove_reference<typename Remove_CV<T>::Type>::type Type;
    };

    template<class T>
    struct Remove_CVRP {
        typedef typename std::remove_pointer<typename Remove_CVR<T>::Type>::type Type;
    };

    /**
     * type char
     * it may vary among platforms
     */
    template<class T>
    struct Is_Char_Type {
        static const bool Value = false;
    };

    template<>
    struct Is_Char_Type<char> {
        static const bool Value = true;
    };

    template<>
    struct Is_Char_Type<const char> {
        static const bool Value = true;
    };

    template<class T>
    struct Is_Char {
    private:
        typedef typename Remove_CVR<T>::Type U;
    public:
        static const bool Value = Is_Char_Type<U>::Value;
    };

    /**
     * type: signed char, byte
     */
    template<class T>
    struct Is_Int8_Type {
        static const bool Value = false;
    };

    template<>
    struct Is_Int8_Type<int8_t> {
        static const bool Value = true;
    };

    template<>
    struct Is_Int8_Type<const int8_t> {
        static const bool Value = true;
    };

    template<class T>
    struct Is_Int8 {
    private:
        typedef typename Remove_CVR<T>::Type U;
    public:
        static const bool Value = Is_Int8_Type<U>::Value;
    };

    /**
     * type: unsigned char, byte
     */
    template<class T>
    struct Is_UInt8_Type {
        static const bool Value = false;
    };

    template<>
    struct Is_UInt8_Type<uint8_t> {
        static const bool Value = true;
    };

    template<>
    struct Is_UInt8_Type<const uint8_t> {
        static const bool Value = true;
    };

    template<class T>
    struct Is_UInt8 {
    private:
        typedef typename Remove_CVR<T>::Type U;
    public:
        static const bool Value = Is_UInt8_Type<U>::Value;
    };

    /**
     * type: signed short int
     *
     */
    template<class T>
    struct Is_Int16_Type {
        static const bool Value = false;
    };

    template<>
    struct Is_Int16_Type<int16_t> {
        static const bool Value = true;
    };

    template<>
    struct Is_Int16_Type<const int16_t> {
        static const bool Value = true;
    };

    template<class T>
    struct Is_Int16 {
    private:
        typedef typename Remove_CVR<T>::Type U;
    public:
        static const bool Value = Is_Int16_Type<U>::Value;
    };

    /**
     * type: unsigned short int
     *
     */
    template<class T>
    struct Is_UInt16_Type {
        static const bool Value = false;
    };

    template<>
    struct Is_UInt16_Type<uint16_t> {
        static const bool Value = true;
    };

    template<>
    struct Is_UInt16_Type<const uint16_t> {
        static const bool Value = true;
    };

    template<class T>
    struct Is_UInt16 {
    private:
        typedef typename Remove_CVR<T>::Type U;
    public:
        static const bool Value = Is_UInt16_Type<U>::Value;
    };

    /**
     * type: signed int
     *
     */
    template<class T>
    struct Is_Int32_Type {
        static const bool Value = false;
    };

    template<>
    struct Is_Int32_Type<int32_t> {
        static const bool Value = true;
    };

    template<>
    struct Is_Int32_Type<const int32_t> {
        static const bool Value = true;
    };

    template<class T>
    struct Is_Int32 {
    private:
        typedef typename Remove_CVR<T>::Type U;
    public:
        static const bool Value = Is_Int32_Type<U>::Value;
    };

    /**
     * type: unsigned int
     *
     */
    template<class T>
    struct Is_UInt32_Type {
        static const bool Value = false;
    };

    template<>
    struct Is_UInt32_Type<uint32_t> {
        static const bool Value = true;
    };

    template<>
    struct Is_UInt32_Type<const uint32_t> {
        static const bool Value = true;
    };

    template<class T>
    struct Is_UInt32 {
    private:
        typedef typename Remove_CVR<T>::Type U;
    public:
        static const bool Value = Is_UInt32_Type<U>::Value;
    };

    /**
     * type: signed long int or signed long long int
     *
     */
    template<class T>
    struct Is_Int64_Type {
        static const bool Value = false;
    };

    template<>
    struct Is_Int64_Type<int64_t> {
        static const bool Value = true;
    };

    template<>
    struct Is_Int64_Type<const int64_t> {
        static const bool Value = true;
    };

    template<class T>
    struct Is_Int64 {
    private:
        typedef typename Remove_CVR<T>::Type U;
    public:
        static const bool Value = Is_Int64_Type<U>::Value;
    };

    /**
     * type: unsigned long int or unsigned long long int
     *
     */
    template<class T>
    struct Is_UInt64_Type {
        static const bool Value = false;
    };

    template<>
    struct Is_UInt64_Type<uint64_t> {
        static const bool Value = true;
    };

    template<>
    struct Is_UInt64_Type<const uint64_t> {
        static const bool Value = true;
    };

    template<class T>
    struct Is_UInt64 {
    private:
        typedef typename Remove_CVR<T>::Type U;
    public:
        static const bool Value = Is_UInt64_Type<U>::Value;
    };

    /**
     * type check for float
     */
    template<class T>
    struct Is_Float_Type {
        static const bool Value = false;
    };

    template<>
    struct Is_Float_Type<float> {
        static const bool Value = true;
    };

    template<>
    struct Is_Float_Type<const float> {
        static const bool Value = true;
    };

    template<class T>
    struct Is_Float {
    private:
        typedef typename Remove_CVR<T>::Type U;
    public:
        static const bool Value = Is_Float_Type<U>::Value;
    };

    /**
     * type check for double
     */
    template<class T>
    struct Is_Double_Type {
        static const bool Value = false;
    };

    template<>
    struct Is_Double_Type<double> {
        static const bool Value = true;
    };

    template<>
    struct Is_Double_Type<const double> {
        static const bool Value = true;
    };

    template<class T>
    struct Is_Double {
    private:
        typedef typename Remove_CVR<T>::Type U;
    public:
        static const bool Value = Is_Double_Type<U>::Value;
    };

    /**
     * long double type
     */
    template<class T>
    struct Is_LongDouble_Type {
        static const bool Value = false;
    };

    template<>
    struct Is_LongDouble_Type<long double> {
        static const bool Value = true;
    };

    template<>
    struct Is_LongDouble_Type<const long double> {
        static const bool Value = true;
    };

    template<class T>
    struct Is_LongDouble {
    private:
        typedef typename Remove_CVR<T>::Type U;
    public:
        static const bool Value = Is_LongDouble_Type<U>::Value;
    };

    /**
     * type check for boolean
     */
    template<class T>
    struct Is_Bool_Type {
        static const bool Value = false;
    };

    template<>
    struct Is_Bool_Type<bool> {
        static const bool Value = true;
    };

    template<>
    struct Is_Bool_Type<const bool> {
        static const bool Value = true;
    };

    template<class T>
    struct Is_Bool {
    private:
        typedef typename Remove_CVR<T>::Type U;
    public:
        static const bool Value = Is_Bool_Type<U>::Value;
    };

    /**
     * type check for string
     */
    template<class T>
    struct Is_String_Type {
        static const bool Value = false;
    };

    template<>
    struct Is_String_Type<std::string> {
        static const bool Value = true;
    };

    template<>
    struct Is_String_Type<const std::string> {
        static const bool Value = true;
    };

    template<class T>
    struct Is_String {
    private:
        typedef typename Remove_CVR<T>::Type U;
    public:
        static const bool Value = Is_String_Type<U>::Value;
    };

    /**
     * Type check for Is_Decimal
     */
    template<class T>
    struct Is_Decimal {
    private:
        typedef typename Remove_CVR<T>::Type U;

    public:
        static constexpr bool Value = (
                (Is_Float<U>::Value) ||
                (Is_Double<U>::Value) ||
                (Is_LongDouble<U>::Value)
        );
    };

    /**
     * type check for integers
     */
    template<class T>
    struct Is_Integer {
    private:
        typedef typename Remove_CVR<T>::Type U;
    public:
        static constexpr bool Value = (
                (Is_Int8<U>::Value) || (Is_UInt8<U>::Value) ||
                (Is_Int16<U>::Value) || (Is_UInt16<U>::Value) ||
                (Is_Int32<U>::Value) || (Is_UInt32<U>::Value) ||
                (Is_Int64<U>::Value) || (Is_UInt64<U>::Value)
        );
    };

    /**
     * Determines weather T is primitive type (i.e. not a class except string)
     * considering std::string is primitive
     */
    template<class T>
    struct Is_Premitive {
    private:
        typedef typename Remove_CVR<T>::Type U;

    public:
        static constexpr bool Value = (
                (Is_Bool<U>::Value) ||
                (Is_Char<U>::Value) ||
                (Is_Integer<U>::Value) ||
                (Is_Decimal<U>::Value) ||
                (Is_String<U>::Value)
        );
    };

    /**
     * check weateher T is a std::vector
     */
    template<class T>
    struct Is_Vector {
        static const bool Value = false;
    };

    template<class T, class Alloc>
        struct Is_Vector<std::vector<T, Alloc> > {
        static const bool Value = true;
    };

    template<class T, class Alloc>
        struct Is_Vector<std::vector<T, Alloc> &&> {
        static const bool Value = true;
    };

    template<class T, class Alloc>
        struct Is_Vector<std::vector<T, Alloc> &> {
        static const bool Value = true;
    };

    /**
    * Checks if T is a custom defined type
    */
    //    template<class T>
    //    struct Is_Class {
    //    private:
    //        typedef typename Remove_CVR<T>::Type U;
    //
    //    public:
    //        static constexpr bool Value = (
    //                !(Is_Premitive<U>::Value) &&
    //                !(Is_Vector<U>::Value) &&
    //                !(std::is_pointer<U>::value) &&
    //                !(std::is_enum<U>::value) &&
    //                (std::is_object<U>::value)
    //                );
    //    };

    template<class T>
    struct Is_Class {
    private:
        typedef typename Remove_CVR<T>::Type U;

    public:
        static constexpr bool Value = (
                (!Is_Vector<U>::Value) &&
                (!Is_Premitive<U>::Value) &&
                //(!std::is_enum<U>::value) &&
                (std::is_class<U>::value)
        );
    };


    /**
     * make compilable with long long int in 64 bit word size system
     * and long int is 32 bit word size system.
     */
#if __WORDSIZE == 32

    template<>
    struct Is_Int32_Type<long int> {
        static const bool Value = true;
    };

    template<>
    struct Is_Int32_Type<unsigned long int> {
        static const bool Value = true;
    };

    struct Is_UInt32_Type<unsigned long int> {
        static const bool Value = true;
    };

    template<>
    struct Is_UInt32_Type<const unsigned long int> {
        static const bool Value = true;
    };

#elif __WORDSIZE == 64

    template<>
    struct Is_Int64_Type<long long> {
        static const bool Value = true;
    };

    template<>
    struct Is_Int64_Type<const long long> {
        static const bool Value = true;
    };

    template<>
    struct Is_UInt64_Type<unsigned long long> {
        static const bool Value = true;
    };

    template<>
    struct Is_UInt64_Type<const unsigned long long> {
        static const bool Value = true;
    };
#endif

}


#endif //OPEN_JSON_TYPETRAITS_H
