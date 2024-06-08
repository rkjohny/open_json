#ifndef OPEN_JSON_TYPETRAITSUINT16_H
#define OPEN_JSON_TYPETRAITSUINT16_H

#include <stdint.h>
#include "type_traits/ConstraintsRemover.h"

namespace open_json {
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

    /*
    template<>
    struct Is_UInt16_Type<uint16_t &> {
        static const bool Value = true;
    };

    template<>
    struct Is_UInt16_Type<uint16_t *> {
        static const bool Value = true;
    };

    template<>
    struct Is_UInt16_Type<const uint16_t> {
        static const bool Value = true;
    };

    template<>
    struct Is_UInt16_Type<const uint16_t &> {
        static const bool Value = true;
    };

    template<>
    struct Is_UInt16_Type<const uint16_t *> {
        static const bool Value = true;
    };

    template<>
    struct Is_UInt16_Type<uint16_t *const> {
        static const bool Value = true;
    };

    template<>
    struct Is_UInt16_Type<const uint16_t *const> {
        static const bool Value = true;
    };

    template<>
    struct Is_UInt16_Type<const uint16_t *const *> {
        static const bool Value = true;
    };
    */

    template<class T>
    struct Is_UInt16 {
    private:
        typedef typename Remove_CVRP<T>::Type U;
    public:
        static const bool Value = Is_UInt16_Type<U>::Value;
    };
}

#endif //OPEN_JSON_TYPETRAITSUINT16_H
