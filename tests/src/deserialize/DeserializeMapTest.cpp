#include <gtest/gtest.h>
#include <map>
#include <string>
#include "../../../include/open_json.h"


namespace open_json_test::deserialize::map_test {

    class KeyComparator;

    class Key {
        friend class KeyComparator;

    private:
        int index;
        std::string value;

    public:
        Key() = default;

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

        void SetValue(const std::string &value) {
            this->value = value;
        }

        int GetIndex() const {
            return index;
        }

        const std::string &GetValue() const {
            return value;
        }

        bool operator<(const Key &other) const {
            return this->index < other.index;
        };

        Key &operator=(const Key &&k) {
            this->index = std::move(k.index);
            this->value = std::move(k.value);
            return *this;
        }

        Key &operator=(const Key &k) {
            this->index = k.index;
            this->value = k.value;
            return *this;
        }

        REGISTER_SETTER_START
        SETTER(Key, int, "id", &Key::SetIndex),
        SETTER(Key, const std::string&, "name", &Key::SetValue)
        REGISTER_SETTER_END
    };

    class KeyComparator {
    public:
        bool operator()(const Key &first, const Key &second) const {
            return first.index < second.index;
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

        void SetGrade(std::string grade) {
            this->grade = grade;
        }

        double GetScore() const {
            return score;
        }

        const std::string &GetGrade() const {
            return grade;
        }

        Value &operator=(const Value &v) {
            this->score = v.score;
            this->grade = v.grade;
            return *this;
        }

        Value &operator=(Value &&v) {
            this->score = std::move(v.score);
            this->grade = std::move(v.grade);
            return *this;
        }

        REGISTER_SETTER_START
        SETTER(Value, double, "score", &Value::SetScore),
        SETTER(Value, std::string, "grade", &Value::SetGrade)
        REGISTER_SETTER_END
    };

    class DeserializeMapTest : public ::testing::Test {
    public:
        DeserializeMapTest() = default;

        // TODO: both key and value are object type
        std::map<Key, Value> mapKeyValue;

        virtual ~DeserializeMapTest() {
        };

        void SetUp() override {
        }

        void TearDown() override {

        }
    };

    TEST_F(DeserializeMapTest, TestMap1) {
        nlohmann::json jsonObject;

        jsonObject["first"]["score"] = 90;
        jsonObject["first"]["grade"] = "A+";

        jsonObject["second"]["score"] = 80;
        jsonObject["second"]["grade"] = "A-";

        jsonObject["third"]["score"] = 90;
        jsonObject["third"]["grade"] = "A";

        std::map<std::string, Value> mapObject = open_json::FromJson<std::map<std::string, Value>>(jsonObject);

        ASSERT_DOUBLE_EQ(mapObject.at("first").GetScore(), jsonObject["first"].at("score").template get<double>());
        ASSERT_EQ(mapObject.at("first").GetGrade(), jsonObject["first"].at("grade").template get<std::string>());

        ASSERT_DOUBLE_EQ(mapObject.at("second").GetScore(), jsonObject["second"].at("score").template get<double>());
        ASSERT_EQ(mapObject.at("second").GetGrade(), jsonObject["second"].at("grade").template get<std::string>());

        ASSERT_DOUBLE_EQ(mapObject.at("third").GetScore(), jsonObject["third"].at("score").template get<double>());
        ASSERT_EQ(mapObject.at("third").GetGrade(), jsonObject["third"].at("grade").template get<std::string>());
    }
}
