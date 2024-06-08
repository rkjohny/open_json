#ifndef OPEN_JSON_GETTERSETTERDEF_H
#define OPEN_JSON_GETTERSETTERDEF_H

namespace open_json {
#define REGISTER_GETTER_START \
        static constexpr auto getters = std::make_tuple(
#define GETTER(CLASS, RETURN_TYPE, NAME, FP) open_json::Getter<CLASS, RETURN_TYPE>(FP, NAME)
#define REGISTER_GETTER_END );


#define REGISTER_SETTER_START \
        static constexpr auto setters = std::make_tuple(
#define SETTER(CLASS, ARG_TYPE, NAME, FP) open_json::Setter<CLASS, ARG_TYPE>(FP, NAME)
#define REGISTER_SETTER_END );


#define REGISTER_GETTER_INCLUDING_BASE_START(BASE_CLASS) \
        static constexpr auto getters = std::tuple_cat(BASE_CLASS::getters, std::make_tuple (
#define REGISTER_GETTER_INCLUDING_BASE_END ));

#define REGISTER_SETTER_INCLUDING_BASE_START(BASE_CLASS) \
        static constexpr auto setters = std::tuple_cat(BASE_CLASS::setters, std::make_tuple (
#define REGISTER_SETTER_INCLUDING_BASE_END ));
}


#endif //OPEN_JSON_GETTERSETTERDEF_H
