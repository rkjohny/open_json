#ifndef OPEN_JSON_TYPETRAITS_H
#define OPEN_JSON_TYPETRAITS_H


#include <type_traits>
#include <string>
#include <vector>
#include <cstdint>
#include <map>


namespace open_json {

    // base class to remove const, volatile and reference qualifiers at all levels
    template <typename T>
    struct Remove_CVR {
        using Type = std::remove_cv_t<std::remove_reference_t<T>>;
    };

    template <typename T>
    struct Remove_CVR<T*> {
        using Type = typename Remove_CVR<std::remove_cv_t<std::remove_reference_t<T>>>::Type*;
    };

    // Helper alias template
    template <typename T>
    using Remove_CVR_T = typename Remove_CVR<T>::Type;

    // base class to remove const, volatile and reference at all levels, and removes top level pointer qualifiers
    template <typename T>
    struct Remove_CVRP {
        using Type = std::remove_pointer_t<Remove_CVR_T<T>>;
    };
    
    // Helper alias template
    template <typename T>
    using Remove_CVRP_T = typename Remove_CVRP<T>::Type;


    // Base class to remove volatile, references, and pointers at all levels
    template <typename T>
    struct Remove_VRP {
        using Type = std::remove_volatile_t<std::remove_reference_t<T>>;
    };

    // Specialization to handle pointers
    template <typename T>
    struct Remove_VRP<T*> {
        using Type = typename Remove_VRP<std::remove_volatile_t<std::remove_reference_t<T>>>::Type;
    };

    // Specialization to handle pointers to volatile
    template <typename T>
    struct Remove_VRP<volatile T*> {
        using Type = typename Remove_VRP<T>::Type;
    };

    // Helper alias template
    template <typename T>
    using Remove_VRP_T = typename Remove_VRP<T>::Type;

    

    /**
     * Type check for const
     */
    template<class T>
    struct Is_Const {
    private:
        typedef typename Remove_VRP<T>::Type U;
    public:
        static constexpr bool Value = std::is_const<U>::value;
    };

    /**
     * Type check for pointer
     */
    template<class T>
    struct Is_Pointer {
    private:
        typedef typename Remove_CVR<T>::Type U;
    public:
        static constexpr bool Value = std::is_pointer<U>::value;
    };

    ///////////////////////////////////////////////////////////////
    /**
     * Type check for enum
     */
    template<class T>
    struct Is_Enum {
    private:
        typedef typename Remove_CVR<T>::Type U;
    public:
        static constexpr bool Value = std::is_enum<U>::value;
    };

    /**
     * Type check for union
     */
    template<class T>
    struct Is_Union {
    private:
        typedef typename Remove_CVR<T>::Type U;
    public:
        static constexpr bool Value = std::is_union<T>::value;
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

    template<class T>
    struct Is_Bool {
    private:
        typedef typename Remove_CVR<T>::Type U;
    public:
        static constexpr bool Value = Is_Bool_Type<U>::Value;
    };

    /**
     * type char, it may vary among platforms
     */
    template<class T>
    struct Is_Char_Type {
        static const bool Value = false;
    };

    template<>
    struct Is_Char_Type<char> {
        static const bool Value = true;
    };

    template<class T>
    struct Is_Char {
    private:
        typedef typename Remove_CVR<T>::Type U;
    public:
        static constexpr bool Value = Is_Char_Type<U>::Value;
    };

    /**
     * type unsigned char, it may vary among platforms
     */
    template<class T>
    struct Is_UChar_Type {
        static const bool Value = false;
    };

    template<>
    struct Is_UChar_Type<unsigned char> {
        static const bool Value = true;
    };

    template<class T>
    struct Is_UChar {
    private:
        typedef typename Remove_CVR<T>::Type U;
    public:
        static constexpr bool Value = Is_UChar_Type<U>::Value;
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

    template<class T>
    struct Is_Int8 {
    private:
        typedef typename Remove_CVR<T>::Type U;
    public:
        static constexpr bool Value = Is_Int8_Type<U>::Value;
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

    template<class T>
    struct Is_UInt8 {
    private:
        typedef typename Remove_CVR<T>::Type U;
    public:
        static constexpr bool Value = Is_UInt8_Type<U>::Value;
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

    template<class T>
    struct Is_Int16 {
    private:
        typedef typename Remove_CVR<T>::Type U;
    public:
        static constexpr bool Value = Is_Int16_Type<U>::Value;
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

    template<class T>
    struct Is_UInt16 {
    private:
        typedef typename Remove_CVR<T>::Type U;
    public:
        static constexpr bool Value = Is_UInt16_Type<U>::Value;
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

#if WORD_SIZE == 32
    template<>
    struct Is_Int32_Type<long int > {
        static const bool Value = true;
    };
#endif

