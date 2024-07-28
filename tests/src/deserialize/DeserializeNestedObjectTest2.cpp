#include <gtest/gtest.h>
#include <nlohmann/json.hpp>
#include <string>
#include "../../../include/open_json.h"


// test deserialization of derived1 class

namespace open_json_test::deserialize::nested_2 {

    class BaseClass {
    private:
        double score;
        bool is_valid;

    public:
        BaseClass() : score{24.5678}, is_valid{false} {
        }
        
        virtual ~BaseClass() = default;

        double GetScore() const {
            return score;
        }

        bool IsValid() const {
            return is_valid;
        }

        void SetScore(double d) {
            score = d;
        }

        void SetValid(bool b) {
            is_valid = b;
        }

        virtual void Clear() {
            score = 0;
            is_valid = false;
        }

        REGISTER_GETTER_START
        GETTER(BaseClass, double, "score", &BaseClass::GetScore),
        GETTER(BaseClass, bool, "is_valid", &BaseClass::IsValid)
        REGISTER_GETTER_END

        REGISTER_SETTER_START
        SETTER(BaseClass, double, "score", &BaseClass::SetScore),
        SETTER(BaseClass, bool, "is_valid", &BaseClass::SetValid)
        REGISTER_SETTER_END
    };

    class DerivedClass1 : public BaseClass {
    private:
        long id;
        std::string name;

    public:
        DerivedClass1() : BaseClass(), id{10L}, name{"name1"} {
        }

        virtual ~DerivedClass1() = default;

        long GetId() const {
            return id;
        }

        std::string GetName() const {
            return name;
        }

        void SetId(long i) {
            id = i;
        }

        void SetName(std::string s) {
            name = s;
        }

        void Clear() override {
            BaseClass::Clear();
            id = 0;
            name = "";
        }

        REGISTER_GETTER_INCLUDING_BASE_START(BaseClass)
        GETTER(DerivedClass1, long, "id", &DerivedClass1::GetId),
        GETTER(DerivedClass1, std::string, "name", &DerivedClass1::GetName)
        REGISTER_GETTER_INCLUDING_BASE_END

        REGISTER_SETTER_INCLUDING_BASE_START(BaseClass)
        SETTER(DerivedClass1, long, "id", &DerivedClass1::SetId),
        SETTER(DerivedClass1, std::string, "name", &DerivedClass1::SetName)
        REGISTER_SETTER_INCLUDING_BASE_END
    };

    class DerivedClass2 : public DerivedClass1 {
    private:
        int code;

    public:
        DerivedClass2() : DerivedClass1(), code{200} {
        }

        int GetCode() const {
            return code;
        }

        void SetCode(int code) {
            this->code = code;
        }

        void Clear() override {
            code = 0;
            DerivedClass1::Clear();
        }

        REGISTER_GETTER_INCLUDING_BASE_START(DerivedClass1)
        GETTER(DerivedClass2, int, "code", &DerivedClass2::GetCode)
        REGISTER_GETTER_INCLUDING_BASE_END

        REGISTER_SETTER_INCLUDING_BASE_START(DerivedClass1)
        SETTER(DerivedClass2, int, "code", &DerivedClass2::SetCode)
        REGISTER_SETTER_INCLUDING_BASE_END
    };

    class NestedClass {
    private:
        BaseClass base;
        BaseClass *basePtr;

        DerivedClass1 derived1;
        DerivedClass1 *derived1Ptr;

        DerivedClass2 derived2;
        DerivedClass2 *derived2Ptr;

    public:
        virtual ~NestedClass() {
            delete basePtr;
            delete derived1Ptr;
            delete derived2Ptr;
        }

        // Base
        const BaseClass &GetBase() const {
            return base;
        }

        void SetBase(const BaseClass &b) {
            this->base = b;
        }

        const BaseClass* GetBasePtr() const {
            return basePtr;
        }

        void SetBasePtr(const BaseClass *b) {
            basePtr = const_cast<BaseClass *>(b);
        }

        // Derived1
        const DerivedClass1 &GetDerived1() const {
            return derived1;
        }

        void SetDerived1(const DerivedClass1 &b) {
            this->derived1 = b;
        }

        const DerivedClass1* GetDerived1Ptr() const {
            return const_cast<const DerivedClass1 *> (derived1Ptr);
        }

        void SetDerived1Ptr(const DerivedClass1 *b) {
            derived1Ptr = const_cast<DerivedClass1 *>(b);
        }

        // Derived2
        const DerivedClass2 &GetDerived2() const {
            return derived2;
        }

        void SetDerived2(const DerivedClass2 &b) {
            this->derived2 = b;
        }

        const DerivedClass2* GetDerived2Ptr() const {
            return const_cast<const DerivedClass2 *> (derived2Ptr);
        }

        void SetDerived2Ptr(const DerivedClass2 *b) {
            derived2Ptr = const_cast<DerivedClass2 *>(b);
        }

