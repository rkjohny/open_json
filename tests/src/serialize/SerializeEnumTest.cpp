#include <gtest/gtest.h>
#include "../../../include/open_json.h"

namespace open_json_test {
    namespace serialize {

        enum EnumTest {
            A = 10,
            B = 20,
            C = 30,
        };

        TEST(SerializeEnumTest, ValueType) {
            EnumTest enm = EnumTest::B;
            nlohmann::json jsonObject = open_json::ToJson(enm);
            ASSERT_TRUE(jsonObject.template get<int>() == static_cast<int>(EnumTest::B));
        }
    }
}