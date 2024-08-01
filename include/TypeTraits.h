#ifndef OPEN_JSON_TYPETRAITS_H
#define OPEN_JSON_TYPETRAITS_H


#include <type_traits>
#include <string>
#include <vector>
#include <cstdint>
#include <map>


namespace open_json {

    /********************************************************************************
     *  class to remove const, volatile and reference qualifiers at all levels
     ********************************************************************************/
    template <typename T>
    struct remove_all_cvr {
        using type = std::remove_cv_t<std::remove_reference_t<T>>;
    };

    template <typename T>
    struct remove_all_cvr<T*> {
        using type = typename remove_all_cvr<std::remove_cv_t<std::remove_reference_t<T>>>::type*;
    };

    template <typename T, std::size_t N>
    struct remove_all_cvr<T[N]> {
        using type = typename remove_all_cvr<std::remove_cv_t<std::remove_reference_t<T>>>::type[N];
    };

    template <typename T>
    struct remove_all_cvr<T[]> {
        using type = typename remove_all_cvr<std::remove_cv_t<std::remove_reference_t<T>>>::type[];
    };

    template <typename T>
    using remove_all_cvr_t = typename remove_all_cvr<T>::type;


    /********************************************************************************
     *  class to remove const, volatile and reference at all levels, and removes top level pointer qualifiers
     ********************************************************************************/
    template <typename T>
    struct remove_all_cvr_single_p {
        using type = std::remove_pointer_t<remove_all_cvr_t<T>>;
    };

    template <typename T>
    using remove_all_cvr_single_p_t = typename remove_all_cvr_single_p<T>::type;


    /********************************************************************************
     *  class to remove volatile, references, and pointers at all levels
     ********************************************************************************/
    template <typename T>
    struct remove_all_vrp {
        using type = std::remove_volatile_t<std::remove_reference_t<T>>;
    };

    // Specialization to handle pointers
    template <typename T>
    struct remove_all_vrp<T*> {
        using type = typename remove_all_vrp<std::remove_volatile_t<std::remove_reference_t<T>>>::type;
    };

    // Specialization to handle pointers to volatile
    template <typename T>
    struct remove_all_vrp<volatile T*> {
        using type = typename remove_all_vrp<std::remove_volatile_t<std::remove_reference_t<T>>>::type;
    };

    template <typename T>
    using remove_all_vrp_t = typename remove_all_vrp<T>::type;


    /********************************************************************************
     *  class to remove const, volatile, references, and pointers at all levels
     ********************************************************************************/
    template <typename T>
    struct remove_all_cvrp {
        using type = remove_all_cvr_t<T>;
    };

    template <typename T>
    struct remove_all_cvrp<T*> {
        using type = typename remove_all_cvrp<remove_all_cvr_t<T>>::type;
    };

    template <typename T>
    using remove_all_cvrp_t = typename remove_all_cvrp<T>::type;



    /**
     * type check for const
     */
    template<class T>
    struct is_const {
    private:
        typedef typename remove_all_vrp<T>::type U;
    public:
        static constexpr bool value = std::is_const<U>::value;
    };

    /**
     * type check for pointer
     */
    template<class T>
    struct is_pointer {
    private:
        typedef typename remove_all_cvr<T>::type U;
    public:
        static constexpr bool value = std::is_pointer<U>::value;
    };

    ///////////////////////////////////////////////////////////////
    /**
     * type check for enum
     */
    template<class T>
    struct is_enum {
    private:
        typedef typename remove_all_cvrp<T>::type U;
    public:
        static constexpr bool value = std::is_enum<U>::value;
    };

    /**
     * type check for union
     */
    template<class T>
    struct is_union {
    private:
        typedef typename remove_all_cvrp<T>::type U;
    public:
        static constexpr bool value = std::is_union<T>::value;
    };

    /**
     * type check for boolean
     */
    template<class T>
    struct is_bool_type {
        static const bool value = false;
    };

    template<>
    struct is_bool_type<bool> {
        static const bool value = true;
    };

    template<class T>
    struct is_bool {
    private:
        typedef typename remove_all_cvrp<T>::type U;
    public:
        static constexpr bool value = is_bool_type<U>::value;
    };

    /**
     * type char, it may vary among platforms
     */
    template<class T>
    struct is_char_type {
        static const bool value = false;
    };

    template<>
    struct is_char_type<char> {
        static const bool value = true;
    };

    template<class T>
    struct is_char {
    private:
        typedef typename remove_all_cvrp<T>::type U;
    public:
        static constexpr bool value = is_char_type<U>::value;
    };

    /**
     * type unsigned char, it may vary among platforms
     */
    template<class T>
    struct is_uchar_type {
        static const bool value = false;
    };

    template<>
    struct is_uchar_type<unsigned char> {
        static const bool value = true;
    };

