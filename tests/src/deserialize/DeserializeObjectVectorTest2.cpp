#include <gtest/gtest.h>
#include "../../../include/open_json.h"


namespace open_json_test::deserialize::vector_of_object::nested {

    class Value {
    private:
        double score;
        std::string grade;

    public:
        Value() = default;

        Value(Value &&v) {
            std::cout << "inside move constructor" << std::endl;
            this->score = std::move(v.score);
            this->grade = std::move(v.grade);
        }

        Value(const Value &v) {
            std::cout << "inside copy constructor" << std::endl;
            this->score = v.score;
            this->grade = v.grade;
        }

        void operator=(const Value &v) {
            std::cout << "inside copy assignment" << std::endl;
            this->score = v.score;
            this->grade = v.grade;
        }

        void operator=(const Value &&v) {
            std::cout << "inside move assignment" << std::endl;
            this->score = std::move(v.score);
            this->grade = std::move(v.grade);
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
        SETTER(Value, double, "score", &Value::SetScore),
        SETTER(Value, const std::string&, "grade", &Value::SetGrade)
        REGISTER_SETTER_END
    };

    class Nested1 {
    private:
        Value value;

    public:
        Value& GetValue() {
            return value;
        }
        void SetValue(const Value &value) {
            this->value = value;
        }
        REGISTER_SETTER_START
        SETTER(Nested1, const Value&, "value", &Nested1::SetValue)
        REGISTER_SETTER_END
    };

    class Nested2 {
    private:
        Nested1 nested;
    public:
        Nested1& GetNested() {
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

    void check(Nested2 &v, const nlohmann::json &jsonObject)  {
        ASSERT_DOUBLE_EQ(v.GetNested().GetValue().GetScore(), jsonObject["nested"]["value"]["score"].template get<double>());
        ASSERT_EQ(0, v.GetNested().GetValue().GetGrade().compare(jsonObject["nested"]["value"]["grade"].template get<std::string>()));
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
        for (auto &obj : jsonObject) {
            check(*itr, obj);
            ++itr;
        }

        std::vector<Nested2*> vecPtr = open_json::FromJson<std::vector<Nested2*>>(jsonObject);

        ASSERT_TRUE(vecPtr.size() == 3);
        auto itr2 = vecPtr.begin();
        for (auto &obj : jsonObject) {
            check(*(*itr2), obj);
            ++itr2;
        }

        for (auto p : vecPtr) {
            delete p;
        }

        std::vector<Nested2**> **vecPtrPtr = open_json::FromJson<std::vector<Nested2**>**>(jsonObject);

        ASSERT_TRUE((**vecPtrPtr).size() == 3);
        auto itr3 = (**vecPtrPtr).begin();
        for (auto &obj : jsonObject) {
            check(**(*itr3), obj);
            ++itr3;
        }

        for (auto p : **vecPtrPtr) {
            delete *p;
            delete p;
        }
        delete *vecPtrPtr;
        delete vecPtrPtr;
    }
}
