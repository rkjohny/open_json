#include <gtest/gtest.h>
#include <nlohmann/json.hpp>
#include <string>
#include "../../../include/open_json.h"
#include "../../include/RandomGenerator.h"


namespace open_json_test::deserialize::nested::derived::vector {

    class BaseClass {
    protected:
        double *score = nullptr;
        bool is_valid;

    public:
        BaseClass() = default;

        virtual ~BaseClass() {
            delete score;
        }

        BaseClass(BaseClass &&v) {
            this->score = new double(std::move(*v.score));
            this->is_valid = std::move(v.is_valid);
        }

        BaseClass(const BaseClass &v) {
            this->score = new double(*v.score);
            this->is_valid = v.is_valid;
        }

        BaseClass &operator=(const BaseClass &v) {
            this->score = new double(*v.score);
            this->is_valid = v.is_valid;
            return *this;
        }

        BaseClass &operator=(const BaseClass &&v) {
            this->score = new double(std::move(*v.score));
            this->is_valid = std::move(v.is_valid);
            return *this;
        }

        double *GetScore() const {
            return score;
        }

        bool IsValid() const {
            return is_valid;
        }

        void SetScore(double *score) {
            this->score = score;
        }

        void SetValid(bool valid) {
            is_valid = valid;
        }

        REGISTER_SETTER_START
        SETTER(BaseClass, double*, "score", &BaseClass::SetScore),
        SETTER(BaseClass, bool, "is_valid", &BaseClass::SetValid)
        REGISTER_SETTER_END
    };

    class DerivedClass1 : public BaseClass {
    protected:
        long *id = nullptr;
        std::string name;

    public:
        DerivedClass1() = default;

        virtual ~DerivedClass1() {
            delete id;
        }

        DerivedClass1(DerivedClass1 &&v) : BaseClass(std::move(v)) {
            this->id = new long(std::move(*v.id));
            this->name = std::move(v.name);
        }

        DerivedClass1(const DerivedClass1 &v) : BaseClass(v) {
            this->id = new long(*v.id);
            this->name = v.name;
        }

        DerivedClass1 &operator=(const DerivedClass1 &v) {
            this->score = new double(*v.score);
            this->is_valid = v.is_valid;
            this->id = new long(*v.id);
            this->name = v.name;
            return *this;
        }

        DerivedClass1 &operator=(DerivedClass1 &&v) {
            this->score = new double(std::move(*v.score));
            this->is_valid = std::move(v.is_valid);
            this->id = new long(std::move(*v.id));
            this->name = std::move(v.name);
            return *this;
        }

        long *GetId() const {
            return id;
        }

        std::string GetName() const {
            return name;
        }

        void SetId(long *id) {
            this->id = id;
        }

        void SetName(std::string name) {
            this->name = name;
        }

        REGISTER_SETTER_INCLUDING_BASE_START(BaseClass)
        SETTER(DerivedClass1, long*, "id", &DerivedClass1::SetId),
        SETTER(DerivedClass1, std::string, "name", &DerivedClass1::SetName)
        REGISTER_SETTER_INCLUDING_BASE_END
    };

    class DerivedClass2 : public DerivedClass1 {
    private:
        int code;
        int *age = nullptr;

    public:
        DerivedClass2() = default;

        virtual ~DerivedClass2() {
            delete age;
        }

        DerivedClass2(DerivedClass2 &&v) : DerivedClass1(std::move(v)) {
            this->code = std::move(v.code);
            this->age = new int(std::move(*v.age));
        }

        DerivedClass2(const DerivedClass2 &v) : DerivedClass1(v) {
            this->code = v.code;
            this->age = new int(*v.age);
        }

        DerivedClass2 &operator=(const DerivedClass2 &v) {
            this->score = new double(*v.score);
            this->is_valid = v.is_valid;
            this->id = new long(*v.id);
            this->name = v.name;
            this->code = v.code;
            this->age = new int(*v.age);
            return *this;
        }

