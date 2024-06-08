
#ifndef OPEN_JSON_TYPETRAITSINT16_H
#define OPEN_JSON_TYPETRAITSINT16_H

#include <stdint.h>
#include "type_traits/ConstraintsRemover.h"


namespace open_json {
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

    /*
    template<>
    struct Is_Int16_Type<int16_t &> {
        static const bool Value = true;
    };

    template<>
    struct Is_Int16_Type<int16_t *> {
        static const bool Value = true;
    };

    template<>
    struct Is_Int16_Type<const int16_t> {
        static const bool Value = true;
    };

    template<>
    struct Is_Int16_Type<const int16_t &> {
        static const bool Value = true;
    };

    template<>
    struct Is_Int16_Type<const int16_t *> {
        static const bool Value = true;
    };

    template<>
    struct Is_Int16_Type<int16_t *const> {
        static const bool Value = true;
    };

    template<>
    struct Is_Int16_Type<const int16_t *const> {
        static const bool Value = true;
    };

    template<>
    struct Is_Int16_Type<const int16_t *const *> {
        static const bool Value = true;
    };
    */

    template<class T>
    struct Is_Int16 {
    private:
        typedef typename Remove_CVRP<T>::Type U;
    public:
        static const bool Value = Is_Int16_Type<U>::Value;
    };
}

#endif //OPEN_JSON_TYPETRAITSINT16_H
