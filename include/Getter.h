
#ifndef OPEN_JSON_GETTER_H
#define OPEN_JSON_GETTER_H

namespace open_json {

    template<class ClassT, class ReturnT>
    class Getter {
    public:

        using ClassType = ClassT;
        using ReturnType = ReturnT;

        typedef ReturnT(ClassT::*GetterPtr)() const;

        GetterPtr fp;
        const char *name;

        constexpr Getter(GetterPtr fp, const char *name) : fp(fp), name(name) {
        }
    };
}

#endif //OPEN_JSON_GETTER_H
