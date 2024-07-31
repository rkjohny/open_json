#include <gtest/gtest.h>
#include "../../../include/open_json.h"

namespace open_json_test::deserialize::enum_test {

    enum EnumTest {
        A = 10,
        B = 20,
        C = 30,
    };

    TEST(DeserializeEnumTest, ValueType) {
        nlohmann::json jsonObject = static_cast<int>(EnumTest::B);
        EnumTest enm = open_json::FromJson<EnumTest>(jsonObject);
        ASSERT_TRUE(enm == EnumTest::B);
    }
}