    template<class T>
    struct is_uchar {
    private:
        typedef typename remove_all_cvrp<T>::type U;
    public:
        static constexpr bool value = is_uchar_type<U>::value;
    };

    /**
     * type: signed char, byte
     */
    template<class T>
    struct is_int8_type {
        static const bool value = false;
    };

    template<>
    struct is_int8_type<int8_t> {
        static const bool value = true;
    };

    template<class T>
    struct is_int8 {
    private:
        typedef typename remove_all_cvrp<T>::type U;
    public:
        static constexpr bool value = is_int8_type<U>::value;
    };

    /**
     * type: unsigned char, byte
     */
    template<class T>
    struct is_uint8_type {
        static const bool value = false;
    };

    template<>
    struct is_uint8_type<uint8_t> {
        static const bool value = true;
    };

    template<class T>
    struct is_uint8 {
    private:
        typedef typename remove_all_cvrp<T>::type U;
    public:
        static constexpr bool value = is_uint8_type<U>::value;
    };

    /**
     * type: signed short int
     *
     */
    template<class T>
    struct is_int16_type {
        static const bool value = false;
    };

    template<>
    struct is_int16_type<int16_t> {
        static const bool value = true;
    };

    template<class T>
    struct is_int16 {
    private:
        typedef typename remove_all_cvrp<T>::type U;
    public:
        static constexpr bool value = is_int16_type<U>::value;
    };

    /**
     * type: unsigned short int
     *
     */
    template<class T>
    struct is_uint16_type {
        static const bool value = false;
    };

    template<>
    struct is_uint16_type<uint16_t> {
        static const bool value = true;
    };

    template<class T>
    struct is_uint16 {
    private:
        typedef typename remove_all_cvrp<T>::type U;
    public:
        static constexpr bool value = is_uint16_type<U>::value;
    };

    /**
     * type: signed int
     *
     */
    template<class T>
    struct is_int32_type {
        static const bool value = false;
    };

    template<>
    struct is_int32_type<int32_t> {
        static const bool value = true;
    };

#if WORD_SIZE == 32
    template<>
    struct is_int32_type<long int > {
        static const bool value = true;
    };
#endif

    template<class T>
    struct is_int32 {
    private:
        typedef typename remove_all_cvrp<T>::type U;
    public:
        static constexpr bool value = is_int32_type<U>::value;
    };

    /**
     * type: unsigned int
     *
     */
    template<class T>
    struct is_uint32_type {
        static const bool value = false;
    };


    template<>
    struct is_uint32_type<uint32_t> {
        static const bool value = true;
    };

#if WORD_SIZE == 32
    template<>
    struct is_uint32_type<unsigned long int> {
        static const bool value = true;
    };
#endif

    template<class T>
    struct is_uint32 {
    private:
        typedef typename remove_all_cvrp<T>::type U;
    public:
        static constexpr bool value = is_uint32_type<U>::value;
    };

    /**
     * type: signed long int or signed long long int
     *
     */
    template<class T>
    struct is_int64_type {
        static const bool value = false;
    };

    template<>
    struct is_int64_type<int64_t> {
        static const bool value = true;
    };

#if WORD_SIZE == 64
    template<>
    struct is_int64_type<long int> {
        static const bool value = true;
    };
#endif

    template<class T>
    struct is_int64 {
    private:
        typedef typename remove_all_cvrp<T>::type U;
    public:
        static constexpr bool value = is_int64_type<U>::value;
    };

    /**
     * type: unsigned long int or unsigned long long int
     *
     */
    template<class T>
    struct is_uint64_type {
        static const bool value = false;
    };

    template<>
    struct is_uint64_type<uint64_t> {
        static const bool value = true;
    };

#if WORD_SIZE == 64
    template<>
    struct is_uint64_type<unsigned long int> {
        static const bool value = true;
    };
#endif

    template<class T>
    struct is_uint64 {
    private:
        typedef typename remove_all_cvrp<T>::type U;
    public:
        static constexpr bool value = is_uint64_type<U>::value;
    };

    /**
     * type check for float
     */
    template<class T>
    struct is_float_type {
        static const bool value = false;
    };

    template<>
    struct is_float_type<float> {
        static const bool value = true;
    };

    template<class T>
    struct is_float {
    private:
        typedef typename remove_all_cvrp<T>::type U;
    public:
        static constexpr bool value = is_float_type<U>::value;
    };

    /**
     * type check for double
     */
    template<class T>
    struct is_double_type {
        static const bool value = false;
    };

    template<>
    struct is_double_type<double> {
        static const bool value = true;
    };

    template<class T>
    struct is_double {
    private:
        typedef typename remove_all_cvrp<T>::type U;
    public:
        static constexpr bool value = is_double_type<U>::value;
    };

    /**
     * long double type
     */
    template<class T>
    struct is_long_double_type {
        static const bool value = false;
    };

