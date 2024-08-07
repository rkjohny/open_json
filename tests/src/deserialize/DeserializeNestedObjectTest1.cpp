#include <gtest/gtest.h>
#include <nlohmann/json.hpp>
#include <string>
#include "../../../include/open_json.h"


// test deserialization of derived1 class

namespace open_json_test::deserialize::nested {

    class BaseClass {
    private:
        int score;

    public:
        BaseClass() = default;

        BaseClass(BaseClass &&v) {
            this->score = std::move(v.score);
        }

        BaseClass(const BaseClass &v) {
            this->score = v.score;
        }

        BaseClass &operator=(const BaseClass &v) {
            this->score = v.score;
            return *this;
        }

        BaseClass &operator=(const BaseClass &&v) {
            this->score = std::move(v.score);
            return *this;
        }

        int GetScore() const {
            return score;
        }

        void SetScore(const int &score) {
            this->score = score;
        }

        REGISTER_SETTER_START
        SETTER(BaseClass, const int&, "score", &BaseClass::SetScore)
        REGISTER_SETTER_END
    };

    class NestedClass {
    private:
        BaseClass base;
        int code;

    public:
        NestedClass() = default;

        NestedClass(NestedClass &&v) {
            this->base = std::move(v.base);
            this->code = std::move(v.code);
        }

        NestedClass(const NestedClass &v) {
            this->base = v.base;
            this->code = v.code;
        }

        NestedClass &operator=(const NestedClass &v) {
            this->base = v.base;
            this->code = v.code;
            return *this;
        }

        NestedClass &operator=(const NestedClass &&v) {
            this->base = std::move(v.base);
            this->code = std::move(v.code);
            return *this;
        }

        const BaseClass &GetBase() const {
            return base;
        }

        void SetBase(BaseClass &base) {
            this->base = base;
        }

        int GetCode() const {
            return code;
        }

        void SetCode(const int &code) {
            this->code = code;
        }

        REGISTER_SETTER_START
        SETTER(NestedClass, BaseClass &, "base", &NestedClass::SetBase),
        SETTER(NestedClass, const int&, "code", &NestedClass::SetCode)
        REGISTER_SETTER_END
    };

    class NestedClass2 {
    private:
        NestedClass nested;
        int age;

    public:
        NestedClass2() = default;

        NestedClass2(NestedClass2 &&v) {
            this->nested = std::move(v.nested);
            this->age = std::move(v.age);
        }

        NestedClass2(const NestedClass2 &v) {
            this->nested = v.nested;
            this->age = v.age;
        }

        NestedClass2 &operator=(const NestedClass2 &v) {
            this->nested = v.nested;
            this->age = v.age;
            return *this;
        }

        NestedClass2 &operator=(const NestedClass2 &&v) {
            this->nested = std::move(v.nested);
            this->age = std::move(v.age);
            return *this;
        }

        const NestedClass &GetNested() const {
            return nested;
        }

        void SetNested(NestedClass &n) {
            nested = n;
        }

        int GetAge() const {
            return age;
        }

        void SetAge(const int &age) {
            this->age = age;
        }

        REGISTER_SETTER_START
        SETTER(NestedClass2, NestedClass &, "nested", &NestedClass2::SetNested),
        SETTER(NestedClass2, const int&, "age", &NestedClass2::SetAge)
        REGISTER_SETTER_END

    };

    class DeserializeNestedObjectTest1 : public ::testing::Test {
    public:
        void SetUp() override {
        }

        void TearDown() override {
        }
    };

    TEST_F(DeserializeNestedObjectTest1, NestedTest) {
        nlohmann::json jsonNested = nlohmann::json::object();
        jsonNested["base"] = nlohmann::json::object();
        jsonNested["code"] = 100;
        jsonNested["base"]["score"] = 10;

        NestedClass nested = open_json::FromJson<NestedClass>(jsonNested);
        ASSERT_EQ(100, nested.GetCode());
        ASSERT_EQ(10, nested.GetBase().GetScore());

        nlohmann::json jsonNested2 = nlohmann::json::object();
        jsonNested2["nested"] = nlohmann::json::object();
        jsonNested2["nested"]["base"] = nlohmann::json::object();

        jsonNested2["age"] = 40;
        jsonNested2["nested"]["code"] = 20;
        jsonNested2["nested"]["base"]["score"] = 10;

        NestedClass2 nested2 = open_json::FromJson<NestedClass2>(jsonNested2);

        ASSERT_EQ(40, nested2.GetAge());
        ASSERT_EQ(20, nested2.GetNested().GetCode());
        ASSERT_EQ(10, nested2.GetNested().GetBase().GetScore());
    }
}