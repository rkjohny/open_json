#include <gtest/gtest.h>
#include <string>
#include "../../../include/open_json.h"


namespace open_json_test {
    namespace serialize {

        class BaseClass2 : public open_json::Serializable {
        private:
            double score;
            bool is_valid;

        public:
            BaseClass2() : score{24.5678}, is_valid{true} {
            }

            [[nodiscard]]
            const nlohmann::json ToJson() override {
                return open_json::serializer::ToJsonObject(this);
            }

            double GetScore() const {
                return score;
            }

            bool IsValid() const {
                return is_valid;
            }

            REGISTER_GETTER_INCLUDING_BASE_START(open_json::Serializable)
            GETTER(BaseClass2, double, "score", &BaseClass2::GetScore),
            GETTER(BaseClass2, bool, "is_valid", &BaseClass2::IsValid)
            REGISTER_GETTER_INCLUDING_BASE_END
        };

        class DerivedClass2 : public BaseClass2 {
        private:
            long id;
            std::string name;

        public:
            DerivedClass2() : BaseClass2(), id{ 10 }, name{"name1"} {
            }

            [[nodiscard]]
            const nlohmann::json ToJson() override {
                return open_json::serializer::ToJsonObject(this);
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

            [[nodiscard]]
            const nlohmann::json ToJson() override {
                return open_json::serializer::ToJsonObject(this);
            }

            int GetCode() const {
                return code;
            }

            REGISTER_GETTER_INCLUDING_BASE_START(DerivedClass2)
            GETTER(DerivedClass3, int, "code", &DerivedClass3::GetCode)
            REGISTER_GETTER_INCLUDING_BASE_END
        };

        class SerializeDerivedClassTest2 : public ::testing::Test {
        public:
            BaseClass2 *base2;
            DerivedClass2 *derived2;
            DerivedClass3 *derived3;

            void SetUp() override {
                base2 = new BaseClass2();
                derived2 = new DerivedClass2();
                derived3 = new DerivedClass3();
            }

            void TearDown() override {
                delete base2;
                delete derived2;
                delete derived3;
            }
        };

        TEST_F(SerializeDerivedClassTest2, BaseTest2) {
            nlohmann::json jsonObject = base2->ToJson();

            //std::cout << "Base2:" << jsonObject.dump() << std::endl;

            ASSERT_TRUE(jsonObject.is_object());
            ASSERT_DOUBLE_EQ(base2->GetScore(), jsonObject.at("score").template get<double>());
            ASSERT_TRUE(base2->IsValid() == jsonObject.at("is_valid").template get<bool>());
        }

        TEST_F(SerializeDerivedClassTest2, DrivedTest2) {
            nlohmann::json jsonObject = derived2->ToJson();

            //std::cout << "Derived2:" << jsonObject.dump() << std::endl;

            ASSERT_TRUE(jsonObject.is_object());
            ASSERT_DOUBLE_EQ(derived2->GetId(), jsonObject.at("id").template get<long>());
            ASSERT_TRUE(0 == derived2->GetName().compare(jsonObject.at("name").template get<std::string>()));
            ASSERT_DOUBLE_EQ(derived2->GetScore(), jsonObject.at("score").template get<double>());
            ASSERT_TRUE(derived2->IsValid() == jsonObject.at("is_valid").template get<bool>());
        }

        TEST_F(SerializeDerivedClassTest2, DrivedTest3) {
            nlohmann::json jsonObject = derived3->ToJson();

            //std::cout << "Derived3:" << jsonObject.dump() << std::endl;

            ASSERT_TRUE(jsonObject.is_object());
            ASSERT_EQ(derived3->GetCode(), jsonObject.at("code").template get<int>());
            ASSERT_DOUBLE_EQ(derived3->GetId(), jsonObject.at("id").template get<long>());
            ASSERT_TRUE(0 == derived3->GetName().compare(jsonObject.at("name").template get<std::string>()));
            ASSERT_DOUBLE_EQ(derived3->GetScore(), jsonObject.at("score").template get<double>());
            ASSERT_TRUE(derived3->IsValid() == jsonObject.at("is_valid").template get<bool>());
        }
    }
}
