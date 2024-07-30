#include <gtest/gtest.h>
#include <nlohmann/json.hpp>
#include <string>
#include "../../../include/open_json.h"


namespace open_json_test::deserialize::derived_class {

    class BaseClass {
    private:
        double score;
        bool is_valid;

    public:
        BaseClass() : score{24.5678}, is_valid{false} {
        }

        virtual ~BaseClass() = default;

        BaseClass(BaseClass &&v) {
            this->score = std::move(v.score);
            this->is_valid = std::move(v.is_valid);
        }

        BaseClass(const BaseClass &v) {
            this->score = v.score;
            this->is_valid = v.is_valid;
        }

        BaseClass &operator=(const BaseClass &v) {
            this->score = v.score;
            this->is_valid = v.is_valid;
            return *this;
        }

        BaseClass &operator=(const BaseClass &&v) {
            this->score = std::move(v.score);
            this->is_valid = std::move(v.is_valid);
            return *this;
        }


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

    class DeserializeDerivedClassTest : public ::testing::Test {
    public:
        void SetUp() override {
        }

        void TearDown() override {
        }
    };


    TEST_F(DeserializeDerivedClassTest, BaseTest) {
        BaseClass base;

        base.SetScore(45.12);
        base.SetValid(true);

        nlohmann::json jsonObject = open_json::ToJson(base);

        ASSERT_TRUE(jsonObject.is_object());
        ASSERT_DOUBLE_EQ(base.GetScore(), jsonObject.at("score").template get<double>());
        ASSERT_TRUE(base.IsValid() == jsonObject.at("is_valid").template get<bool>());

        base.Clear();
        base = open_json::FromJson<BaseClass>(jsonObject);

        ASSERT_DOUBLE_EQ(base.GetScore(), jsonObject.at("score").template get<double>());
        ASSERT_TRUE(base.IsValid() == jsonObject.at("is_valid").template get<bool>());
    }

    TEST_F(DeserializeDerivedClassTest, BasePointerTest) {
        BaseClass *base = new BaseClass();

        base->SetScore(45.12);
        base->SetValid(true);

        nlohmann::json jsonObject = open_json::ToJson(base);

        ASSERT_TRUE(jsonObject.is_object());
        ASSERT_DOUBLE_EQ(base->GetScore(), jsonObject.at("score").template get<double>());
        ASSERT_TRUE(base->IsValid() == jsonObject.at("is_valid").template get<bool>());

        base->Clear();
        delete base;

        base = open_json::FromJson<BaseClass *>(jsonObject);

        ASSERT_DOUBLE_EQ(base->GetScore(), jsonObject.at("score").template get<double>());
        ASSERT_TRUE(base->IsValid() == jsonObject.at("is_valid").template get<bool>());
        delete base;
    }

    TEST_F(DeserializeDerivedClassTest, Drived1Test) {
        DerivedClass1 derived1 = DerivedClass1();

        derived1.SetName("abc xyz");
        derived1.SetId(452);
        derived1.SetValid(true);
        derived1.SetScore(89.15);

        nlohmann::json jsonObject = open_json::ToJson(derived1);

        ASSERT_TRUE(jsonObject.is_object());
        ASSERT_DOUBLE_EQ(derived1.GetId(), jsonObject.at("id").template get<long>());
        ASSERT_TRUE(0 == jsonObject.at("name").template get<std::string>().compare(derived1.GetName()));
        ASSERT_DOUBLE_EQ(derived1.GetScore(), jsonObject.at("score").template get<double>());
        ASSERT_TRUE(derived1.IsValid() == jsonObject.at("is_valid").template get<bool>());

        derived1.Clear();
        derived1 = open_json::FromJson<DerivedClass1>(jsonObject);

        ASSERT_DOUBLE_EQ(derived1.GetId(), jsonObject.at("id").template get<long>());
        ASSERT_TRUE(0 == jsonObject.at("name").template get<std::string>().compare(derived1.GetName()));
        ASSERT_DOUBLE_EQ(derived1.GetScore(), jsonObject.at("score").template get<double>());
        ASSERT_TRUE(derived1.IsValid() == jsonObject.at("is_valid").template get<bool>());
    }

