#include <gtest/gtest.h>
#include <nlohmann/json.hpp>
#include <string>
#include "../../../include/open_json.h"


// test deserialization of derived1 class

namespace open_json_test::deserialize::nested_3 {

    class BaseClass {
    private:
        int score;
        bool vaild;

    public:
        int GetScore() const {
            return score;
        }
        void SetScore(int score) {
            this->score = score;
        }
        bool IsValid() const {
            return vaild;
        }
        void SetValid(bool valid) {
            this->vaild = valid;
        }
        REGISTER_SETTER_START
        SETTER(BaseClass, int, "score", &BaseClass::SetScore),
        SETTER(BaseClass, bool, "is_valid", &BaseClass::SetValid)
        REGISTER_SETTER_END
    };

    class DerivedClass1 : public BaseClass {
    private:
        long id;
        std::string name;

    public:
        long GetId() const {
            return id;
        }
        void SetId(long id) {
            this->id = id;
        }
        std::string GetName() const {
            return name;
        }
        void SetName(std::string name) {
            this->name = name;
        }
        REGISTER_SETTER_INCLUDING_BASE_START(BaseClass)
        SETTER(DerivedClass1, long, "id", &DerivedClass1::SetId),
        SETTER(DerivedClass1, std::string, "name", &DerivedClass1::SetName)
        REGISTER_SETTER_INCLUDING_BASE_END
    };

    class DerivedClass2 : public DerivedClass1 {
    private:
        int code;

    public:
        int GetCode() const {
            return code;
        }
        void SetCode(int code) {
            this->code = code;
        }
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
            //delete basePtr;
            //delete derived1Ptr;
            //delete derived2Ptr;
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
        DerivedClass1 GetDerived1() const {
            return derived1;
        }
        void SetDerived1(DerivedClass1 d1) {
            this->derived1 = d1;
        }
        DerivedClass1* GetDerived1Ptr() const {
            return derived1Ptr;
        }
        void SetDerived1Ptr(DerivedClass1 *d1) {
            derived1Ptr = d1;
        }

        // Derived2
        const DerivedClass2 &GetDerived2() const {
            return derived2;
        }
        void SetDerived2(const DerivedClass2 &d2) {
            this->derived2 = d2;
        }
        const DerivedClass2* GetDerived2Ptr() const {
            return const_cast<const DerivedClass2 *> (derived2Ptr);
        }
        void SetDerived2Ptr(const DerivedClass2 *d2) {
            derived2Ptr = const_cast<DerivedClass2 *>(d2);
        }

        REGISTER_SETTER_START
        SETTER(NestedClass, const BaseClass &, "base", &NestedClass::SetBase),
        SETTER(NestedClass, const BaseClass *, "base_ptr", &NestedClass::SetBasePtr),
        SETTER(NestedClass, DerivedClass1, "derived1", &NestedClass::SetDerived1),
        SETTER(NestedClass, DerivedClass1*, "derived1_ptr", &NestedClass::SetDerived1Ptr),
        SETTER(NestedClass, const DerivedClass2 &, "derived2", &NestedClass::SetDerived2),
        SETTER(NestedClass, const DerivedClass2 *, "derived2_ptr", &NestedClass::SetDerived2Ptr)
        REGISTER_SETTER_END
    };

    class NestedClass2 {
    private:
        NestedClass nested;

    public:
        const NestedClass& GetNested() const {
            return nested;
        }
        void SetNested(const NestedClass &n) {
            nested = n;
        }
        REGISTER_SETTER_START
                SETTER(NestedClass2, const NestedClass&, "nested", &NestedClass2::SetNested)
        REGISTER_SETTER_END

    };

    class DeserializeNestedObjectTest3 : public ::testing::Test {
    public:
        void SetUp() override {
        }
        void TearDown() override {
        }
    };
    
