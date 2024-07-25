#include <gtest/gtest.h>
#include "../../../include/open_json.h"


namespace open_json_test::serialize::vector_of_object {

    class Value {
    private:
        double score;
        std::string grade;

    public:
        Value() = default;

        Value(double score, std::string grade) : score(score), grade(grade) {
        }

        Value(Value &&v) {
            this->score = std::move(v.score);
            this->grade = std::move(v.grade);
        }

        Value(const Value &v) {
            this->score = v.score;
            this->grade = v.grade;
        }

        void SetScore(double score) {
            this->score = score;
        }

        void setGrade(std::string grade) {
            this->grade = grade;
        }

        double GetScore() const {
            return score;
        }

        const std::string &GetGrade() const {
            return grade;
        }

        void operator=(const Value &v) {
            this->score = v.score;
            this->grade = v.grade;
        }

        void operator=(const Value &&v) {
            this->score = std::move(v.score);
            this->grade = std::move(v.grade);
        }

        REGISTER_GETTER_START
        GETTER(Value, double, "score", &Value::GetScore),
        GETTER(Value, const std::string&, "grade", &Value::GetGrade)
        REGISTER_GETTER_END
    };

    class SerializeObjectVectorTest : public ::testing::Test {
    public:
        SerializeObjectVectorTest() = default;

        virtual ~SerializeObjectVectorTest() = default;

        std::vector<Value> vec;
        std::vector<Value*> vecPtr;
        std::vector<Value**> **vecPtrPtr;

        void SetUp() override {
            vec.push_back({80, "A+"});
            vec.push_back({70, "A-"});
            vec.push_back({60, "A"});

            vecPtr.push_back(new Value{80, "A+"});
            vecPtr.push_back(new Value{70, "A-"});
            vecPtr.push_back(new Value{60, "A"});

            vecPtrPtr = new std::vector<Value **> *;
            *vecPtrPtr = new std::vector<Value**>;

            Value ** v = new Value*;
            *v = new Value{80, "A+"};
            (*vecPtrPtr)->push_back(v);

            v = new Value*;
            *v = new Value{70, "A-"};
            (*vecPtrPtr)->push_back(v);

            v = new Value*;
            *v = new Value{60, "A"};
            (*vecPtrPtr)->push_back(v);
        }

        void TearDown() override {
            for (auto p : vecPtr) {
                delete p;
            }

            for (auto p : **vecPtrPtr) {
                delete *p;
                delete p;
            }
            delete *vecPtrPtr;
            delete vecPtrPtr;
        }

    }; // class SerializeObjectVectorTest

    void check(const Value &v, const nlohmann::json &jsonObject) {
        ASSERT_EQ(v.GetScore(), jsonObject["score"].template get<double>());
        ASSERT_EQ(0, v.GetGrade().compare(jsonObject["grade"].template get<std::string>()));
    }

    TEST_F(SerializeObjectVectorTest, ObjectArray) {
        nlohmann::json jsonObject;

        jsonObject = open_json::ToJson(vec);
        ASSERT_TRUE(jsonObject.is_array());
        auto itr = vec.begin();
        for (auto &obj : jsonObject) {
            check(*itr, obj);
            ++itr;
        }

        jsonObject = open_json::ToJson(vecPtr);
        ASSERT_TRUE(jsonObject.is_array());
        auto itr2 = vecPtr.begin();
        for (auto &obj : jsonObject) {
            check(**itr2, obj);
            ++itr2;
        }

        jsonObject = open_json::ToJson(vecPtrPtr);
        ASSERT_TRUE(jsonObject.is_array());
        auto itr3 = (**vecPtrPtr).begin();
        for (auto &obj : jsonObject) {
            check(***itr3, obj);
            ++itr3;
        }
    }
}
