
#ifndef OPEN_JSON_SETTER_H
#define OPEN_JSON_SETTER_H

namespace open_json {

    template<class ClassT, class ArgT>
    class Setter {
    public:
        using Class = ClassT;
        using Type = ArgT;

        typedef void (Class::*SetterPtr)(ArgT);

        SetterPtr fp;
        const char *name;

        constexpr Setter(SetterPtr fp, const char *name) : fp(fp), name(name) {
        }

    }; //Class Setter

}

#endif //OPEN_JSON_SETTER_H
