#ifndef OPEN_JSON_TYPETRAITSFLOAT_H
#define OPEN_JSON_TYPETRAITSFLOAT_H

#include "type_traits/ConstraintsRemover.h"


namespace open_json {
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

    /*
    template<>
    struct Is_Float_Type<float &> {
        static const bool Value = true;
    };

    template<>
    struct Is_Float_Type<float *> {
        static const bool Value = true;
    };

    template<>
    struct Is_Float_Type<const float> {
        static const bool Value = true;
    };

    template<>
    struct Is_Float_Type<const float &> {
        static const bool Value = true;
    };

    template<>
    struct Is_Float_Type<const float *> {
        static const bool Value = true;
    };

    template<>
    struct Is_Float_Type<float *const> {
        static const bool Value = true;
    };

    template<>
    struct Is_Float_Type<const float *const> {
        static const bool Value = true;
    };

    template<>
    struct Is_Float_Type<const float *const *> {
        static const bool Value = true;
    };
    */

    template<class T>
    struct Is_Float {
    private:
        typedef typename Remove_CVRP<T>::Type U;
    public:
        static const bool Value = Is_Float_Type<U>::Value;
    };
}

#endif //OPEN_JSON_TYPETRAITSFLOAT_H
