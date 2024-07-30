#include <gtest/gtest.h>
#include "../../../include/open_json.h"


namespace open_json_test::deserialize::vector_of_object::nested_pointer {

    class Value {
    private:
        double *score;
        std::string *grade;

    public:
        Value() = default;

        virtual ~Value() {
            std::cout << "Inside ~Value()" << std::endl;
            delete score;
            delete grade;
        }

        Value(Value &&v) {
            std::cout << "inside move constructor Value" << std::endl;
            this->score = new double(*v.score);
            this->grade = new std::string(*v.grade);
        }

        Value(const Value &v) {
            std::cout << "inside copy constructor Value" << std::endl;
            this->score = new double(*v.score);
            this->grade = new std::string(*v.grade);
        }

        void operator=(const Value &v) {
            std::cout << "inside copy assignment Value" << std::endl;
            this->score = new double(*v.score);
            this->grade = new std::string(*v.grade);
        }

        void operator=(const Value &&v) {
            std::cout << "inside move assignment Value" << std::endl;
            this->score = new double(*v.score);
            this->grade = new std::string(*v.grade);
        }

        void SetScore(double *score) {
            this->score = score;
        }

        void SetGrade(const std::string *grade) {
            this->grade = const_cast<std::string*>(grade);
        }

        double* GetScore() const {
            return score;
        }

        const std::string *GetGrade() const {
            return grade;
        }

        REGISTER_SETTER_START
        SETTER(Value, double*, "score", &Value::SetScore),
        SETTER(Value, const std::string*, "grade", &Value::SetGrade)
        REGISTER_SETTER_END
    };

    class Nested1 {
    private:
        Value *value;

    public:
        Nested1() = default;

        virtual ~Nested1() {
            std::cout << "Inside ~Nested1() Nested1" << std::endl;
            delete value;
        }

        Nested1(Nested1 &&v) {
            std::cout << "inside move constructor Nested1" << std::endl;
            this->value = new Value();
            *this->value = *v.value;
        }

        Nested1(const Nested1 &v) {
            std::cout << "inside copy constructor Nested1" << std::endl;
            this->value = new Value();
            *this->value = *v.value;
        }

        void operator=(const Nested1 &v) {
            std::cout << "inside copy assignment Nested1" << std::endl;
            this->value = new Value();
            *this->value = *v.value;
        }

        void operator=(const Nested1 &&v) {
            std::cout << "inside move assignment Nested1" << std::endl;
            this->value = new Value();
            *this->value = *v.value;
        }

        Value* GetValue() {
            return value;
        }
        void SetValue(const Value *value) {
            this->value = const_cast<Value*>(value);
        }
        REGISTER_SETTER_START
        SETTER(Nested1, const Value*, "value", &Nested1::SetValue)
        REGISTER_SETTER_END
    };

    class Nested2 {
    private:
        Nested1 *nested;
    public:
        Nested2() = default;

        virtual ~Nested2() {
            std::cout << "Inside ~Nested2()" << std::endl;
            delete nested;
        }

        Nested2(Nested2 &&v) {
            std::cout << "inside move constructor Nested2" << std::endl;
            this->nested = new Nested1();
            *this->nested = *v.nested;
        }

        Nested2(const Nested2 &v) {
            std::cout << "inside copy constructor Nested2" << std::endl;
            this->nested = new Nested1();
            *this->nested = *v.nested;
        }

        void operator=(const Nested2 &v) {
            std::cout << "inside copy assignment Nested2" << std::endl;
            this->nested = new Nested1();
            *this->nested = *v.nested;
        }

        void operator=(const Nested2 &&v) {
            std::cout << "inside move assignment Nested2" << std::endl;
            this->nested = new Nested1();
            *this->nested = *v.nested;
        }
        Nested1* GetNested() {
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

    void check(Nested2 &v, const nlohmann::json &jsonObject)  {
        ASSERT_DOUBLE_EQ(*v.GetNested()->GetValue()->GetScore(), jsonObject["nested"]["value"]["score"].template get<double>());
        ASSERT_EQ(0, v.GetNested()->GetValue()->GetGrade()->compare(jsonObject["nested"]["value"]["grade"].template get<std::string>()));
    }

    TEST_F(DeserializeObjectVectorTest3, VectorNestedPointer) {
        nlohmann::json jsonObject = nlohmann::json::array();

        jsonObject[0]["nested"]["value"]["score"] = 90;
        jsonObject[0]["nested"]["value"]["grade"] = "A+";
        jsonObject[1]["nested"]["value"]["score"] = 80;
        jsonObject[1]["nested"]["value"]["grade"] = "A";
        jsonObject[2]["nested"]["value"]["score"] = 70;
        jsonObject[2]["nested"]["value"]["grade"] = "A-";

        std::cout << jsonObject.dump() << std::endl;

        //std::cout << "Going to call deserialize" << std::endl;
        std::vector<Nested2> vec = open_json::FromJson<std::vector<Nested2>>(jsonObject);
        //std::cout << "After call deserialize" << std::endl;

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
