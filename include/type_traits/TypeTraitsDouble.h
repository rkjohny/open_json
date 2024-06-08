#ifndef OPEN_JSON_TYPETRAITSDOUBLE_H
#define OPEN_JSON_TYPETRAITSDOUBLE_H

#include "type_traits/ConstraintsRemover.h"


namespace open_json {
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

    /*
    template<>
    struct Is_Double_Type<double &> {
        static const bool Value = true;
    };

    template<>
    struct Is_Double_Type<double *> {
        static const bool Value = true;
    };

    template<>
    struct Is_Double_Type<const double> {
        static const bool Value = true;
    };

    template<>
    struct Is_Double_Type<const double &> {
        static const bool Value = true;
    };

    template<>
    struct Is_Double_Type<const double *> {
        static const bool Value = true;
    };

    template<>
    struct Is_Double_Type<double *const> {
        static const bool Value = true;
    };

    template<>
    struct Is_Double_Type<const double *const> {
        static const bool Value = true;
    };

    template<>
    struct Is_Double_Type<const double *const *> {
        static const bool Value = true;
    };
    */

    template<class T>
    struct Is_Double {
    private:
        typedef typename Remove_CVRP<T>::Type U;
    public:
        static const bool Value = Is_Double_Type<U>::Value;
    };
}


#endif //OPEN_JSON_TYPETRAITSDOUBLE_H
