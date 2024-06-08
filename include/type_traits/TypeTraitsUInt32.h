#ifndef OPEN_JSON_TYPETRAITSUINT32_H
#define OPEN_JSON_TYPETRAITSUINT32_H

#include <stdint.h>
#include "type_traits/ConstraintsRemover.h"

namespace open_json {
    /**
     * type: unsigned int
     *
     */
    template<class T>
    struct Is_UInt32_Type {
        static const bool Value = false;
    };

    template<>
    struct Is_UInt32_Type<uint32_t> {
        static const bool Value = true;
    };

    /*
    template<>
    struct Is_UInt32_Type<uint32_t &> {
        static const bool Value = true;
    };

    template<>
    struct Is_UInt32_Type<uint32_t *> {
        static const bool Value = true;
    };

    template<>
    struct Is_UInt32_Type<const uint32_t> {
        static const bool Value = true;
    };

    template<>
    struct Is_UInt32_Type<const uint32_t &> {
        static const bool Value = true;
    };

    template<>
    struct Is_UInt32_Type<const uint32_t *> {
        static const bool Value = true;
    };

    template<>
    struct Is_UInt32_Type<uint32_t *const> {
        static const bool Value = true;
    };

    template<>
    struct Is_UInt32_Type<const uint32_t *const> {
        static const bool Value = true;
    };

    template<>
    struct Is_UInt32_Type<const uint32_t *const *> {
        static const bool Value = true;
    };
    */

    template<class T>
    struct Is_UInt32 {
    private:
        typedef typename Remove_CVRP<T>::Type U;
    public:
        static const bool Value = Is_UInt32_Type<U>::Value;
    };
}

#endif //OPEN_JSON_TYPETRAITSUINT32_H
