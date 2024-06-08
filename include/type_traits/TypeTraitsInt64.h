#ifndef OPEN_JSON_TYPETRAITSINT64_H
#define OPEN_JSON_TYPETRAITSINT64_H

#include <stdint.h>
#include "type_traits/ConstraintsRemover.h"

namespace open_json {
    /**
     * type: signed long int or signed long long int
     *
     */
    template<class T>
    struct Is_Int64_Type {
        static const bool Value = false;
    };

    template<>
    struct Is_Int64_Type<int64_t> {
        static const bool Value = true;
    };

    /*
    template<>
    struct Is_Int64_Type<int64_t &> {
        static const bool Value = true;
    };

    template<>
    struct Is_Int64_Type<int64_t *> {
        static const bool Value = true;
    };

    template<>
    struct Is_Int64_Type<const int64_t> {
        static const bool Value = true;
    };

    template<>
    struct Is_Int64_Type<const int64_t &> {
        static const bool Value = true;
    };

    template<>
    struct Is_Int64_Type<const int64_t *> {
        static const bool Value = true;
    };

    template<>
    struct Is_Int64_Type<int64_t *const> {
        static const bool Value = true;
    };

    template<>
    struct Is_Int64_Type<const int64_t *const> {
        static const bool Value = true;
    };

    template<>
    struct Is_Int64_Type<const int64_t *const *> {
        static const bool Value = true;
    };
    */

    template<class T>
    struct Is_Int64 {
    private:
        typedef typename Remove_CVRP<T>::Type U;
    public:
        static const bool Value = Is_Int64_Type<U>::Value;
    };
}


#endif //OPEN_JSON_TYPETRAITSINT64_H
