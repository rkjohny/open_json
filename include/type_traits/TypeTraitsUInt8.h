#ifndef OPEN_JSON_TYPETRAITSUINT8_H
#define OPEN_JSON_TYPETRAITSUINT8_H

#include <stdint.h>
#include "type_traits/ConstraintsRemover.h"


namespace open_json {

    /**
     * type: unsigned char, byte
     */
    template<class T>
    struct Is_UInt8_Type {
        static const bool Value = false;
    };

    template<>
    struct Is_UInt8_Type<uint8_t> {
        static const bool Value = true;
    };

    /*
    template<>
    struct Is_UInt8_Type<uint8_t &> {
        static const bool Value = true;
    };

    template<>
    struct Is_UInt8_Type<uint8_t *> {
        static const bool Value = true;
    };

    template<>
    struct Is_UInt8_Type<const uint8_t> {
        static const bool Value = true;
    };

    template<>
    struct Is_UInt8_Type<const uint8_t &> {
        static const bool Value = true;
    };

    template<>
    struct Is_UInt8_Type<const uint8_t *> {
        static const bool Value = true;
    };

    template<>
    struct Is_UInt8_Type<uint8_t *const> {
        static const bool Value = true;
    };

    template<>
    struct Is_UInt8_Type<const uint8_t *const> {
        static const bool Value = true;
    };

    template<>
    struct Is_UInt8_Type<const uint8_t *const *> {
        static const bool Value = true;
    };
    */

    template<class T>
    struct Is_UInt8 {
    private:
        typedef typename Remove_CVRP<T>::Type U;
    public:
        static const bool Value = Is_UInt8_Type<U>::Value;
    };
}


#endif //OPEN_JSON_TYPETRAITSUINT8_H