    template<>
    struct is_long_double_type<long double> {
        static const bool value = true;
    };

    template<class T>
    struct is_long_double {
    private:
        typedef typename remove_all_cvrp<T>::type U;
    public:
        static constexpr bool value = is_long_double_type<U>::value;
    };

    /**
     * type check for string
     */
    template<class T>
    struct is_string_type {
        static const bool value = false;
    };

    template<>
    struct is_string_type<std::string> {
        static const bool value = true;
    };

    template<class T>
    struct is_string {
    private:
        typedef typename remove_all_cvrp<T>::type U;
    public:
        static constexpr bool value = is_string_type<U>::value;
    };


    /**
     * type check for array
     */
    template<class T>
    struct is_array {
    private:
        typedef typename remove_all_cvr<T>::type U;
    public:
        static constexpr bool value = std::is_array<U>::value;
    };


    /**
     * type check for is_decimal
     */
    template<class T>
    struct is_decimal {
    private:
        typedef typename remove_all_cvrp<T>::type U;

    public:
        static constexpr bool value = (
                (is_float<U>::value) ||
                (is_double<U>::value) ||
                (is_long_double<U>::value)
        );
    };

    /**
     * type check for integers
     */
    template<class T>
    struct is_integer {
    private:
        typedef typename remove_all_cvrp<T>::type U;
    public:
        static constexpr bool value = (
                (is_int8<U>::value) || (is_uint8<U>::value) ||
                (is_int16<U>::value) || (is_uint16<U>::value) ||
                (is_int32<U>::value) || (is_uint32<U>::value) ||
                (is_int64<U>::value) || (is_uint64<U>::value)
        );
    };

    /**
     * type check for integers
     */
    template<class T>
    struct is_number {
    private:
        typedef typename remove_all_cvrp<T>::type U;
    public:
        static constexpr bool value = (
                (is_integer<U>::value) || (is_decimal<U>::value)
        );
    };

    /**
     * Determines weather T is primitive type (i.e. not a class except string)
     */
    template<class T>
    struct is_primitive {
    private:
        typedef typename remove_all_cvrp<T>::type U;

    public:
        static constexpr bool value = (
                (is_bool<U>::value) ||
                (is_char<U>::value) ||
                (is_number<U>::value)
        );
    };


    /**
     * check weather T is a std::vector
     */
    template<class T>
    struct is_vector {
        static const bool value = false;
    };

    template<class T, class Alloc>
    struct is_vector<std::vector<T, Alloc> > {
        static const bool value = true;
    };

    template<class T, class Alloc>
    struct is_vector<const std::vector<T, Alloc> > {
        static const bool value = true;
    };

    template<class T, class Alloc>
    struct is_vector<std::vector<T, Alloc> &&> {
        static const bool value = true;
    };

    template<class T, class Alloc>
    struct is_vector<std::vector<T, Alloc> &> {
        static const bool value = true;
    };

    template<class T, class Alloc>
    struct is_vector<const std::vector<T, Alloc> &> {
        static const bool value = true;
    };

    /**
     * check weather T is a std::map
     */
    template<class T>
    struct is_map {
        static const bool value = false;
    };

    template<class T, class U, class Alloc>
    struct is_map<std::map<T, U, Alloc> > {
        static const bool value = true;
    };

    template<class T, class U, class Alloc>
    struct is_map<const std::map<T, U, Alloc> > {
        static const bool value = true;
    };

    template<class T, class U, class Alloc>
    struct is_map<std::map<T, U, Alloc> &&> {
        static const bool value = true;
    };

    template<class T, class U, class Alloc>
    struct is_map<std::map<T, U, Alloc> &> {
        static const bool value = true;
    };

    template<class T, class U, class Alloc>
    struct is_map<const std::map<T, U, Alloc> &> {
        static const bool value = true;
    };

    /**
     * check weather T is a custom class
     */
    template<class T>
    struct is_class {
    private:
        typedef typename remove_all_cvrp<T>::type U;

    public:
        static constexpr bool value = (
                (!is_primitive<U>::value) &&
                (!is_string<U>::value) &&
                (!is_enum<U>::value) &&
                (!is_union<U>::value) &&
                (!is_vector<U>::value) &&
                (!is_map<U>::value) &&
                (std::is_class<U>::value)
        );
    };

    template<typename T>
    struct is_unique_ptr : std::false_type {

    };

    template<typename T, typename D>
    struct is_unique_ptr<std::unique_ptr<T, D>> : std::true_type {

    };

    // Helper template to extract the value type of a unique_ptr
    template<typename T>
    struct unique_ptr_value_type {
        using type = void; // Default to void for non-unique_ptr types
    };

    template<typename T, typename D>
    struct unique_ptr_value_type<std::unique_ptr<T, D>> {
        using type = T; // Extract the value type for unique_ptr
    };
}


#endif //OPEN_JSON_TYPETRAITS_H
