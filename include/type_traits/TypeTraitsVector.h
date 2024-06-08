#ifndef OPEN_JSON_TYPETRAITSVECTOR_H
#define OPEN_JSON_TYPETRAITSVECTOR_H

#include <vector>

namespace open_json {
    /**
     * check wheteher T is a std::vector
     */
    template<class T>
    struct Is_Vector {
        static const bool Value = false;
    };

    template<class T, class Alloc>
    struct Is_Vector<std::vector<T, Alloc> > {
        static const bool Value = true;
    };

    template<class T, class Alloc>
    struct Is_Vector<std::vector<T, Alloc> &&> {
        static const bool Value = true;
    };

    template<class T, class Alloc>
    struct Is_Vector<std::vector<T, Alloc> &> {
        static const bool Value = true;
    };
}

#endif //OPEN_JSON_TYPETRAITSVECTOR_H
