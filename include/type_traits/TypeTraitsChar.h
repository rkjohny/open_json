
#ifndef OPEN_JSON_TYPETRAITSCHAR_H
#define OPEN_JSON_TYPETRAITSCHAR_H

#include "type_traits/ConstraintsRemover.h"

namespace open_json {
    /**
     * type char
     * it may vary among platforms
     */
    template<class T>
    struct Is_Char_Type {
        static const bool Value = false;
    };

    template<>
    struct Is_Char_Type<char> {
        static const bool Value = true;
    };

    /*
    template<>
    struct Is_Char_Type<char &> {
        static const bool Value = true;
    };

    template<>
    struct Is_Char_Type<char *> {
        static const bool Value = true;
    };

    template<>
    struct Is_Char_Type<const char> {
        static const bool Value = true;
    };

    template<>
    struct Is_Char_Type<const char &> {
        static const bool Value = true;
    };

    template<>
    struct Is_Char_Type<const char *> {
        static const bool Value = true;
    };

    template<>
    struct Is_Char_Type<char *const> {
        static const bool Value = true;
    };

    template<>
    struct Is_Char_Type<const char *const> {
        static const bool Value = true;
    };

    template<>
    struct Is_Char_Type<const char *const *> {
        static const bool Value = true;
    };
    */

    template<class T>
    struct Is_Char {
    private:
        typedef typename Remove_CVRP<T>::Type U;
    public:
        static const bool Value = Is_Char_Type<U>::Value;
    };
}


#endif //OPEN_JSON_TYPETRAITSCHAR_H
