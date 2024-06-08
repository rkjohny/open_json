#ifndef OPEN_JSON_TYPETRAITSLONGDOUBLE_H
#define OPEN_JSON_TYPETRAITSLONGDOUBLE_H

#include "type_traits/ConstraintsRemover.h"

namespace open_json {
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

    /*
    template<>
    struct Is_LongDouble_Type<long double &> {
        static const bool Value = true;
    };

    template<>
    struct Is_LongDouble_Type<long double *> {
        static const bool Value = true;
    };

    template<>
    struct Is_LongDouble_Type<const long double> {
        static const bool Value = true;
    };

    template<>
    struct Is_LongDouble_Type<const long double &> {
        static const bool Value = true;
    };

    template<>
    struct Is_LongDouble_Type<const long double *> {
        static const bool Value = true;
    };

    template<>
    struct Is_LongDouble_Type<long double *const> {
        static const bool Value = true;
    };

    template<>
    struct Is_LongDouble_Type<const long double *const> {
        static const bool Value = true;
    };

    template<>
    struct Is_LongDouble_Type<const long double *const *> {
        static const bool Value = true;
    };
    */

    template<class T>
    struct Is_LongDouble {
    private:
        typedef typename Remove_CVRP<T>::Type U;
    public:
        static const bool Value = Is_LongDouble_Type<U>::Value;
    };
}


#endif //OPEN_JSON_TYPETRAITSLONGDOUBLE_H
