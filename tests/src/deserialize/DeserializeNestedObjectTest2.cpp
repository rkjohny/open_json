#include <gtest/gtest.h>
#include <nlohmann/json.hpp>
#include <string>
#include "../../../include/open_json.h"


// test deserialization of derived1 class

namespace open_json_test::deserialize::nested::pointer {

    class BaseClass {
    private:
        int *score;

    public:
        virtual ~BaseClass() {
            delete score;
        }

        BaseClass() {
        }

        int* GetScore() const {
            return score;
        }
        void SetScore(int *score) {
            this->score = score;
        }

        REGISTER_SETTER_START
        SETTER(BaseClass, int*, "score", &BaseClass::SetScore)
        REGISTER_SETTER_END
    };

    class NestedClass {
    private:
        BaseClass *base;
        int *code;

    public:
        virtual ~NestedClass() {
            delete base;
            delete code;
        }

        NestedClass() {
        }

        BaseClass *GetBase() const {
            return base;
        }

        void SetBase(BaseClass *base) {
            this->base = base;
        }

        int* GetCode() const {
            return code;
        }

        void SetCode(int *code) {
            this->code = code;
        }

        REGISTER_SETTER_START
        SETTER(NestedClass, BaseClass *, "base", &NestedClass::SetBase),
        SETTER(NestedClass, int*, "code", &NestedClass::SetCode)
        REGISTER_SETTER_END
    };

    class NestedClass2 {
    private:
        NestedClass *nested;
        int *age;

    public:
        virtual ~NestedClass2() {
            delete nested;
            delete age;
        }

        const NestedClass* GetNested() const {
            return nested;
        }

        void SetNested(const NestedClass *n) {
            nested = const_cast<NestedClass *> (n);
        }

        int* GetAge() const {
            return age;
        }

        void SetAge(int *age) {
            this->age = age;
        }

        REGISTER_SETTER_START
        SETTER(NestedClass2, const NestedClass*, "nested", &NestedClass2::SetNested),
        SETTER(NestedClass2, int*, "age", &NestedClass2::SetAge)
        REGISTER_SETTER_END
    };

    class DeserializeNestedObjectTest2 : public ::testing::Test {
    public:
        void SetUp() override {
        }

        void TearDown() override {
        }
    };
    
    TEST_F(DeserializeNestedObjectTest2, NestedTest) {
        nlohmann::json jsonNested = nlohmann::json::object();
        jsonNested["base"] = nlohmann::json::object();
        jsonNested["code"] = 100;
        jsonNested["base"]["score"] = 10;

        nlohmann::json jsonNested2 = nlohmann::json::object();
        jsonNested2["nested"] = nlohmann::json::object();
        jsonNested2["nested"]["base"] = nlohmann::json::object();

        jsonNested2["age"] = 40;
        jsonNested2["nested"]["code"] = 20;
        jsonNested2["nested"]["base"]["score"] = 10;

        NestedClass2 nested2 = open_json::FromJson <NestedClass2 >(jsonNested2);

        ASSERT_EQ(40, *nested2.GetAge());
        ASSERT_EQ(20, *nested2.GetNested()->GetCode());
        ASSERT_EQ(10, *nested2.GetNested()->GetBase()->GetScore());
    }
}