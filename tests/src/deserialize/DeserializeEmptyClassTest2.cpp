#include <gtest/gtest.h>
#include <string>
#include <tuple>
#include "../../../include/open_json.h"


namespace open_json_test::serialize::empty_class::with_setters {

    class DeserializeEmptyClass {
    public:
        DeserializeEmptyClass() = default;

        REGISTER_SETTER_START
        REGISTER_SETTER_END
    };

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"

    TEST(DeserializeEmptyClassTest2, EmptyObject) {
        using Type = typename open_json::Remove_CVR<DeserializeEmptyClass>::Type;
        auto setters = Type::setters;
        const size_t lengthSetter = std::tuple_size<decltype(setters)>::value;

        ASSERT_TRUE(lengthSetter == 0);

        DeserializeEmptyClass emptyObject = open_json::FromJson<DeserializeEmptyClass>(nlohmann::json::object());
        DeserializeEmptyClass *emptyObjectPtr = open_json::FromJson<DeserializeEmptyClass*>(nlohmann::json::object());
        ASSERT_TRUE(emptyObjectPtr != nullptr);
        delete emptyObjectPtr;
    }
#pragma GCC diagnostic pop
}