        REGISTER_GETTER_START
        GETTER(NestedClass, const BaseClass &, "base", &NestedClass::GetBase),
        GETTER(NestedClass, const BaseClass *, "base_ptr", &NestedClass::GetBasePtr),
        GETTER(NestedClass, const DerivedClass1 &, "derived1", &NestedClass::GetDerived1),
        GETTER(NestedClass, const DerivedClass1 *, "derived1_ptr", &NestedClass::GetDerived1Ptr),
        GETTER(NestedClass, const DerivedClass2 &, "derived2", &NestedClass::GetDerived2),
        GETTER(NestedClass, const DerivedClass2 *, "derived2_ptr", &NestedClass::GetDerived2Ptr)
        REGISTER_GETTER_END

        REGISTER_SETTER_START
        SETTER(NestedClass, const BaseClass &, "base", &NestedClass::SetBase),
        SETTER(NestedClass, const BaseClass *, "base_ptr", &NestedClass::SetBasePtr),
        SETTER(NestedClass, const DerivedClass1 &, "derived1", &NestedClass::SetDerived1),
        SETTER(NestedClass, const DerivedClass1 *, "derived1_ptr", &NestedClass::SetDerived1Ptr),
        SETTER(NestedClass, const DerivedClass2 &, "derived2", &NestedClass::SetDerived2),
        SETTER(NestedClass, const DerivedClass2 *, "derived2_ptr", &NestedClass::SetDerived2Ptr)
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
        nlohmann::json jsonObject = nlohmann::json::object();
        jsonObject["base"] = nlohmann::json::object();
        jsonObject["base_ptr"] = nlohmann::json::object();
        jsonObject["derived1"] = nlohmann::json::object();
        jsonObject["derived1_ptr"] = nlohmann::json::object();
        jsonObject["derived2"] = nlohmann::json::object();
        jsonObject["derived2_ptr"] = nlohmann::json::object();

        jsonObject["base"]["score"] = 95.01;
        jsonObject["base"]["is_valid"] = true;

        jsonObject["base_ptr"]["score"] = 90.01;
        jsonObject["base_ptr"]["is_valid"] = true;

        jsonObject["derived1"]["score"] = 85.01;
        jsonObject["derived1"]["is_valid"] = true;
        jsonObject["derived1"]["id"] = 100;
        jsonObject["derived1"]["name"] = "Mr. Rezaul karim";

        jsonObject["derived1_ptr"]["score"] = 80.01;
        jsonObject["derived1_ptr"]["is_valid"] = true;
        jsonObject["derived1_ptr"]["id"] = 200;
        jsonObject["derived1_ptr"]["name"] = "Mr. Johny";

        jsonObject["derived2"]["score"] = 75.01;
        jsonObject["derived2"]["is_valid"] = true;
        jsonObject["derived2"]["id"] = 300;
        jsonObject["derived2"]["name"] = "Mr. Abdur Rahim";
        jsonObject["derived2"]["code"] = 10;

        jsonObject["derived2_ptr"]["score"] = 65.01;
        jsonObject["derived2_ptr"]["is_valid"] = true;
        jsonObject["derived2_ptr"]["id"] = 400;
        jsonObject["derived2_ptr"]["name"] = "Mr. karim";
        jsonObject["derived2_ptr"]["code"] = 20;

        NestedClass nested = open_json::FromJson <NestedClass > (jsonObject);

        ASSERT_EQ(jsonObject["base"]["score"].template get<double>(), nested.GetBase().GetScore());
        ASSERT_EQ(jsonObject["base"]["is_valid"].template get<bool>(), nested.GetBase().IsValid());

        ASSERT_DOUBLE_EQ(jsonObject["base_ptr"]["score"].template get<double>(), nested.GetBasePtr()->GetScore());
        ASSERT_EQ(jsonObject["base_ptr"]["is_valid"].template get<bool>(), nested.GetBasePtr()->IsValid());

        ASSERT_DOUBLE_EQ(jsonObject["derived1"]["score"].template get<double>(), nested.GetDerived1().GetScore());
        ASSERT_EQ(jsonObject["derived1"]["is_valid"].template get<bool>(), nested.GetDerived1().IsValid());
        ASSERT_EQ(jsonObject["derived1"]["id"].template get<int>(), nested.GetDerived1().GetId());
        ASSERT_EQ(0, jsonObject["derived1"]["name"].template get<std::string>().compare(nested.GetDerived1().GetName()));

        ASSERT_DOUBLE_EQ(jsonObject["derived1_ptr"]["score"].template get<double>(), nested.GetDerived1Ptr()->GetScore());
        ASSERT_EQ(jsonObject["derived1_ptr"]["is_valid"].template get<bool>(), nested.GetDerived1Ptr()->IsValid());
        ASSERT_EQ(jsonObject["derived1_ptr"]["id"].template get<int>(), nested.GetDerived1Ptr()->GetId());
        ASSERT_EQ(0, jsonObject["derived1_ptr"]["name"].template get<std::string>().compare(nested.GetDerived1Ptr()->GetName()));

