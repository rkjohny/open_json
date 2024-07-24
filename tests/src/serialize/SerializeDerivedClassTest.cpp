#include <gtest/gtest.h>
#include <string>
#include "../../../include/open_json.h"


namespace open_json_test::serialize {

    class BaseClass {
    private:
        double score;
        bool is_valid;

    public:
        BaseClass() : score{24.5678}, is_valid{true} {
        }

        BaseClass(double d, bool b) : score{d}, is_valid{b} {
        }

        double GetScore() const {
            return score;
        }

        bool IsValid() const {
            return is_valid;
        }

        REGISTER_GETTER_START
        GETTER(BaseClass, double, "score", &BaseClass::GetScore),
        GETTER(BaseClass, bool, "is_valid", &BaseClass::IsValid)
        REGISTER_GETTER_END
    };

    class DerivedClass : public BaseClass {
    private:
        long id;
        std::string name;

    public:
        DerivedClass() : BaseClass(), id{10L}, name{"name1"} {
        }

        long GetId() const {
            return id;
        }

        std::string GetName() const {
            return name;
        }

        REGISTER_GETTER_INCLUDING_BASE_START(BaseClass)
        GETTER(DerivedClass, long, "id", &DerivedClass::GetId),
        GETTER(DerivedClass, std::string, "name", &DerivedClass::GetName)
        REGISTER_GETTER_INCLUDING_BASE_END
    };

    class DerivedClass2 : public DerivedClass {
    private:
        int code;

    public:
        DerivedClass2() : DerivedClass(), code{200} {
        }

        int GetCode() const {
            return code;
        }

        REGISTER_GETTER_INCLUDING_BASE_START(DerivedClass)
        GETTER(DerivedClass2, int, "code", &DerivedClass2::GetCode)
        REGISTER_GETTER_INCLUDING_BASE_END
    };

    class SerializeDrivedClassTest : public ::testing::Test {
    public:
        BaseClass *base;
        DerivedClass *derived;
        DerivedClass2 *derived2;

        void SetUp() override {
            base = new BaseClass();
            derived = new DerivedClass();
            derived2 = new DerivedClass2();
        }

        void TearDown() override {
            delete base;
            delete derived;
            delete derived2;
        }
    };

    TEST_F(SerializeDrivedClassTest, BaseTest) {
        nlohmann::json jsonObject = open_json::ToJson(base);

        ASSERT_TRUE(jsonObject.is_object());
        ASSERT_DOUBLE_EQ(base->GetScore(), jsonObject.at("score").template get<double>());
        ASSERT_TRUE(base->IsValid() == jsonObject.at("is_valid").template get<bool>());
    }

    TEST_F(SerializeDrivedClassTest, DrivedTest) {
        nlohmann::json jsonObject = open_json::ToJson(derived);

        ASSERT_TRUE(jsonObject.is_object());
        ASSERT_DOUBLE_EQ(derived->GetId(), jsonObject.at("id").template get<long>());
        ASSERT_TRUE(0 == derived->GetName().compare(jsonObject.at("name").template get<std::string>()));
        ASSERT_DOUBLE_EQ(derived->GetScore(), jsonObject.at("score").template get<double>());
        ASSERT_TRUE(derived->IsValid() == jsonObject.at("is_valid").template get<bool>());
    }

    TEST_F(SerializeDrivedClassTest, DrivedTest2) {
        nlohmann::json jsonObject = open_json::ToJson(derived2);

        ASSERT_TRUE(jsonObject.is_object());
        ASSERT_EQ(derived2->GetCode(), jsonObject.at("code").template get<int>());
        ASSERT_DOUBLE_EQ(derived2->GetId(), jsonObject.at("id").template get<long>());
        ASSERT_TRUE(0 == derived2->GetName().compare(jsonObject.at("name").template get<std::string>()));
        ASSERT_DOUBLE_EQ(derived2->GetScore(), jsonObject.at("score").template get<double>());
        ASSERT_TRUE(derived2->IsValid() == jsonObject.at("is_valid").template get<bool>());
    }
}

