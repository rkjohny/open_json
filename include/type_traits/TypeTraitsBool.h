#ifndef OPEN_JSON_TYPETRAITSBOOL_H
#define OPEN_JSON_TYPETRAITSBOOL_H

#include "type_traits/ConstraintsRemover.h"

namespace open_json {

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

    /*
    template<>
    struct Is_Bool_Type<bool &> {
        static const bool Value = true;
    };

    template<>
    struct Is_Bool_Type<bool *> {
        static const bool Value = true;
    };

    template<>
    struct Is_Bool_Type<const bool> {
        static const bool Value = true;
    };

    template<>
    struct Is_Bool_Type<const bool &> {
        static const bool Value = true;
    };

    template<>
    struct Is_Bool_Type<const bool *> {
        static const bool Value = true;
    };

    template<>
    struct Is_Bool_Type<bool *const> {
        static const bool Value = true;
    };

    template<>
    struct Is_Bool_Type<const bool *const> {
        static const bool Value = true;
    };

    template<>
    struct Is_Bool_Type<const bool *const *> {
        static const bool Value = true;
    };
    */

    template<class T>
    struct Is_Bool {
    private:
        typedef typename Remove_CVRP<T>::Type U;
    public:
        static const bool Value = Is_Bool_Type<U>::Value;
    };
}


#endif //OPEN_JSON_TYPETRAITSBOOL_H
