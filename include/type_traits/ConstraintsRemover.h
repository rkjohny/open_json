#ifndef OPEN_JSON_COMMON_H
#define OPEN_JSON_COMMON_H

#include <type_traits>

namespace open_json {
    template<class T>
    struct Remove_CV {
        typedef typename std::remove_cv<T>::type Type;
    };

    template<class T>
    struct Remove_CVR {
        typedef typename std::remove_reference<typename Remove_CV<T>::Type> Type;
    };

    template<class T>
    struct Remove_CVRP {
        typedef typename std::remove_pointer<typename Remove_CVR<T>::Type>::type Type;
    };
}

#endif //OPEN_JSON_COMMON_H
