#ifndef OPEN_JSON_TYPETRAITSINT32_H
#define OPEN_JSON_TYPETRAITSINT32_H

#include <stdint.h>
#include "type_traits/ConstraintsRemover.h"


namespace open_json {
    /**
     * type: signed int
     *
     */
    template<class T>
    struct Is_Int32_Type {
        static const bool Value = false;
    };

    /*
    template<>
    struct Is_Int32_Type<int32_t> {
        static const bool Value = true;
    };

    template<>
    struct Is_Int32_Type<int32_t &> {
        static const bool Value = true;
    };

    template<>
    struct Is_Int32_Type<int32_t *> {
        static const bool Value = true;
    };

    template<>
    struct Is_Int32_Type<const int32_t> {
        static const bool Value = true;
    };

    template<>
    struct Is_Int32_Type<const int32_t &> {
        static const bool Value = true;
    };

    template<>
    struct Is_Int32_Type<const int32_t *> {
        static const bool Value = true;
    };

    template<>
    struct Is_Int32_Type<int32_t *const> {
        static const bool Value = true;
    };

    template<>
    struct Is_Int32_Type<const int32_t *const> {
        static const bool Value = true;
    };

    template<>
    struct Is_Int32_Type<const int32_t *const *> {
        static const bool Value = true;
    };
    */

    template<class T>
    struct Is_Int32 {
    private:
        typedef typename Remove_CVRP<T>::Type U;
    public:
        static const bool Value = Is_Int32_Type<U>::Value;
    };

}

#endif //OPEN_JSON_TYPETRAITSINT32_H