    template<class T>
    struct Is_Int32 {
    private:
        typedef typename Remove_CVR<T>::Type U;
    public:
        static constexpr bool Value = Is_Int32_Type<U>::Value;
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

#if WORD_SIZE == 32
    template<>
    struct Is_UInt32_Type<unsigned long int> {
        static const bool Value = true;
    };
#endif

    template<class T>
    struct Is_UInt32 {
    private:
        typedef typename Remove_CVR<T>::Type U;
    public:
        static constexpr bool Value = Is_UInt32_Type<U>::Value;
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

#if WORD_SIZE == 64
    template<>
    struct Is_Int64_Type<long int> {
        static const bool Value = true;
    };
#endif

    template<class T>
    struct Is_Int64 {
    private:
        typedef typename Remove_CVR<T>::Type U;
    public:
        static constexpr bool Value = Is_Int64_Type<U>::Value;
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

#if WORD_SIZE == 64
    template<>
    struct Is_UInt64_Type<unsigned long int> {
        static const bool Value = true;
    };
#endif

    template<class T>
    struct Is_UInt64 {
    private:
        typedef typename Remove_CVR<T>::Type U;
    public:
        static constexpr bool Value = Is_UInt64_Type<U>::Value;
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

    template<class T>
    struct Is_Float {
    private:
        typedef typename Remove_CVR<T>::Type U;
    public:
        static constexpr bool Value = Is_Float_Type<U>::Value;
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

    template<class T>
    struct Is_Double {
    private:
        typedef typename Remove_CVR<T>::Type U;
    public:
        static constexpr bool Value = Is_Double_Type<U>::Value;
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

    template<class T>
    struct Is_LongDouble {
    private:
        typedef typename Remove_CVR<T>::Type U;
    public:
        static constexpr bool Value = Is_LongDouble_Type<U>::Value;
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

    template<class T>
    struct Is_String {
    private:
        typedef typename Remove_CVR<T>::Type U;
    public:
        static constexpr bool Value = Is_String_Type<U>::Value;
    };


    /**
     * Type check for array
     */
    template<class T>
    struct Is_Array {
    private:
        typedef typename Remove_CVR<T>::Type U;
    public:
        static constexpr bool Value = std::is_array<T>::value;
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
     * type check for integers
     */
    template<class T>
    struct Is_Number {
    private:
        typedef typename Remove_CVR<T>::Type U;
    public:
        static constexpr bool Value = (
                (Is_Integer<U>::Value) || (Is_Decimal<U>::Value)
        );
    };

    /**
     * Determines weather T is primitive type (i.e. not a class except string)
     */
    template<class T>
    struct Is_Primitive {
    private:
        typedef typename Remove_CVR<T>::Type U;

    public:
        static constexpr bool Value = (
                (Is_Bool<U>::Value) ||
                (Is_Char<U>::Value) ||
                (Is_Number<U>::Value)
        );
    };


    /**
     * check weather T is a std::vector
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
    struct Is_Vector<const std::vector<T, Alloc> > {
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

    template<class T, class Alloc>
    struct Is_Vector<const std::vector<T, Alloc> &> {
        static const bool Value = true;
    };

    /**
     * check weather T is a std::map
     */
    template<class T>
    struct Is_Map {
        static const bool Value = false;
    };

    template<class T, class U, class Alloc>
    struct Is_Map<std::map<T, U, Alloc> > {
        static const bool Value = true;
    };

    template<class T, class U, class Alloc>
    struct Is_Map<const std::map<T, U, Alloc> > {
        static const bool Value = true;
    };

    template<class T, class U, class Alloc>
    struct Is_Map<std::map<T, U, Alloc> &&> {
        static const bool Value = true;
    };

    template<class T, class U, class Alloc>
    struct Is_Map<std::map<T, U, Alloc> &> {
        static const bool Value = true;
    };

    template<class T, class U, class Alloc>
    struct Is_Map<const std::map<T, U, Alloc> &> {
        static const bool Value = true;
    };

    /**
     * check weather T is a custom class
     */
    template<class T>
    struct Is_Class {
    private:
        typedef typename Remove_CVR<T>::Type U;

    public:
        static constexpr bool Value = (
                (!Is_Primitive<U>::Value) &&
                (!Is_String<U>::Value) &&
                (!Is_Enum<U>::Value) &&
                (!Is_Union<U>::Value) &&
                (!Is_Vector<U>::Value) &&
                (!Is_Map<U>::Value) &&
                (std::is_class<U>::value)
        );
    };
}


#endif //OPEN_JSON_TYPETRAITS_H
