#include <gtest/gtest.h>
#include "../../../include/open_json.h"


namespace open_json_test::deserialize::vector_of_object::nested {

    class BaseClass {
    private:
        double score;
        std::string grade;

    public:
        BaseClass() = default;

        BaseClass(BaseClass &&v) {
            this->score = std::move(v.score);
            this->grade = std::move(v.grade);
        }

        BaseClass(const BaseClass &v) {
            this->score = v.score;
            this->grade = v.grade;
        }

        BaseClass &operator=(const BaseClass &v) {
            this->score = v.score;
            this->grade = v.grade;
            return *this;
        }

        BaseClass &operator=(const BaseClass &&v) {
            this->score = std::move(v.score);
            this->grade = std::move(v.grade);
            return *this;
        }

        void SetScore(double score) {
            this->score = score;
        }

        void SetGrade(const std::string &grade) {
            this->grade = grade;
        }

        double GetScore() const {
            return score;
        }

        const std::string &GetGrade() const {
            return grade;
        }

        REGISTER_SETTER_START
        SETTER(BaseClass, double, "score", &BaseClass::SetScore),
        SETTER(BaseClass, const std::string&, "grade", &BaseClass::SetGrade)
        REGISTER_SETTER_END
    };

    class Nested1 {
    private:
        BaseClass value;

    public:
        Nested1() = default;

        Nested1(Nested1 &&v) {
            this->value = std::move(v.value);
        }

        Nested1(const Nested1 &v) {
            this->value = v.value;
        }

        Nested1 &operator=(const Nested1 &v) {
            this->value = v.value;
            return *this;
        }

        Nested1 &operator=(const Nested1 &&v) {
            this->value = std::move(v.value);
            return *this;
        }

        BaseClass &GetBaseClass() {
            return value;
        }

        void SetBaseClass(const BaseClass &value) {
            this->value = value;
        }

        REGISTER_SETTER_START
        SETTER(Nested1, const BaseClass&, "value", &Nested1::SetBaseClass)
        REGISTER_SETTER_END
    };

    class Nested2 {
    private:
        Nested1 nested;
    public:
        Nested2() = default;

        Nested2(Nested2 &&v) {
            this->nested = std::move(v.nested);
        }

        Nested2(const Nested2 &v) {
            this->nested = v.nested;
        }

        Nested2 &operator=(const Nested2 &v) {
            this->nested = v.nested;
            return *this;
        }

        Nested2 &operator=(const Nested2 &&v) {
            this->nested = std::move(v.nested);
            return *this;
        }

        Nested1 &GetNested() {
            return nested;
        }

        void SetNested(const Nested1 &nested) {
            this->nested = nested;
        }

        REGISTER_SETTER_START
        SETTER(Nested2, const Nested1 &, "nested", &Nested2::SetNested)
        REGISTER_SETTER_END
    };


    class DeserializeObjectVectorTest2 : public ::testing::Test {
    public:
        DeserializeObjectVectorTest2() = default;

        virtual ~DeserializeObjectVectorTest2() = default;


        void SetUp() override {
        }

        void TearDown() override {
        }

    }; // class DeserializeObjectVectorTest2

    void check(Nested2 &v, const nlohmann::json &jsonObject) {
        ASSERT_DOUBLE_EQ(v.GetNested().GetBaseClass().GetScore(),
                         jsonObject["nested"]["value"]["score"].template get<double>());
        ASSERT_EQ(0, v.GetNested().GetBaseClass().GetGrade().compare(
                jsonObject["nested"]["value"]["grade"].template get<std::string>()));
    }

    TEST_F(DeserializeObjectVectorTest2, VectorNested) {
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
