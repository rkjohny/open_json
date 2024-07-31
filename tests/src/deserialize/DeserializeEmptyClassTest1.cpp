#include <gtest/gtest.h>
#include <string>
#include <tuple>
#include "../../../include/open_json.h"


namespace open_json_test::serialize::empty_class::without_getters {

    class SerializeEmptyClass : public open_json::Serializable {
    public:
        SerializeEmptyClass() = default;

        REGISTER_SETTER_INCLUDING_BASE_START(open_json::Serializable)
        REGISTER_SETTER_INCLUDING_BASE_END
    };

    class SerializeEmptyClass2 : public open_json::Serializable {
    public:
        SerializeEmptyClass2() = default;
    };

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"

    TEST(DeserializeEmptyClassTest1, EmptyObject1) {
        using Type = typename open_json::Remove_CVR<SerializeEmptyClass>::Type;
        auto setters = Type::setters;
        const size_t lengthSetter = std::tuple_size<decltype(setters)>::value;

        ASSERT_TRUE(lengthSetter == 0);

        SerializeEmptyClass emptyObject = open_json::FromJson<SerializeEmptyClass>(nlohmann::json::object());
        SerializeEmptyClass *emptyObjectPtr = open_json::FromJson<SerializeEmptyClass *>(nlohmann::json::object());
        ASSERT_TRUE(emptyObjectPtr != nullptr);
        delete emptyObjectPtr;
    }

    TEST(DeserializeEmptyClassTest1, EmptyObject2) {
        using Type = typename open_json::Remove_CVR<SerializeEmptyClass2>::Type;
        auto setters = Type::setters;
        const size_t lengthSetter = std::tuple_size<decltype(setters)>::value;

        ASSERT_TRUE(lengthSetter == 0);

        SerializeEmptyClass2 emptyObject = open_json::FromJson<SerializeEmptyClass2>(nlohmann::json::object());
        SerializeEmptyClass2 *emptyObjectPtr = open_json::FromJson<SerializeEmptyClass2 *>(nlohmann::json::object());
        ASSERT_TRUE(emptyObjectPtr != nullptr);
        delete emptyObjectPtr;
    }
#pragma GCC diagnostic pop
}
