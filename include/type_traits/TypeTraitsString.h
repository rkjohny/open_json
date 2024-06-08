#ifndef OPEN_JSON_TYPETRAITSSTRING_H
#define OPEN_JSON_TYPETRAITSSTRING_H

#include <string>
#include "type_traits/ConstraintsRemover.h"

namespace open_json {
    /**
     * type check for string
     */
    template<class T>
    struct Is_String_Type {
        static const bool Value = false;
    };

    template<>
    struct Is_String_Type<std::string> {
        static const bool Value = true;
    };

    /*
    template<>
    struct Is_String_Type<std::string &> {
        static const bool Value = true;
    };

    template<>
    struct Is_String_Type<std::string *> {
        static const bool Value = true;
    };

    template<>
    struct Is_String_Type<const std::string> {
        static const bool Value = true;
    };

    template<>
    struct Is_String_Type<const std::string &> {
        static const bool Value = true;
    };

    template<>
    struct Is_String_Type<const std::string *> {
        static const bool Value = true;
    };

    template<>
    struct Is_String_Type<std::string *const> {
        static const bool Value = true;
    };

    template<>
    struct Is_String_Type<const std::string *const> {
        static const bool Value = true;
    };

    template<>
    struct Is_String_Type<const std::string *const *> {
        static const bool Value = true;
    };
    */

    template<class T>
    struct Is_String {
    private:
        typedef typename Remove_CVRP<T>::Type U;
    public:
        static const bool Value = Is_String_Type<U>::Value;
    };

}

#endif //OPEN_JSON_TYPETRAITSSTRING_H
