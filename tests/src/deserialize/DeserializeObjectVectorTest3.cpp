#include <gtest/gtest.h>
#include "../../../include/open_json.h"


namespace open_json_test::deserialize::vector_of_object::nested_pointer {

    class BaseClass {
    private:
        double *score;
        std::string *grade;

    public:
        BaseClass() = default;

        virtual ~BaseClass() {
            delete score;
            delete grade;
        }

        BaseClass(BaseClass &&v) {
            this->score = new double(std::move(*v.score));
            this->grade = new std::string(std::move(*v.grade));
        }

        BaseClass(const BaseClass &v) {
            this->score = new double(*v.score);
            this->grade = new std::string(*v.grade);
        }

        BaseClass &operator=(const BaseClass &v) {
            this->score = new double(*v.score);
            this->grade = new std::string(*v.grade);
            return *this;
        }

        BaseClass &operator=(const BaseClass &&v) {
            this->score = new double(std::move(*v.score));
            this->grade = new std::string(std::move(*v.grade));
            return *this;
        }

        void SetScore(double *score) {
            this->score = score;
        }

        void SetGrade(const std::string *grade) {
            this->grade = const_cast<std::string *>(grade);
        }

        double *GetScore() const {
            return score;
        }

        const std::string *GetGrade() const {
            return grade;
        }

        REGISTER_SETTER_START
        SETTER(BaseClass, double*, "score", &BaseClass::SetScore),
        SETTER(BaseClass, const std::string*, "grade", &BaseClass::SetGrade)
        REGISTER_SETTER_END
    };

    class Nested1 {
    private:
        BaseClass *value;

    public:
        Nested1() = default;

        virtual ~Nested1() {
            delete value;
        }

        Nested1(Nested1 &&v) {
            this->value = new BaseClass();
            *this->value = std::move(*v.value);
        }

        Nested1(const Nested1 &v) {
            this->value = new BaseClass();
            *this->value = *v.value;
        }

        Nested1 &operator=(const Nested1 &v) {
            this->value = new BaseClass();
            *this->value = *v.value;
            return *this;
        }

        Nested1 &operator=(const Nested1 &&v) {
            this->value = new BaseClass();
            *this->value = std::move(*v.value);
            return *this;
        }

        BaseClass *GetValue() {
            return value;
        }

        void SetValue(const BaseClass *value) {
            this->value = const_cast<BaseClass *>(value);
        }

        REGISTER_SETTER_START
        SETTER(Nested1, const BaseClass*, "value", &Nested1::SetValue)
        REGISTER_SETTER_END
    };

    class Nested2 {
    private:
        Nested1 *nested;
    public:
        Nested2() = default;

        virtual ~Nested2() {
            delete nested;
        }

        Nested2(Nested2 &&v) {
            this->nested = new Nested1();
            *this->nested = std::move(*v.nested);
        }

        Nested2(const Nested2 &v) {
            this->nested = new Nested1();
            *this->nested = *v.nested;
        }

        Nested2 &operator=(const Nested2 &v) {
            this->nested = new Nested1();
            *this->nested = *v.nested;
            return *this;
        }

        Nested2 &operator=(const Nested2 &&v) {
            this->nested = new Nested1();
            *this->nested = std::move(*v.nested);
            return *this;
        }

        Nested1 *GetNested() {
            return nested;
        }

        void SetNested(Nested1 *nested) {
            this->nested = nested;
        }

        REGISTER_SETTER_START
        SETTER(Nested2, Nested1 *, "nested", &Nested2::SetNested)
        REGISTER_SETTER_END
    };


    class DeserializeObjectVectorTest3 : public ::testing::Test {
    public:
        DeserializeObjectVectorTest3() = default;

        virtual ~DeserializeObjectVectorTest3() = default;


        void SetUp() override {
        }

        void TearDown() override {
        }

    }; // class DeserializeObjectVectorTest3

    void check(Nested2 &v, const nlohmann::json &jsonObject) {
        ASSERT_DOUBLE_EQ(*v.GetNested()->GetValue()->GetScore(),
                         jsonObject["nested"]["value"]["score"].template get<double>());
        ASSERT_EQ(0, v.GetNested()->GetValue()->GetGrade()->compare(
                jsonObject["nested"]["value"]["grade"].template get<std::string>()));
    }

    TEST_F(DeserializeObjectVectorTest3, VectorNestedPointer) {
        nlohmann::json jsonObject = nlohmann::json::array();

        jsonObject[0]["nested"]["value"]["score"] = 90;
        jsonObject[0]["nested"]["value"]["grade"] = "A+";
        jsonObject[1]["nested"]["value"]["score"] = 80;
        jsonObject[1]["nested"]["value"]["grade"] = "A";
        jsonObject[2]["nested"]["value"]["score"] = 70;
        jsonObject[2]["nested"]["value"]["grade"] = "A-";

        std::vector<Nested2> vec = open_json::FromJson<std::vector<Nested2>>(jsonObject);

        ASSERT_TRUE(vec.size() == 3);
        auto itr = vec.begin();
        for (auto &obj: jsonObject) {
            check(*itr, obj);
            ++itr;
        }

        std::vector<Nested2 *> vecPtr = open_json::FromJson<std::vector<Nested2 *>>(jsonObject);

        ASSERT_TRUE(vecPtr.size() == 3);
        auto itr2 = vecPtr.begin();
        for (auto &obj: jsonObject) {
            check(*(*itr2), obj);
            ++itr2;
        }

        for (auto p: vecPtr) {
            delete p;
        }

        std::vector<Nested2 **> **vecPtrPtr = open_json::FromJson<std::vector<Nested2 **> **>(jsonObject);

        ASSERT_TRUE((**vecPtrPtr).size() == 3);
        auto itr3 = (**vecPtrPtr).begin();
        for (auto &obj: jsonObject) {
            check(**(*itr3), obj);
            ++itr3;
        }

        for (auto p: **vecPtrPtr) {
            delete *p;
            delete p;
        }
        delete *vecPtrPtr;
        delete vecPtrPtr;
    }
}
