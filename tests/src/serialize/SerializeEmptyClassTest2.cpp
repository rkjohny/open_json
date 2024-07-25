#include <gtest/gtest.h>
#include <string>
#include <tuple>
#include "../../../include/open_json.h"


namespace open_json_test::serialize::empty_class::with_getters {

    class SerializeEmptyClass {
    public:
        SerializeEmptyClass() = default;

        REGISTER_GETTER_START
        REGISTER_GETTER_END
    };

    TEST(SerializeEmptyClass, EmptyObject) {
        using Type = typename open_json::Remove_CVR<SerializeEmptyClass>::Type;
        auto getters = Type::getters;
        const size_t lengthGetter = std::tuple_size<decltype(getters)>::value;

        ASSERT_TRUE(lengthGetter == 0);

        SerializeEmptyClass emptyObject;
        nlohmann::json jsonbObject = open_json::ToJson(emptyObject);

        ASSERT_FALSE(jsonbObject.is_null());
        ASSERT_TRUE(jsonbObject.is_object());
        ASSERT_TRUE(jsonbObject.begin() == jsonbObject.end());
    }
}
