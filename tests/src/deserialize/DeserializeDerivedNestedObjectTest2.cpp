#include <gtest/gtest.h>
#include <nlohmann/json.hpp>
#include <string>
#include "../../../include/open_json.h"


namespace open_json_test::deserialize::nested::derived::pointer {

    class BaseClass {
    protected:
        double *score;
        bool *is_valid;

    public:
        BaseClass() = default;

        virtual ~BaseClass() {
            delete score;
            delete is_valid;
        };

        BaseClass(BaseClass &&v) {
            this->score = new double(std::move(*v.score));
            this->is_valid = new bool(std::move(*v.is_valid));
        }

        BaseClass(const BaseClass &v) {
            this->score = new double(*v.score);
            this->is_valid = new bool(*v.is_valid);
        }

        BaseClass &operator=(const BaseClass &v) {
            this->score = new double(*v.score);
            this->is_valid = new bool(*v.is_valid);
            return *this;
        }

        BaseClass &operator=(BaseClass &&v) {
            this->score = new double(std::move(*v.score));
            this->is_valid = new bool(std::move(*v.is_valid));
            return *this;
        }

        double *GetScore() const {
            return score;
        }

        bool *IsValid() const {
            return is_valid;
        }

        void SetScore(double *score) {
            this->score = score;
        }

        void SetValid(bool *valid) {
            is_valid = valid;
        }

        REGISTER_SETTER_START
        SETTER(BaseClass, double*, "score", &BaseClass::SetScore),
        SETTER(BaseClass, bool*, "is_valid", &BaseClass::SetValid)
        REGISTER_SETTER_END
    };

    class DerivedClass1 : public BaseClass {
    protected:
        long *id;
        std::string *name;

    public:
        DerivedClass1() = default;

        virtual ~DerivedClass1() {
            delete id;
            delete name;
        }

        DerivedClass1(DerivedClass1 &&v) : BaseClass(std::move(v)) {
            this->id = new long(std::move(*v.id));
            this->name = new std::string(std::move(*v.name));
        }

        DerivedClass1(const DerivedClass1 &v) : BaseClass(v) {
            this->id = new long(*v.id);
            this->name = new std::string(*v.name);
        }

        DerivedClass1 &operator=(const DerivedClass1 &v) {
            this->score = new double(*v.score);
            this->is_valid = new bool(*v.is_valid);
            this->id = new long(*v.id);
            this->name = new std::string(*v.name);
            return *this;
        }

        DerivedClass1 &operator=(DerivedClass1 &&v) {
            this->score = new double(std::move(*v.score));
            this->is_valid = new bool(std::move(*v.is_valid));
            this->id = new long(std::move(*v.id));
            this->name = new std::string(std::move(*v.name));
            return *this;
        }

        long *GetId() const {
            return id;
        }

        std::string *GetName() const {
            return name;
        }

        void SetId(long *id) {
            this->id = id;
        }

        void SetName(std::string *name) {
            this->name = name;
        }

        REGISTER_SETTER_INCLUDING_BASE_START(BaseClass)
        SETTER(DerivedClass1, long*, "id", &DerivedClass1::SetId),
        SETTER(DerivedClass1, std::string*, "name", &DerivedClass1::SetName)
        REGISTER_SETTER_INCLUDING_BASE_END
    };

    class DerivedClass2 : public DerivedClass1 {
    private:
        int *code;

    public:
        DerivedClass2() = default;

        virtual ~DerivedClass2() {
            delete code;
        }

        DerivedClass2(DerivedClass2 &&v) : DerivedClass1(std::move(v)) {
            this->code = new int(std::move(*v.code));
        }

        DerivedClass2(const DerivedClass2 &v) : DerivedClass1(v) {
            this->code = new int(*v.code);
        }

        DerivedClass2 &operator=(const DerivedClass2 &v) {
            this->score = new double(*v.score);
            this->is_valid = new bool(*v.is_valid);
            this->id = new long(*v.id);
            this->name = new std::string(*v.name);
            this->code = new int(*v.code);
            return *this;
        }

        DerivedClass2 &operator=(DerivedClass2 &&v) {
            this->score = new double(std::move(*v.score));
            this->is_valid = new bool(std::move(*v.is_valid));
            this->id = new long(std::move(*v.id));
            this->name = new std::string(std::move(*v.name));
            this->code = new int(std::move(*v.code));
            return *this;
        }

