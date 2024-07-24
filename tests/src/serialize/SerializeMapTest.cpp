#include <gtest/gtest.h>
#include <map>
#include <string>
#include "../../../include/open_json.h"


namespace open_json_test::serialize {

    class Key {

    private:
        int index;
        std::string value;

    public:
        Key(int index, std::string value) : index(index), value(value) {

        }

        Key(const Key &k) {
            this->index = k.index;
            this->value = k.value;
        }

        Key(Key &&k) {
            this->index = std::move(k.index);
            this->value = std::move(k.value);
        }

        void SetIndex(int index) {
            this->index = index;
        }

        void SetValue(std::string value) {
            this->value = value;
        }

        int GetIndex() const {
            return index;
        }

        const std::string &GetValue() const {
            return value;
        }

        bool operator()(const Key &x, const Key &y) const {
            return x.index < y.index;
        };

        void operator=(const Key &k) {
            this->index = k.index;
            this->value = k.value;
        }
    };

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

    class SerializeMapTest : public ::testing::Test {
    public:
        SerializeMapTest() = default;

        virtual ~SerializeMapTest() = default;

        std::map<std::string, int> mapObj;
        std::map<std::string, std::string> *mapPtr;
        std::map<std::string, Value> mapObject;

        // TODO: implement comparison methods in Key to use this map
        std::map<Key, Value> mapToDo;

        void SetUp() override {
            mapObj["first"] = 1;
            mapObj["second"] = 2;
            mapObj["third"] = 3;

            mapPtr = new std::map<std::string, std::string>();
            (*mapPtr)["first"] = "one";
            (*mapPtr)["second"] = "two";
            (*mapPtr)["third"] = "three";

            mapObject.insert(std::pair<std::string, Value>("first", {80, "A+"}));
            mapObject.insert(std::pair<std::string, Value>("second", {70, "A"}));
            mapObject.insert(std::pair<std::string, Value>("third", {60, "A-"}));
        }

        void TearDown() override {

        }
    };

    TEST_F(SerializeMapTest, TestPrimitive) {
        nlohmann::json jsonObject;

        jsonObject = open_json::ToJson(mapObj);
        ASSERT_TRUE(jsonObject.is_object());
        ASSERT_EQ(mapObj.at("first"), jsonObject.at("first").template get<int>());
        ASSERT_EQ(mapObj.at("second"), jsonObject.at("second").template get<int>());
        ASSERT_EQ(mapObj.at("third"), jsonObject.at("third").template get<int>());

        jsonObject = open_json::ToJson(mapPtr);
        ASSERT_EQ(0, mapPtr->at("first").compare(jsonObject.at("first").template get<std::string>()));
        ASSERT_EQ(0, mapPtr->at("second").compare(jsonObject.at("second").template get<std::string>()));
        ASSERT_EQ(0, mapPtr->at("third").compare(jsonObject.at("third").template get<std::string>()));
        delete mapPtr;

        jsonObject = open_json::ToJson(mapObject);
        ASSERT_TRUE(jsonObject.is_object());
        ASSERT_DOUBLE_EQ(mapObject.at("first").GetScore(), jsonObject["first"].at("score").template get<double>());
        ASSERT_EQ(mapObject.at("first").GetGrade(), jsonObject["first"].at("grade").template get<std::string>());

        ASSERT_DOUBLE_EQ(mapObject.at("second").GetScore(), jsonObject["second"].at("score").template get<double>());
        ASSERT_EQ(mapObject.at("second").GetGrade(), jsonObject["second"].at("grade").template get<std::string>());

        ASSERT_DOUBLE_EQ(mapObject.at("third").GetScore(), jsonObject["third"].at("score").template get<double>());
        ASSERT_EQ(mapObject.at("third").GetGrade(), jsonObject["third"].at("grade").template get<std::string>());
    }
}