    TEST_F(DeserializeDerivedClassTest, Drived1PoinetTest) {
        DerivedClass1 *derived1 = new DerivedClass1();

        derived1->SetName("abc xyz");
        derived1->SetId(452);
        derived1->SetValid(true);
        derived1->SetScore(89.15);

        nlohmann::json jsonObject = open_json::ToJson(derived1);

        ASSERT_TRUE(jsonObject.is_object());
        ASSERT_DOUBLE_EQ(derived1->GetId(), jsonObject.at("id").template get<long>());
        ASSERT_TRUE(0 == jsonObject.at("name").template get<std::string>().compare(derived1->GetName()));
        ASSERT_DOUBLE_EQ(derived1->GetScore(), jsonObject.at("score").template get<double>());
        ASSERT_TRUE(derived1->IsValid() == jsonObject.at("is_valid").template get<bool>());

        derived1->Clear();
        delete derived1;

        derived1 = open_json::FromJson<DerivedClass1 *>(jsonObject);

        ASSERT_DOUBLE_EQ(derived1->GetId(), jsonObject.at("id").template get<long>());
        ASSERT_TRUE(0 == jsonObject.at("name").template get<std::string>().compare(derived1->GetName()));
        ASSERT_DOUBLE_EQ(derived1->GetScore(), jsonObject.at("score").template get<double>());
        ASSERT_TRUE(derived1->IsValid() == jsonObject.at("is_valid").template get<bool>());
        delete derived1;
    }

    TEST_F(DeserializeDerivedClassTest, Drived2test) {
        DerivedClass2 derived2 = DerivedClass2();

        derived2.SetName("abc xyz");
        derived2.SetId(452);
        derived2.SetValid(true);
        derived2.SetScore(89.15);
        derived2.SetCode(893);

        nlohmann::json jsonObject = open_json::ToJson(derived2);

        ASSERT_TRUE(jsonObject.is_object());
        ASSERT_EQ(derived2.GetCode(), jsonObject.at("code").template get<int>());
        ASSERT_DOUBLE_EQ(derived2.GetId(), jsonObject.at("id").template get<long>());
        ASSERT_TRUE(0 == jsonObject.at("name").template get<std::string>().compare(derived2.GetName()));
        ASSERT_DOUBLE_EQ(derived2.GetScore(), jsonObject.at("score").template get<double>());
        ASSERT_TRUE(derived2.IsValid() == jsonObject.at("is_valid").template get<bool>());

        derived2.Clear();
        derived2 = open_json::FromJson<DerivedClass2>(jsonObject);

        ASSERT_EQ(derived2.GetCode(), jsonObject.at("code").template get<int>());
        ASSERT_DOUBLE_EQ(derived2.GetId(), jsonObject.at("id").template get<long>());
        ASSERT_TRUE(0 == jsonObject.at("name").template get<std::string>().compare(derived2.GetName()));
        ASSERT_DOUBLE_EQ(derived2.GetScore(), jsonObject.at("score").template get<double>());
        ASSERT_TRUE(derived2.IsValid() == jsonObject.at("is_valid").template get<bool>());
    }

    TEST_F(DeserializeDerivedClassTest, Drived2PtrTest) {
        DerivedClass2 *derived2 = new DerivedClass2();

        derived2->SetName("abc xyz");
        derived2->SetId(452);
        derived2->SetValid(true);
        derived2->SetScore(89.15);
        derived2->SetCode(893);

        nlohmann::json jsonObject = open_json::ToJson(derived2);

        ASSERT_TRUE(jsonObject.is_object());
        ASSERT_EQ(derived2->GetCode(), jsonObject.at("code").template get<int>());
        ASSERT_DOUBLE_EQ(derived2->GetId(), jsonObject.at("id").template get<long>());
        ASSERT_TRUE(0 == jsonObject.at("name").template get<std::string>().compare(derived2->GetName()));
        ASSERT_DOUBLE_EQ(derived2->GetScore(), jsonObject.at("score").template get<double>());
        ASSERT_TRUE(derived2->IsValid() == jsonObject.at("is_valid").template get<bool>());

        derived2->Clear();
        delete derived2;

        derived2 = open_json::FromJson<DerivedClass2 *>(jsonObject);

        ASSERT_EQ(derived2->GetCode(), jsonObject.at("code").template get<int>());
        ASSERT_DOUBLE_EQ(derived2->GetId(), jsonObject.at("id").template get<long>());
        ASSERT_TRUE(0 == jsonObject.at("name").template get<std::string>().compare(derived2->GetName()));
        ASSERT_DOUBLE_EQ(derived2->GetScore(), jsonObject.at("score").template get<double>());
        ASSERT_TRUE(derived2->IsValid() == jsonObject.at("is_valid").template get<bool>());
        delete derived2;
    }
}