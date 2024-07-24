#include <gtest/gtest.h>
#include "../../../include/open_json.h"


namespace open_json_test::serialize {

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

        REGISTER_GETTER_START
        GETTER(Value, double, "score", &Value::GetScore),
        GETTER(Value, const std::string&, "grade", &Value::GetGrade)
        REGISTER_GETTER_END
    };

    class SerializeObjectArrayTest : public ::testing::Test {
    public:
        SerializeObjectArrayTest() = default;

        virtual ~SerializeObjectArrayTest() = default;


        void SetUp() override {
        }

        void TearDown() override {
        }

    }; // class SerializeObjectArrayTest

    TEST_F(SerializeObjectArrayTest, ObjectArray) {
        nlohmann::json jsonObject;

        Value valueArr[3] = {{80, "A+"},
                             {70, "A"},
                             {60, "A-"}};

        jsonObject = open_json::ToJson(valueArr, 3);
        ASSERT_TRUE(jsonObject.is_array());
        ASSERT_TRUE(jsonObject.size() == 3);

        int i = 0;
        for (auto &arrItem: jsonObject) {
            ASSERT_DOUBLE_EQ(valueArr[i].GetScore(), arrItem.at("score").template get<double>());
            ASSERT_EQ(0, valueArr[i].GetGrade().compare(arrItem.at("grade").template get<std::string>()));
            ++i;
        }

        Value *ptrArr1 = new Value[]{{80, "A+"},
                                     {70, "A"},
                                     {60, "A-"}};

        jsonObject = open_json::ToJson(ptrArr1, 3);
        ASSERT_TRUE(jsonObject.is_array());
        ASSERT_TRUE(jsonObject.size() == 3);
        i = 0;
        for (auto &arrItem: jsonObject) {
            ASSERT_DOUBLE_EQ(ptrArr1[i].GetScore(), arrItem.at("score").template get<double>());
            ASSERT_EQ(0, ptrArr1[i].GetGrade().compare(arrItem.at("grade").template get<std::string>()));
            ++i;
        }
        delete[] ptrArr1;

        Value **ptrArr2 = new Value *[]{new Value(80, "A+"), new Value(70, "A"), new Value(60, "A-")};
        jsonObject = open_json::ToJson(ptrArr2, 3);
        ASSERT_TRUE(jsonObject.is_array());
        ASSERT_TRUE(jsonObject.size() == 3);
        i = 0;
        for (auto &arrItem: jsonObject) {
            ASSERT_DOUBLE_EQ(ptrArr2[i]->GetScore(), arrItem.at("score").template get<double>());
            ASSERT_EQ(0, ptrArr2[i]->GetGrade().compare(arrItem.at("grade").template get<std::string>()));
            ++i;
        }
        delete[] ptrArr2;

        Value *ptrArr3[3] = {new Value(80, "A+"), new Value(70, "A"), new Value(60, "A-")};
        jsonObject = open_json::ToJson(ptrArr3, 3);
        ASSERT_TRUE(jsonObject.is_array());
        ASSERT_TRUE(jsonObject.size() == 3);
        i = 0;
        for (auto &arrItem: jsonObject) {
            ASSERT_DOUBLE_EQ(ptrArr3[i]->GetScore(), arrItem.at("score").template get<double>());
            ASSERT_EQ(0, ptrArr3[i]->GetGrade().compare(arrItem.at("grade").template get<std::string>()));
            ++i;
        }
        for (auto p: ptrArr3) {
            delete p;
        }
    }
}