        int *GetCode() const {
            return code;
        }

        void SetCode(int *code) {
            this->code = code;
        }

        REGISTER_SETTER_INCLUDING_BASE_START(DerivedClass1)
        SETTER(DerivedClass2, int*, "code", &DerivedClass2::SetCode)
        REGISTER_SETTER_INCLUDING_BASE_END
    };

    class NestedClass {
    protected:
        BaseClass *base;
        DerivedClass1 *derived1;
        DerivedClass2 *derived2;

    public:
        NestedClass() = default;

        virtual ~NestedClass() {
            delete base;
            delete derived1;
            delete derived2;
        }

        NestedClass(const NestedClass &obj) {
            base = new BaseClass(*obj.base);
            derived1 = new DerivedClass1(*obj.derived1);
            derived2 = new DerivedClass2(*obj.derived2);
        }

        NestedClass(NestedClass &&obj) {
            base = std::move(obj.base);
            derived1 = std::move(obj.derived1);
            derived2 = std::move(obj.derived2);
        }

        NestedClass &operator=(const NestedClass &obj) {
            base = new BaseClass(*obj.base);
            derived1 = new DerivedClass1(*obj.derived1);
            derived2 = new DerivedClass2(*obj.derived2);
            return *this;
        }

        NestedClass &operator=(NestedClass &&obj) {
            base = std::move(obj.base);
            derived1 = std::move(obj.derived1);
            derived2 = std::move(obj.derived2);
            return *this;
        }

        // Base
        BaseClass *GetBase() const {
            return base;
        }

        void SetBase(BaseClass *base) {
            this->base = base;
        }

        // Derived1
        const DerivedClass1 *GetDerived1() const {
            return derived1;
        }

        void SetDerived1(const DerivedClass1 *derived1) {
            this->derived1 = const_cast<DerivedClass1 *>(derived1);
        }

        // Derived2
        DerivedClass2 *GetDerived2() const {
            return derived2;
        }

        void SetDerived2(DerivedClass2 *derived2) {
            this->derived2 = derived2;
        }

        REGISTER_SETTER_START
        SETTER(NestedClass, BaseClass *, "base", &NestedClass::SetBase),
        SETTER(NestedClass, const DerivedClass1 *, "derived1", &NestedClass::SetDerived1),
        SETTER(NestedClass, DerivedClass2 *, "derived2", &NestedClass::SetDerived2)
        REGISTER_SETTER_END
    };

    class NestedClass2 {
    private:
        NestedClass *nested;

    public:
        NestedClass2() = default;

        virtual ~NestedClass2() {
            delete nested;
        }

        NestedClass2(const NestedClass2 &obj) {
            nested = new NestedClass(*obj.nested);
        }

        NestedClass2(NestedClass2 &&obj) {
            nested = new NestedClass(std::move(*obj.nested));
        }

        NestedClass2 &operator=(const NestedClass2 &obj) {
            nested = new NestedClass(*obj.nested);
            return *this;
        }

        NestedClass2 &operator=(NestedClass2 &&obj) {
            nested = new NestedClass(*std::move(obj.nested));
            return *this;
        }

        NestedClass *GetNested() const {
            return nested;
        }

        void SetNested(NestedClass *nested) {
            this->nested = nested;
        }

        REGISTER_SETTER_START
        SETTER(NestedClass2, NestedClass *, "nested", &NestedClass2::SetNested)
        REGISTER_SETTER_END
    };

    class DeserializeDerivedNestedObjectTest2 : public ::testing::Test {
    public:
        void SetUp() override {
        }

        void TearDown() override {
        }
    };