        DerivedClass2 &operator=(DerivedClass2 &&v) {
            this->score = new double(std::move(*v.score));
            this->is_valid = std::move(v.is_valid);
            this->id = new long(std::move(*v.id));
            this->name = std::move(v.name);
            this->code = std::move(v.code);
            this->age = new int(*v.age);
            return *this;
        }

        int GetCode() const {
            return code;
        }

        void SetCode(int code) {
            this->code = code;
        }

        int *GetAge() const {
            return age;
        }

        void SetAge(int *a) {
            age = a;
        }

        REGISTER_SETTER_INCLUDING_BASE_START(DerivedClass1)
        SETTER(DerivedClass2, int, "code", &DerivedClass2::SetCode),
        SETTER(DerivedClass2, int*, "age", &DerivedClass2::SetAge)
        REGISTER_SETTER_INCLUDING_BASE_END
    };

    class NestedClass {
    private:
        DerivedClass2 derived2;
        DerivedClass2 *derived2Ptr = nullptr;

    public:
        NestedClass() = default;

        virtual ~NestedClass() {
            delete derived2Ptr;
        };

        NestedClass(const NestedClass &obj) {
            derived2 = obj.derived2;
            derived2Ptr = new DerivedClass2(*obj.derived2Ptr);
        }

        NestedClass(NestedClass &&obj) {
            derived2 = std::move(obj.derived2);
            derived2Ptr = new DerivedClass2(std::move(*obj.derived2Ptr));
        }

        NestedClass &operator=(const NestedClass &obj) {
            derived2 = obj.derived2;
            derived2Ptr = new DerivedClass2(*obj.derived2Ptr);
            return *this;
        }

        NestedClass &operator=(NestedClass &&obj) {
            derived2 = std::move(obj.derived2);
            derived2Ptr = new DerivedClass2(std::move(*obj.derived2Ptr));
            return *this;
        }

        // Derived1
        const DerivedClass2 &GetDerived2() const {
            return derived2;
        }

        void SetDerived2(const DerivedClass2 &derived2) {
            this->derived2 = derived2;
        }

        // Derived2
        const DerivedClass2 *GetDerived2Ptr() const {
            return derived2Ptr;
        }

        void SetDerived2Ptr(const DerivedClass2 *derived2) {
            this->derived2Ptr = const_cast<DerivedClass2 *>(derived2);
        }

        REGISTER_SETTER_START
        SETTER(NestedClass, const DerivedClass2 &, "derived", &NestedClass::SetDerived2),
        SETTER(NestedClass, const DerivedClass2 *, "derived_ptr", &NestedClass::SetDerived2Ptr)
        REGISTER_SETTER_END
    };

    class NestedClass2 {
    private:
        NestedClass nested;
        NestedClass *nestedPtr = nullptr;
        std::vector<NestedClass> nestedList;
        std::vector<NestedClass *> nestedPtrList;

    public:
        NestedClass2() = default;

        virtual ~NestedClass2() {
            delete nestedPtr;
            for (auto p: nestedPtrList) {
                delete p;
            }
        };

        NestedClass2(const NestedClass2 &obj) {
            nested = obj.nested;
            nestedPtr = new NestedClass(*obj.nestedPtr);
            nestedList = obj.nestedList;
            // do not directly assign vector of pointers (in fact any pointer), because it will assign the pointer directly
            for (auto p: obj.nestedPtrList) {
                nestedPtrList.push_back(new NestedClass(*p));
            }
        }

        NestedClass2(NestedClass2 &&obj) {
            nested = std::move(obj.nested);
            nestedPtr = new NestedClass(std::move(*obj.nestedPtr));
            nestedList = std::move(obj.nestedList);
            // do not directly assign vector of pointers (in fact any pointer), because it will assign the pointer directly
            for (auto p: obj.nestedPtrList) {
                nestedPtrList.push_back(new NestedClass(std::move(*p)));
            }
        }

