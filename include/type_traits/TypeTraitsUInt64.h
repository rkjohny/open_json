#ifndef OPEN_JSON_TYPETRAITSUINT64_H
#define OPEN_JSON_TYPETRAITSUINT64_H

#include <stdint.h>
#include "type_traits/ConstraintsRemover.h"

namespace open_json {
    /**
     * type: unsigned long int or unsigned long long int
     *
     */
    template<class T>
    struct Is_UInt64_Type {
        static const bool Value = false;
    };

    template<>
    struct Is_UInt64_Type<uint64_t> {
        static const bool Value = true;
    };

    /*
    template<>
    struct Is_UInt64_Type<uint64_t &> {
        static const bool Value = true;
    };

    template<>
    struct Is_UInt64_Type<uint64_t *> {
        static const bool Value = true;
    };

    template<>
    struct Is_UInt64_Type<const uint64_t> {
        static const bool Value = true;
    };

    template<>
    struct Is_UInt64_Type<const uint64_t &> {
        static const bool Value = true;
    };

    template<>
    struct Is_UInt64_Type<const uint64_t *> {
        static const bool Value = true;
    };

    template<>
    struct Is_UInt64_Type<uint64_t *const> {
        static const bool Value = true;
    };

    template<>
    struct Is_UInt64_Type<const uint64_t *const> {
        static const bool Value = true;
    };

    template<>
    struct Is_UInt64_Type<const uint64_t *const *> {
        static const bool Value = true;
    };
    */

    template<class T>
    struct Is_UInt64 {
    private:
        typedef typename Remove_CVRP<T>::Type U;
    public:
        static const bool Value = Is_UInt64_Type<U>::Value;
    };

}

#endif //OPEN_JSON_TYPETRAITSUINT64_H