        ASSERT_DOUBLE_EQ(jsonObject["derived2"]["score"].template get<double>(), nested.GetDerived2().GetScore());
        ASSERT_EQ(jsonObject["derived2"]["is_valid"].template get<bool>(), nested.GetDerived2().IsValid());
        ASSERT_EQ(jsonObject["derived2"]["id"].template get<int>(), nested.GetDerived2().GetId());
        ASSERT_EQ(0, jsonObject["derived2"]["name"].template get<std::string>().compare(nested.GetDerived2().GetName()));
        ASSERT_EQ(jsonObject["derived2"]["code"].template get<int>(), nested.GetDerived2().GetCode());

        ASSERT_DOUBLE_EQ(jsonObject["derived2_ptr"]["score"].template get<double>(), nested.GetDerived2Ptr()->GetScore());
        ASSERT_EQ(jsonObject["derived2_ptr"]["is_valid"].template get<bool>(), nested.GetDerived2Ptr()->IsValid());
        ASSERT_EQ(jsonObject["derived2_ptr"]["id"].template get<int>(), nested.GetDerived2Ptr()->GetId());
        ASSERT_EQ(0, jsonObject["derived2_ptr"]["name"].template get<std::string>().compare(nested.GetDerived2Ptr()->GetName()));
        ASSERT_EQ(jsonObject["derived2_ptr"]["code"].template get<int>(), nested.GetDerived2Ptr()->GetCode());

        NestedClass *nestedPtr = open_json::FromJson <NestedClass *> (jsonObject);

        ASSERT_DOUBLE_EQ(jsonObject["base"]["score"].template get<double>(), nestedPtr->GetBase().GetScore());
        ASSERT_EQ(jsonObject["base"]["is_valid"].template get<bool>(), nestedPtr->GetBase().IsValid());

        ASSERT_DOUBLE_EQ(jsonObject["base_ptr"]["score"].template get<double>(), nestedPtr->GetBasePtr()->GetScore());
        ASSERT_EQ(jsonObject["base_ptr"]["is_valid"].template get<bool>(), nestedPtr->GetBasePtr()->IsValid());

        ASSERT_DOUBLE_EQ(jsonObject["derived1"]["score"].template get<double>(), nestedPtr->GetDerived1().GetScore());
        ASSERT_EQ(jsonObject["derived1"]["is_valid"].template get<bool>(), nestedPtr->GetDerived1().IsValid());
        ASSERT_EQ(jsonObject["derived1"]["id"].template get<int>(), nestedPtr->GetDerived1().GetId());
        ASSERT_EQ(0, jsonObject["derived1"]["name"].template get<std::string>().compare(nestedPtr->GetDerived1().GetName()));

        ASSERT_DOUBLE_EQ(jsonObject["derived1_ptr"]["score"].template get<double>(), nestedPtr->GetDerived1Ptr()->GetScore());
        ASSERT_EQ(jsonObject["derived1_ptr"]["is_valid"].template get<bool>(), nestedPtr->GetDerived1Ptr()->IsValid());
        ASSERT_EQ(jsonObject["derived1_ptr"]["id"].template get<int>(), nestedPtr->GetDerived1Ptr()->GetId());
        ASSERT_EQ(0, jsonObject["derived1_ptr"]["name"].template get<std::string>().compare(nestedPtr->GetDerived1Ptr()->GetName()));

        ASSERT_DOUBLE_EQ(jsonObject["derived2"]["score"].template get<double>(), nestedPtr->GetDerived2().GetScore());
        ASSERT_EQ(jsonObject["derived2"]["is_valid"].template get<bool>(), nestedPtr->GetDerived2().IsValid());
        ASSERT_EQ(jsonObject["derived2"]["id"].template get<int>(), nestedPtr->GetDerived2().GetId());
        ASSERT_EQ(0, jsonObject["derived2"]["name"].template get<std::string>().compare(nestedPtr->GetDerived2().GetName()));
        ASSERT_EQ(jsonObject["derived2"]["code"].template get<int>(), nestedPtr->GetDerived2().GetCode());

        ASSERT_DOUBLE_EQ(jsonObject["derived2_ptr"]["score"].template get<double>(), nestedPtr->GetDerived2Ptr()->GetScore());
        ASSERT_EQ(jsonObject["derived2_ptr"]["is_valid"].template get<bool>(), nestedPtr->GetDerived2Ptr()->IsValid());
        ASSERT_EQ(jsonObject["derived2_ptr"]["id"].template get<int>(), nestedPtr->GetDerived2Ptr()->GetId());
        ASSERT_EQ(0, jsonObject["derived2_ptr"]["name"].template get<std::string>().compare(nestedPtr->GetDerived2Ptr()->GetName()));
        ASSERT_EQ(jsonObject["derived2_ptr"]["code"].template get<int>(), nestedPtr->GetDerived2Ptr()->GetCode());
        delete nestedPtr;
    }

}