        NestedClass2 &operator=(const NestedClass2 &obj) {
            nested = obj.nested;
            nestedPtr = new NestedClass(*obj.nestedPtr);
            nestedList = obj.nestedList;
            // do not directly assign vector of pointers (in fact any pointer), because it will assign the pointer directly
            for (auto p: obj.nestedPtrList) {
                nestedPtrList.push_back(new NestedClass(*p));
            }
            return *this;
        }

        NestedClass2 &operator=(NestedClass2 &&obj) {
            nested = std::move(obj.nested);
            nestedPtr = new NestedClass(std::move(*obj.nestedPtr));
            nestedList = std::move(obj.nestedList);
            // do not directly assign vector of pointers (in fact any pointer), because it will assign the pointer directly
            for (auto p: obj.nestedPtrList) {
                nestedPtrList.push_back(new NestedClass(std::move(*p)));
            }
            return *this;
        }

        const NestedClass &GetNested() const {
            return nested;
        }

        void SetNested(const NestedClass &nested) {
            this->nested = nested;
        }

        NestedClass *GetNestedPtr() const {
            return nestedPtr;
        }

        void SetNestedPtr(NestedClass *ptr) {
            nestedPtr = ptr;
        }

        const std::vector<NestedClass> &GetNestedList() const {
            return nestedList;
        }

        void SetNestedList(std::vector<NestedClass> &vec) {
            nestedList = vec;
        }

        const std::vector<NestedClass *> &GetNestedPtrList() const {
            return nestedPtrList;
        }

        void SetNestedPtrList(std::vector<NestedClass *> &vec) {
            nestedPtrList = vec;
        }

        REGISTER_SETTER_START
        SETTER(NestedClass2, const NestedClass &, "nested", &NestedClass2::SetNested),
        SETTER(NestedClass2, NestedClass *, "nested_ptr", &NestedClass2::SetNestedPtr),
        SETTER(NestedClass2, std::vector<NestedClass> &, "nested_list", &NestedClass2::SetNestedList),
        SETTER(NestedClass2, std::vector<NestedClass *> &, "nested_ptr_list", &NestedClass2::SetNestedPtrList)
        REGISTER_SETTER_END
    };

    class NestedClass3 {
    private:
        NestedClass2 nested2;
        NestedClass2 *nested2Ptr = nullptr;
    public:
        NestedClass3() = default;

        virtual ~NestedClass3() {
            delete nested2Ptr;
        }

        NestedClass3(const NestedClass3 &obj) {
            this->nested2 = obj.nested2;
            this->nested2Ptr = new NestedClass2(*obj.nested2Ptr);
        }

        NestedClass3(NestedClass3 &&obj) {
            this->nested2 = std::move(obj.nested2);
            this->nested2Ptr = new NestedClass2(std::move(*obj.nested2Ptr));
        }

        NestedClass3 &operator=(const NestedClass3 &obj) {
            this->nested2 = obj.nested2;
            this->nested2Ptr = new NestedClass2(*obj.nested2Ptr);
            return *this;
        }

        NestedClass3 &operator=(NestedClass3 &&obj) {
            this->nested2 = std::move(obj.nested2);
            this->nested2Ptr = new NestedClass2(std::move(*obj.nested2Ptr));
            return *this;
        }

        const NestedClass2 &GetNested() const {
            return nested2;
        }

        void SetNested(NestedClass2 &obj) {
            nested2 = obj;
        }

        const NestedClass2 *GetNestedPtr() const {
            return nested2Ptr;
        }

        void SetNestedPtr(NestedClass2 *ptr) {
            nested2Ptr = ptr;
        }

        REGISTER_SETTER_START
        SETTER(NestedClass3, NestedClass2 &, "nested", &NestedClass3::SetNested),
        SETTER(NestedClass3, NestedClass2*, "nested_ptr", &NestedClass3::SetNestedPtr)
        REGISTER_SETTER_END
    };

    class DeserializeComplexObjectTest1 : public ::testing::Test {
    public:
        void SetUp() override {
        }

        void TearDown() override {
        }
    };

