#ifndef OPEN_JSON_TEST_EMPTY_CLASS_H
#define OPEN_JSON_TEST_EMPTY_CLASS_H

#include <nlohmann/json.hpp>
#include "../../include/GetterSetterDef.h"

namespace open_json_test {

    class EmptyClass {
    public:
        EmptyClass() = default;

        virtual ~EmptyClass() = default;

        REGISTER_GETTER_START
        REGISTER_GETTER_END

        REGISTER_SETTER_START
        REGISTER_SETTER_END
    };

}

#endif //OPEN_JSON_TEST_EMPTY_CLASS_H
