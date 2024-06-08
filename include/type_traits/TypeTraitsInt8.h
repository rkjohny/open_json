#ifndef OPEN_JSON_TYPETRAITSINT8_H
#define OPEN_JSON_TYPETRAITSINT8_H

#include <stdint.h>
#include "type_traits/ConstraintsRemover.h"


namespace open_json {

    /**
     * type: unsigned char, byte
     */
    template<class T>
    struct Is_Int8_Type {
        static const bool Value = false;
    };

    template<>
    struct Is_Int8_Type<int8_t> {
        static const bool Value = true;
    };

    /*
    template<>
    struct Is_Int8_Type<int8_t &> {
        static const bool Value = true;
    };

    template<>
    struct Is_Int8_Type<int8_t *> {
        static const bool Value = true;
    };

    template<>
    struct Is_Int8_Type<const int8_t> {
        static const bool Value = true;
    };

    template<>
    struct Is_Int8_Type<const int8_t &> {
        static const bool Value = true;
    };

    template<>
    struct Is_Int8_Type<const int8_t *> {
        static const bool Value = true;
    };

    template<>
    struct Is_Int8_Type<int8_t *const> {
        static const bool Value = true;
    };

    template<>
    struct Is_Int8_Type<const int8_t *const> {
        static const bool Value = true;
    };

    template<>
    struct Is_Int8_Type<const int8_t *const *> {
        static const bool Value = true;
    };
    */

    template<class T>
    struct Is_Int8 {
    private:
        typedef typename Remove_CVRP<T>::Type U;
    public:
        static const bool Value = Is_Int8_Type<U>::Value;
    };
}


#endif //OPEN_JSON_TYPETRAITSINT8_H