    TEST_F(DeserializeDerivedNestedObjectTest2, NestedTest) {
        nlohmann::json jsonObject = nlohmann::json::object();
        jsonObject["nested"]["base"] = nlohmann::json::object();
        jsonObject["nested"]["derived1"] = nlohmann::json::object();
        jsonObject["nested"]["derived2"] = nlohmann::json::object();

        jsonObject["nested"]["base"]["score"] = 95.01;
        jsonObject["nested"]["base"]["is_valid"] = true;

        jsonObject["nested"]["derived1"]["score"] = 85.01;
        jsonObject["nested"]["derived1"]["is_valid"] = true;
        jsonObject["nested"]["derived1"]["id"] = 100;
        jsonObject["nested"]["derived1"]["name"] = "Mr. Rezaul karim";

        jsonObject["nested"]["derived2"]["score"] = 75.01;
        jsonObject["nested"]["derived2"]["is_valid"] = true;
        jsonObject["nested"]["derived2"]["id"] = 300;
        jsonObject["nested"]["derived2"]["name"] = "Mr. Abdur Rahim";
        jsonObject["nested"]["derived2"]["code"] = 10;


        NestedClass2 nested = open_json::FromJson<NestedClass2>(jsonObject);

        ASSERT_EQ(jsonObject["nested"]["base"]["score"].template get<double>(),
                  *nested.GetNested()->GetBase()->GetScore());
        ASSERT_EQ(jsonObject["nested"]["base"]["is_valid"].template get<bool>(),
                  *nested.GetNested()->GetBase()->IsValid());

        ASSERT_DOUBLE_EQ(jsonObject["nested"]["derived1"]["score"].template get<double>(),
                         *nested.GetNested()->GetDerived1()->GetScore());
        ASSERT_EQ(jsonObject["nested"]["derived1"]["is_valid"].template get<bool>(),
                  *nested.GetNested()->GetDerived1()->IsValid());
        ASSERT_EQ(jsonObject["nested"]["derived1"]["id"].template get<int>(),
                  *nested.GetNested()->GetDerived1()->GetId());
        ASSERT_EQ(0, jsonObject["nested"]["derived1"]["name"].template get<std::string>().compare(
                *nested.GetNested()->GetDerived1()->GetName()));

        ASSERT_DOUBLE_EQ(jsonObject["nested"]["derived2"]["score"].template get<double>(),
                         *nested.GetNested()->GetDerived2()->GetScore());
        ASSERT_EQ(jsonObject["nested"]["derived2"]["is_valid"].template get<bool>(),
                  *nested.GetNested()->GetDerived2()->IsValid());
        ASSERT_EQ(jsonObject["nested"]["derived2"]["id"].template get<int>(),
                  *nested.GetNested()->GetDerived2()->GetId());
        ASSERT_EQ(0, jsonObject["nested"]["derived2"]["name"].template get<std::string>().compare(
                *nested.GetNested()->GetDerived2()->GetName()));
        ASSERT_EQ(jsonObject["nested"]["derived2"]["code"].template get<int>(),
                  *nested.GetNested()->GetDerived2()->GetCode());


        NestedClass2 *nestedPtr = open_json::FromJson<NestedClass2 *>(jsonObject);

        ASSERT_DOUBLE_EQ(jsonObject["nested"]["base"]["score"].template get<double>(),
                         *nestedPtr->GetNested()->GetBase()->GetScore());
        ASSERT_EQ(jsonObject["nested"]["base"]["is_valid"].template get<bool>(),
                  *nestedPtr->GetNested()->GetBase()->IsValid());

        ASSERT_DOUBLE_EQ(jsonObject["nested"]["derived1"]["score"].template get<double>(),
                         *nestedPtr->GetNested()->GetDerived1()->GetScore());
        ASSERT_EQ(jsonObject["nested"]["derived1"]["is_valid"].template get<bool>(),
                  *nestedPtr->GetNested()->GetDerived1()->IsValid());
        ASSERT_EQ(jsonObject["nested"]["derived1"]["id"].template get<int>(),
                  *nestedPtr->GetNested()->GetDerived1()->GetId());
        ASSERT_EQ(0, jsonObject["nested"]["derived1"]["name"].template get<std::string>().compare(
                *nestedPtr->GetNested()->GetDerived1()->GetName()));

        ASSERT_DOUBLE_EQ(jsonObject["nested"]["derived2"]["score"].template get<double>(),
                         *nestedPtr->GetNested()->GetDerived2()->GetScore());
        ASSERT_EQ(jsonObject["nested"]["derived2"]["is_valid"].template get<bool>(),
                  *nestedPtr->GetNested()->GetDerived2()->IsValid());
        ASSERT_EQ(jsonObject["nested"]["derived2"]["id"].template get<int>(),
                  *nestedPtr->GetNested()->GetDerived2()->GetId());
        ASSERT_EQ(0, jsonObject["nested"]["derived2"]["name"].template get<std::string>().compare(
                *nestedPtr->GetNested()->GetDerived2()->GetName()));
        ASSERT_EQ(jsonObject["nested"]["derived2"]["code"].template get<int>(),
                  *nestedPtr->GetNested()->GetDerived2()->GetCode());
        delete nestedPtr;
    }
}