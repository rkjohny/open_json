#include <gtest/gtest.h>
#include <string>
#include <tuple>
#include "../../../include/open_json.h"


namespace open_json_test {
    namespace serialize {

        class SerializeEmptyClass : public open_json::Serializable<SerializeEmptyClass> {
        public:
            SerializeEmptyClass() = default;
        };

        TEST(SerializeEmptyClass, EmptyObject) {
            using Type = typename open_json::Remove_CVR<SerializeEmptyClass>::Type;
            auto getters = Type::getters;
            const size_t lengthGetter = std::tuple_size<decltype(getters)>::value;

            ASSERT_TRUE(lengthGetter == 0);

            SerializeEmptyClass emptyObject;
            nlohmann::json jsonbObject = emptyObject.ToJson();

            ASSERT_FALSE(jsonbObject.is_null());
            ASSERT_TRUE(jsonbObject.is_object());
            ASSERT_TRUE(jsonbObject.begin() == jsonbObject.end());
        }
    }
}