    void CheckDerived2(const DerivedClass2 &derived, const nlohmann::json &object) {
        ASSERT_DOUBLE_EQ(*derived.GetScore(), object["score"].template get<double>());
        ASSERT_DOUBLE_EQ(derived.IsValid(), object["is_valid"].template get<bool>());
        ASSERT_DOUBLE_EQ(*derived.GetId(), object["id"].template get<long>());
        ASSERT_DOUBLE_EQ(0, derived.GetName().compare(object["name"].template get<std::string>()));
        ASSERT_DOUBLE_EQ(derived.GetCode(), object["code"].template get<int>());
        ASSERT_DOUBLE_EQ(*derived.GetAge(), object["age"].template get<int>());
    }

    nlohmann::json GetDerived2() {
        nlohmann::json derived2 = nlohmann::json::object();
        derived2["score"] = (open_json_test::RandomGenerator::GetInstance().GetNextInt() + 0.5);
        derived2["is_valid"] = ((open_json_test::RandomGenerator::GetInstance().GetNextInt() % 2) == 0);
        derived2["id"] = open_json_test::RandomGenerator::GetInstance().GetNextInt();
        derived2["name"] = open_json_test::RandomGenerator::GetInstance().GetNextString(10);
        derived2["code"] = open_json_test::RandomGenerator::GetInstance().GetNextInt();
        derived2["age"] = open_json_test::RandomGenerator::GetInstance().GetNextInt();
        return derived2;
    }

    void CheckNested(const NestedClass &nested, const nlohmann::json &object) {
        CheckDerived2(nested.GetDerived2(), object["derived"]);
        CheckDerived2(*nested.GetDerived2Ptr(), object["derived_ptr"]);
    }

    nlohmann::json GetNested() {
        nlohmann::json nested = nlohmann::json::object();
        nested["derived"] = GetDerived2();
        nested["derived_ptr"] = GetDerived2();
        return nested;
    }

    void CheckNested2(const NestedClass2 &nested, const nlohmann::json &object) {
        CheckNested(nested.GetNested(), object["nested"]);
        CheckNested(*nested.GetNestedPtr(), object["nested_ptr"]);

        ASSERT_EQ(3, nested.GetNestedList().size());
        auto itr = nested.GetNestedList().begin();
        for (auto &arrItem : object["nested_list"]) {
            CheckNested(*itr, arrItem);
            ++itr;
        }

        ASSERT_EQ(3, nested.GetNestedPtrList().size());
        auto itr2 = nested.GetNestedPtrList().begin();
        for (auto &arrItem : object["nested_ptr_list"]) {
            CheckNested(**itr2, arrItem);
            ++itr2;
        }
    }

    nlohmann::json GetNested2() {
        nlohmann::json nested2 = nlohmann::json::object();
        nested2["nested"] = GetNested();
        nested2["nested_ptr"] = GetNested();
        nested2["nested_list"][0] = GetNested();
        nested2["nested_list"][1] = GetNested();
        nested2["nested_list"][2] = GetNested();
        nested2["nested_ptr_list"][0] = GetNested();
        nested2["nested_ptr_list"][1] = GetNested();
        nested2["nested_ptr_list"][2] = GetNested();
        return nested2;
    }

    void CheckNested3(const NestedClass3 &nested, const nlohmann::json &object) {
        CheckNested2(nested.GetNested(), object["nested"]);
        CheckNested2(*nested.GetNestedPtr(), object["nested_ptr"]);
    }

    nlohmann::json GetNested3() {
        nlohmann::json nested3 = nlohmann::json::object();
        nested3["nested"] = GetNested2();
        nested3["nested_ptr"] = GetNested2();
        return nested3;
    }

    TEST_F(DeserializeComplexObjectTest1, ComplexTest) {
        nlohmann::json jsonObject = GetNested3();

        //std::cout << jsonObject.dump(4) << std::endl;
        NestedClass3 nested = open_json::FromJson<NestedClass3>(jsonObject);
        CheckNested3(nested, jsonObject);
    }
}