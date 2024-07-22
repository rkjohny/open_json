#include <gtest/gtest.h>
#include <string>
#include "../../../include/open_json.h"


namespace open_json_test {
    namespace serialize {

        class BaseClass2 : public open_json::Serializable<BaseClass2> {
        private:
            double score;
            bool is_valid;

        public:
            BaseClass2() : score{24.5678}, is_valid{true} {
            }

            BaseClass2(double d, bool b) : score{d}, is_valid{b} {
            }

            double GetScore() const {
                return score;
            }

            bool IsValid() const {
                return is_valid;
            }

            REGISTER_GETTER_INCLUDING_BASE_START(open_json::Serializable<BaseClass2>)
            GETTER(BaseClass2, double, "score", &BaseClass2::GetScore),
            GETTER(BaseClass2, bool, "is_valid", &BaseClass2::IsValid)
            REGISTER_GETTER_INCLUDING_BASE_END
        };

        class DerivedClass2 : public BaseClass2 {
        private:
            long id;
            std::string name;

        public:
            DerivedClass2() : BaseClass2(), id{10L}, name{"name1"} {
            }

            long GetId() const {
                return id;
            }

            std::string GetName() const {
                return name;
            }

            REGISTER_GETTER_INCLUDING_BASE_START(BaseClass2)
            GETTER(DerivedClass2, long, "id", &DerivedClass2::GetId),
            GETTER(DerivedClass2, std::string, "name", &DerivedClass2::GetName)
            REGISTER_GETTER_INCLUDING_BASE_END
        };

        class DerivedClass3 : public DerivedClass2 {
        private:
            int code;

        public:
            DerivedClass3() : DerivedClass2(), code{200} {
            }

            int GetCode() const {
                return code;
            }

            REGISTER_GETTER_INCLUDING_BASE_START(DerivedClass2)
            GETTER(DerivedClass3, int, "code", &DerivedClass3::GetCode)
            REGISTER_GETTER_INCLUDING_BASE_END
        };

        class SerializeDrivedClassTest2 : public ::testing::Test {
        public:
            BaseClass2 *base;
            DerivedClass2 *derived;
            DerivedClass3 *derived2;

            void SetUp() override {
                base = new BaseClass2();
                derived = new DerivedClass2();
                derived2 = new DerivedClass3();
            }

            void TearDown() override {
                delete base;
                delete derived;
                delete derived2;
            }
        };

        TEST_F(SerializeDrivedClassTest2, BaseTest) {
            nlohmann::json jsonObject = open_json::ToJson(base);

            ASSERT_TRUE(jsonObject.is_object());
            ASSERT_DOUBLE_EQ(base->GetScore(), jsonObject.at("score").template get<double>());
            ASSERT_TRUE(base->IsValid() == jsonObject.at("is_valid").template get<bool>());
        }

        TEST_F(SerializeDrivedClassTest2, DrivedTest) {
            nlohmann::json jsonObject = open_json::ToJson(derived);

            ASSERT_TRUE(jsonObject.is_object());
            ASSERT_DOUBLE_EQ(derived->GetId(), jsonObject.at("id").template get<long>());
            ASSERT_TRUE(0 == derived->GetName().compare(jsonObject.at("name").template get<std::string>()));
            ASSERT_DOUBLE_EQ(derived->GetScore(), jsonObject.at("score").template get<double>());
            ASSERT_TRUE(derived->IsValid() == jsonObject.at("is_valid").template get<bool>());
        }

        TEST_F(SerializeDrivedClassTest2, DrivedTest2) {
            nlohmann::json jsonObject = open_json::ToJson(derived2);

            ASSERT_TRUE(jsonObject.is_object());
            ASSERT_EQ(derived2->GetCode(), jsonObject.at("code").template get<int>());
            ASSERT_DOUBLE_EQ(derived2->GetId(), jsonObject.at("id").template get<long>());
            ASSERT_TRUE(0 == derived2->GetName().compare(jsonObject.at("name").template get<std::string>()));
            ASSERT_DOUBLE_EQ(derived2->GetScore(), jsonObject.at("score").template get<double>());
            ASSERT_TRUE(derived2->IsValid() == jsonObject.at("is_valid").template get<bool>());
        }
    }
}