    TEST_F(DeserializeNestedObjectTest3, NestedTest) {
        nlohmann::json jsonObject = nlohmann::json::object();
        jsonObject["nested"] = nlohmann::json::object();
        jsonObject["nested"]["base"] = nlohmann::json::object();
        jsonObject["nested"]["base_ptr"] = nlohmann::json::object();
        jsonObject["nested"]["derived1"] = nlohmann::json::object();
        jsonObject["nested"]["derived1_ptr"] = nlohmann::json::object();
        jsonObject["nested"]["derived2"] = nlohmann::json::object();
        jsonObject["nested"]["derived2_ptr"] = nlohmann::json::object();

        jsonObject["nested"]["base"]["score"] = 95;
        jsonObject["nested"]["base"]["is_valid"] = true;

        jsonObject["nested"]["base_ptr"]["score"] = 90;
        jsonObject["nested"]["base_ptr"]["is_valid"] = true;

        jsonObject["nested"]["derived1"]["score"] = 85;
        jsonObject["nested"]["derived1"]["is_valid"] = true;
        jsonObject["nested"]["derived1"]["id"] = 100;
        jsonObject["nested"]["derived1"]["name"] = "Mr. Rezaul karim";

        jsonObject["nested"]["derived1_ptr"]["score"] = 80;
        jsonObject["nested"]["derived1_ptr"]["is_valid"] = true;
        jsonObject["nested"]["derived1_ptr"]["id"] = 200;
        jsonObject["nested"]["derived1_ptr"]["name"] = "Mr. Johny";

        jsonObject["nested"]["derived2"]["score"] = 75;
        jsonObject["nested"]["derived2"]["is_valid"] = true;
        jsonObject["nested"]["derived2"]["id"] = 300;
        jsonObject["nested"]["derived2"]["name"] = "Mr. Abdur Rahim";
        jsonObject["nested"]["derived2"]["code"] = 10;

        jsonObject["nested"]["derived2_ptr"]["score"] = 65;
        jsonObject["nested"]["derived2_ptr"]["is_valid"] = true;
        jsonObject["nested"]["derived2_ptr"]["id"] = 400;
        jsonObject["nested"]["derived2_ptr"]["name"] = "Mr. karim";
        jsonObject["nested"]["derived2_ptr"]["code"] = 20;

        NestedClass2 nested2 = open_json::FromJson <NestedClass2> (jsonObject);

        ASSERT_EQ(jsonObject["nested"]["base"]["score"].template get<int>(), nested2.GetNested().GetBase().GetScore());
        ASSERT_EQ(jsonObject["nested"]["base"]["is_valid"].template get<bool>(), nested2.GetNested().GetBasePtr()->IsValid());

        ASSERT_EQ(jsonObject["nested"]["base_ptr"]["score"].template get<int>(), nested2.GetNested().GetBasePtr()->GetScore());
        ASSERT_EQ(jsonObject["nested"]["base_ptr"]["is_valid"].template get<bool>(), nested2.GetNested().GetBasePtr()->IsValid());

        ASSERT_EQ(jsonObject["nested"]["derived1"]["score"].template get<int>(), nested2.GetNested().GetDerived1().GetScore());
        ASSERT_EQ(jsonObject["nested"]["derived1"]["is_valid"].template get<bool>(), nested2.GetNested().GetDerived1().IsValid());
        ASSERT_EQ(jsonObject["nested"]["derived1"]["id"].template get<int>(), nested2.GetNested().GetDerived1().GetId());
        ASSERT_EQ(0, jsonObject["nested"]["derived1"]["name"].template get<std::string>().compare(nested2.GetNested().GetDerived1().GetName()));

        ASSERT_EQ(jsonObject["nested"]["derived1_ptr"]["score"].template get<int>(), nested2.GetNested().GetDerived1Ptr()->GetScore());
        ASSERT_EQ(jsonObject["nested"]["derived1_ptr"]["is_valid"].template get<bool>(), nested2.GetNested().GetDerived1Ptr()->IsValid());
        ASSERT_EQ(jsonObject["nested"]["derived1_ptr"]["id"].template get<int>(), nested2.GetNested().GetDerived1Ptr()->GetId());
        ASSERT_EQ(0, jsonObject["nested"]["derived1_ptr"]["name"].template get<std::string>().compare(nested2.GetNested().GetDerived1Ptr()->GetName()));

        ASSERT_EQ(jsonObject["nested"]["derived2"]["score"].template get<int>(), nested2.GetNested().GetDerived2().GetScore());
        ASSERT_EQ(jsonObject["nested"]["derived2"]["is_valid"].template get<bool>(), nested2.GetNested().GetDerived2().IsValid());
        ASSERT_EQ(jsonObject["nested"]["derived2"]["id"].template get<int>(), nested2.GetNested().GetDerived2().GetId());
        ASSERT_EQ(0, jsonObject["nested"]["derived2"]["name"].template get<std::string>().compare(nested2.GetNested().GetDerived2().GetName()));
        ASSERT_EQ(jsonObject["nested"]["derived2"]["code"].template get<int>(), nested2.GetNested().GetDerived2().GetCode());

        ASSERT_EQ(jsonObject["nested"]["derived2_ptr"]["score"].template get<int>(), nested2.GetNested().GetDerived2Ptr()->GetScore());
        ASSERT_EQ(jsonObject["nested"]["derived2_ptr"]["is_valid"].template get<bool>(), nested2.GetNested().GetDerived2Ptr()->IsValid());
        ASSERT_EQ(jsonObject["nested"]["derived2_ptr"]["id"].template get<int>(), nested2.GetNested().GetDerived2Ptr()->GetId());
        ASSERT_EQ(0, jsonObject["nested"]["derived2_ptr"]["name"].template get<std::string>().compare(nested2.GetNested().GetDerived2Ptr()->GetName()));
        ASSERT_EQ(jsonObject["nested"]["derived2_ptr"]["code"].template get<int>(), nested2.GetNested().GetDerived2Ptr()->GetCode());

//        NestedClass2 *nestedPtr = open_json::FromJson <NestedClass2 *> (jsonObject);
//
//        ASSERT_EQ(jsonObject["nested"]["base"]["score"].template get<int>(), nestedPtr->GetNested().GetBase().GetScore());
//        ASSERT_EQ(jsonObject["nested"]["base"]["is_valid"].template get<bool>(), nestedPtr->GetNested().GetBase().IsValid());
//
//        ASSERT_EQ(jsonObject["nested"]["base_ptr"]["score"].template get<int>(), nestedPtr->GetNested().GetBasePtr()->GetScore());
//        ASSERT_EQ(jsonObject["nested"]["base_ptr"]["is_valid"].template get<bool>(), nestedPtr->GetNested().GetBasePtr()->IsValid());
//
//        ASSERT_EQ(jsonObject["nested"]["derived1"]["score"].template get<int>(), nestedPtr->GetNested().GetDerived1().GetScore());
//        ASSERT_EQ(jsonObject["nested"]["derived1"]["is_valid"].template get<bool>(), nestedPtr->GetNested().GetDerived1().IsValid());
//        ASSERT_EQ(jsonObject["nested"]["derived1"]["id"].template get<int>(), nestedPtr->GetNested().GetDerived1().GetId());
//        ASSERT_EQ(0, jsonObject["nested"]["derived1"]["name"].template get<std::string>().compare(nestedPtr->GetNested().GetDerived1().GetName()));
//
//        ASSERT_EQ(jsonObject["nested"]["derived1_ptr"]["score"].template get<int>(), nestedPtr->GetNested().GetDerived1Ptr()->GetScore());
//        ASSERT_EQ(jsonObject["nested"]["derived1_ptr"]["is_valid"].template get<bool>(), nestedPtr->GetNested().GetDerived1Ptr()->IsValid());
//        ASSERT_EQ(jsonObject["nested"]["derived1_ptr"]["id"].template get<int>(), nestedPtr->GetNested().GetDerived1Ptr()->GetId());
//        ASSERT_EQ(0, jsonObject["nested"]["derived1_ptr"]["name"].template get<std::string>().compare(nestedPtr->GetNested().GetDerived1Ptr()->GetName()));
//
//        ASSERT_EQ(jsonObject["nested"]["derived2"]["score"].template get<int>(), nestedPtr->GetNested().GetDerived2().GetScore());
//        ASSERT_EQ(jsonObject["nested"]["derived2"]["is_valid"].template get<bool>(), nestedPtr->GetNested().GetDerived2().IsValid());
//        ASSERT_EQ(jsonObject["nested"]["derived2"]["id"].template get<int>(), nestedPtr->GetNested().GetDerived2().GetId());
//        ASSERT_EQ(0, jsonObject["nested"]["derived2"]["name"].template get<std::string>().compare(nestedPtr->GetNested().GetDerived2().GetName()));
//        ASSERT_EQ(jsonObject["nested"]["derived2"]["code"].template get<int>(), nestedPtr->GetNested().GetDerived2().GetCode());
//
//        ASSERT_EQ(jsonObject["nested"]["derived2_ptr"]["score"].template get<int>(), nestedPtr->GetNested().GetDerived2Ptr()->GetScore());
//        ASSERT_EQ(jsonObject["nested"]["derived2_ptr"]["is_valid"].template get<bool>(), nestedPtr->GetNested().GetDerived2Ptr()->IsValid());
//        ASSERT_EQ(jsonObject["nested"]["derived2_ptr"]["id"].template get<int>(), nestedPtr->GetNested().GetDerived2Ptr()->GetId());
//        ASSERT_EQ(0, jsonObject["nested"]["derived2_ptr"]["name"].template get<std::string>().compare(nestedPtr->GetNested().GetDerived2Ptr()->GetName()));
//        ASSERT_EQ(jsonObject["nested"]["derived2_ptr"]["code"].template get<int>(), nestedPtr->GetNested().GetDerived2Ptr()->GetCode());
//        delete nestedPtr;
    }
}