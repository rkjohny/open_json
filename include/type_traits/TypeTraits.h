#ifndef OPEN_JSON_TYPETRAITS_H
#define OPEN_JSON_TYPETRAITS_H


#include "TypeTraitsChar.h"
#include "TypeTraitsInt8.h"
#include "TypeTraitsUInt8.h"
#include "TypeTraitsInt16.h"
#include "TypeTraitsUInt16.h"
#include "TypeTraitsInt32.h"
#include "TypeTraitsUInt32.h"
#include "TypeTraitsInt64.h"
#include "TypeTraitsUInt64.h"
#include "TypeTraitsBool.h"
#include "TypeTraitsFloat.h"
#include "TypeTraitsDouble.h"
#include "TypeTraitsLongDouble.h"
#include "TypeTraitsString.h"
#include "TypeTraitsVector.h"


namespace open_json {
    /**
     * Type check for Is_Decimal
     */
    template<class T>
    struct Is_Decimal {
    private:
        typedef typename Remove_CVRP<T>::Type U;

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
        typedef typename Remove_CVRP<T>::Type U;
    public:
        static constexpr bool Value = (
                (Is_Int8<U>::Value) || (Is_UInt8<U>::Value) ||
                (Is_Int16<U>::Value) || (Is_UInt16<U>::Value) ||
                (Is_Int32<U>::Value) || (Is_UInt32<U>::Value) ||
                (Is_Int64<U>::Value) || (Is_UInt64<U>::Value)
        );
    };

    /**
     * Determines wheather T is primitive type (i.e. not a class except string)
     * considering std::string is primitive
     */
    template<class T>
    struct Is_Primitive {
    private:
        typedef typename Remove_CVRP<T>::Type U;

    public:
        static constexpr bool Value = (
                (Is_Bool<U>::Value) ||
                (Is_Char<U>::Value) ||
                (Is_Integer<U>::Value) ||
                (Is_Decimal<U>::Value) ||
                (Is_String<U>::Value)
        );
    };

    template<class T>
    struct Is_Class {
    private:
        typedef typename Remove_CVRP<T>::Type U;

    public:
        static constexpr bool Value = (
                (!Is_Vector<U>::Value) &&
                (!Is_Primitive<U>::Value) &&
                //(!std::is_enum<U>::value) &&
                //(!std::is_union<U>::value) &&
                (std::is_class<U>::value)
        );
    };
}


#endif //OPEN_JSON_TYPETRAITS_H
