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
    template<typename T>
    struct remove_all_cvr {
        using type = std::remove_cv_t<std::remove_reference_t<T>>;
    };

    template<typename T>
    struct remove_all_cvr<T *> {
        using type = typename remove_all_cvr<std::remove_cv_t<std::remove_reference_t<T>>>::type *;
    };

    template<typename T, std::size_t N>
    struct remove_all_cvr<T[N]> {
        using type = typename remove_all_cvr<std::remove_cv_t<std::remove_reference_t<T>>>::type[N];
    };

    template<typename T>
    struct remove_all_cvr<T[]> {
        using type = typename remove_all_cvr<std::remove_cv_t<std::remove_reference_t<T>>>::type[];
    };

    template<typename T>
    using remove_all_cvr_t = typename remove_all_cvr<T>::type;


    /********************************************************************************
     *  class to remove const, volatile and reference at all levels, and removes top level pointer qualifiers
     ********************************************************************************/
    template<typename T>
    struct remove_all_cvr_single_p {
        using type = std::remove_pointer_t<remove_all_cvr_t<T>>;
    };

    template<typename T>
    using remove_all_cvr_single_p_t = typename remove_all_cvr_single_p<T>::type;


    /********************************************************************************
     *  class to remove volatile, references, and pointers at all levels
     ********************************************************************************/
    template<typename T>
    struct remove_all_vrp {
        using type = std::remove_volatile_t<std::remove_reference_t<T>>;
    };

    template<typename T>
    struct remove_all_vrp<T *> {
        using type = typename remove_all_vrp<std::remove_volatile_t<std::remove_reference_t<T>>>::type;
    };

    template<typename T>
    struct remove_all_vrp<volatile T *> {
        using type = typename remove_all_vrp<std::remove_volatile_t<std::remove_reference_t<T>>>::type;
    };

    template<typename T>
    using remove_all_vrp_t = typename remove_all_vrp<T>::type;


    /********************************************************************************
     *  class to remove const, volatile, references, and pointers at all levels
     ********************************************************************************/
    template<typename T>
    struct remove_all_cvrp {
        using type = remove_all_cvr_t<T>;
    };

    template<typename T>
    struct remove_all_cvrp<T *> {
        using type = typename remove_all_cvrp<remove_all_cvr_t<T>>::type;
    };

    template<typename T>
    using remove_all_cvrp_t = typename remove_all_cvrp<T>::type;


    /**
     * type check for const
     */
    template<class T>
    struct is_const {
    private:
        typedef remove_all_vrp_t<T> U;
    public:
        static constexpr bool value = std::is_const<U>::value;
    };

    template<class T>
    inline constexpr bool is_const_v = is_const<T>::value;

    /**
     * type check for pointer
     */
    template<class T>
    struct is_pointer {
    private:
        typedef remove_all_cvr_t<T> U;
    public:
        static constexpr bool value = std::is_pointer<U>::value;
    };

    template<class T>
    inline constexpr bool is_pointer_v = is_pointer<T>::value;

    ///////////////////////////////////////////////////////////////
    /**
     * type check for enum
     */
    template<class T>
    struct is_enum {
    private:
        typedef remove_all_cvrp_t<T> U;
    public:
        static constexpr bool value = std::is_enum<U>::value;
    };

    template<class T>
    inline constexpr bool is_enum_v = is_enum<T>::value;

    /**
     * type check for union
     */
    template<class T>
    struct is_union {
    private:
        typedef remove_all_cvrp_t<T> U;
    public:
        static constexpr bool value = std::is_union<U>::value;
    };

    template<class T>
    inline constexpr bool is_union_v = is_union<T>::value;

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
        typedef remove_all_cvrp_t<T> U;
    public:
        static constexpr bool value = is_bool_type<U>::value;
    };

    template<class T>
    inline constexpr bool is_bool_v = is_bool<T>::value;

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
        typedef remove_all_cvrp_t<T> U;
    public:
        static constexpr bool value = is_char_type<U>::value;
    };

    template<class T>
    inline constexpr bool is_char_v = is_char<T>::value;

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
        typedef remove_all_cvrp_t<T> U;
    public:
        static constexpr bool value = is_uchar_type<U>::value;
    };

    template<class T>
    inline constexpr bool is_uchar_v = is_uchar<T>::value;

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
        typedef remove_all_cvrp_t<T> U;
    public:
        static constexpr bool value = is_int8_type<U>::value;
    };

    template<class T>
    inline constexpr bool is_int8_v = is_int8<T>::value;

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
        typedef remove_all_cvrp_t<T> U;
    public:
        static constexpr bool value = is_uint8_type<U>::value;
    };

    template<class T>
    inline constexpr bool is_uint8_v = is_uint8<T>::value;

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
        typedef remove_all_cvrp_t<T> U;
    public:
        static constexpr bool value = is_int16_type<U>::value;
    };

    template<class T>
    inline constexpr bool is_int16_v = is_int16<T>::value;

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
        typedef remove_all_cvrp_t<T> U;
    public:
        static constexpr bool value = is_uint16_type<U>::value;
    };

    template<class T>
    inline constexpr bool is_uint16_v = is_uint16<T>::value;

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
        typedef remove_all_cvrp_t<T> U;
    public:
        static constexpr bool value = is_int32_type<U>::value;
    };

    template<class T>
    inline constexpr bool is_int32_v = is_int32<T>::value;

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
        typedef remove_all_cvrp_t<T> U;
    public:
        static constexpr bool value = is_uint32_type<U>::value;
    };

    template<class T>
    inline constexpr bool is_uint32_v = is_uint32<T>::value;

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
        typedef remove_all_cvrp_t<T> U;
    public:
        static constexpr bool value = is_int64_type<U>::value;
    };

    template<class T>
    inline constexpr bool is_int64_v = is_int64<T>::value;

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
        typedef remove_all_cvrp_t<T> U;
    public:
        static constexpr bool value = is_uint64_type<U>::value;
    };

    template<class T>
    inline constexpr bool is_uint64_v = is_uint64<T>::value;

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
        typedef remove_all_cvrp_t<T> U;
    public:
        static constexpr bool value = is_float_type<U>::value;
    };

    template<class T>
    inline constexpr bool is_float_v = is_float<T>::value;

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
        typedef remove_all_cvrp_t<T> U;
    public:
        static constexpr bool value = is_double_type<U>::value;
    };

    template<class T>
    inline constexpr bool is_double_v = is_double<T>::value;

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
        typedef remove_all_cvrp_t<T> U;
    public:
        static constexpr bool value = is_long_double_type<U>::value;
    };

    template<class T>
    inline constexpr bool is_long_double_v = is_long_double<T>::value;

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
        typedef remove_all_cvrp_t<T> U;
    public:
        static constexpr bool value = is_string_type<U>::value;
    };

    template<class T>
    inline constexpr bool is_string_v = is_string<T>::value;

    /**
     * type check for array
     */
    template<class T>
    struct is_array {
    private:
        typedef remove_all_cvr_t<T> U;
    public:
        static constexpr bool value = std::is_array<U>::value;
    };

    template<class T>
    inline constexpr bool is_array_v = is_array<T>::value;


    /**
     * type check for is_decimal
     */
    template<class T>
    struct is_decimal {
    private:
        typedef remove_all_cvrp_t<T> U;

    public:
        static constexpr bool value = (
                (is_float<U>::value) ||
                (is_double<U>::value) ||
                (is_long_double<U>::value)
        );
    };

    template<class T>
    inline constexpr bool is_decimal_v = is_decimal<T>::value;

    /**
     * type check for integers
     */
    template<class T>
    struct is_integer {
    private:
        typedef remove_all_cvrp_t<T> U;
    public:
        static constexpr bool value = (
                (is_int8<U>::value) || (is_uint8<U>::value) ||
                (is_int16<U>::value) || (is_uint16<U>::value) ||
                (is_int32<U>::value) || (is_uint32<U>::value) ||
                (is_int64<U>::value) || (is_uint64<U>::value)
        );
    };

    template<class T>
    inline constexpr bool is_integer_v = is_integer<T>::value;

    /**
     * type check for integers
     */
    template<class T>
    struct is_number {
    private:
        typedef remove_all_cvrp_t<T> U;
    public:
        static constexpr bool value = (
                (is_integer<U>::value) || (is_decimal<U>::value)
        );
    };

    template<class T>
    inline constexpr bool is_number_v = is_number<T>::value;

    /**
     * Determines whether T is primitive type (i.e. not a class except string)
     */
    template<class T>
    struct is_primitive {
    private:
        typedef remove_all_cvrp_t<T> U;

    public:
        static constexpr bool value = (
                (is_bool<U>::value) ||
                (is_char<U>::value) ||
                (is_number<U>::value)
        );
    };

    template<class T>
    inline constexpr bool is_primitive_v = is_primitive<T>::value;

    /**
     * check whether T is a std::vector
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

    template<class T, class Alloc>
    struct is_vector<const volatile std::vector<T, Alloc> &> {
        static const bool value = true;
    };

    template<class T>
    inline constexpr bool is_vector_v = is_vector<std::remove_cv_t<std::remove_reference_t<T>>>::value;

    /**
     * check whether T is a std::map
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

    template<class T, class U, class Alloc>
    struct is_map<const volatile std::map<T, U, Alloc> &> {
        static const bool value = true;
    };

    template<class T>
    inline constexpr bool is_map_v = is_map<std::remove_cv_t<std::remove_reference_t<T>>>::value;

    /**
    * check whether T is a std::unique_ptr
    */
    template <typename T>
    struct is_unique_ptr : std::false_type {};

    template <typename T, class D>
    struct is_unique_ptr<std::unique_ptr<T, D>> : std::true_type {};

    template <typename T, class D>
    struct is_unique_ptr<std::unique_ptr<T, D> const> : std::true_type {};

    template <typename T, class D>
    struct is_unique_ptr<std::unique_ptr<T, D> volatile> : std::true_type {};

    template <typename T, class D>
    struct is_unique_ptr<std::unique_ptr<T, D> const volatile> : std::true_type {};

    template <typename T>
    inline constexpr bool is_unique_ptr_v = is_unique_ptr<std::remove_cv_t<std::remove_reference_t<T>>>::value;

    // Helper template to extract the value type of a unique_ptr
    template<typename T>
    struct unique_ptr_value_type {
        using type = void; // Default to void for non-unique_ptr types
    };

    template<typename T, typename D>
    struct unique_ptr_value_type<std::unique_ptr<T, D>> {
        using type = T; // Extract the value type for unique_ptr
    };

    template<typename T>
    using unique_ptr_value_type_t = typename unique_ptr_value_type<T>::type;

    /**
    * check whether T is a std::shared_ptr
    */
    template <typename T>
    struct is_shared_ptr : std::false_type {};

    template <typename T>
    struct is_shared_ptr<std::shared_ptr<T>> : std::true_type {};

    template <typename T>
    struct is_shared_ptr<std::shared_ptr<T> const> : std::true_type {};

    template <typename T>
    struct is_shared_ptr<std::shared_ptr<T> volatile> : std::true_type {};

    template <typename T>
    struct is_shared_ptr<std::shared_ptr<T> const volatile> : std::true_type {};

    template <typename T>
    inline constexpr bool is_shared_ptr_v = is_shared_ptr<std::remove_cv_t<std::remove_reference_t<T>>>::value;

    // Helper template to extract the value type of a unique_ptr
    template<typename T>
    struct shared_ptr_value_type {
        using type = void; // Default to void for non-unique_ptr types
    };

    template<typename T>
    struct shared_ptr_value_type<std::shared_ptr<T>> {
        using type = T; // Extract the value type for unique_ptr
    };

    template<typename T>
    using shared_ptr_value_type_t = typename shared_ptr_value_type<T>::type;

    /**
     * check whether T is a custom class
     */
    template<class T>
    struct is_class {
    private:
        typedef remove_all_cvrp_t<T> U;

    public:
        static constexpr bool value = (
                (!is_primitive<U>::value) &&
                (!is_string<U>::value) &&
                (!is_enum<U>::value) &&
                (!is_union<U>::value) &&
                (!is_vector<U>::value) &&
                (!is_map<U>::value) &&
                (!is_unique_ptr<T>::value) &&
                (!is_shared_ptr<T>::value) &&
                (std::is_class<U>::value)
        );
    };

    template <typename T>
    inline constexpr bool is_class_v = is_class<T>::value;
}


#endif //OPEN_JSON_TYPETRAITS_H
