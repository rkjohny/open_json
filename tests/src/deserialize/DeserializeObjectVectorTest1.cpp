#include <gtest/gtest.h>
#include "../../../include/open_json.h"


namespace open_json_test::deserialize::vector_of_object::object {

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

    class DeserializeObjectVectorTest1 : public ::testing::Test {
    public:
        DeserializeObjectVectorTest1() = default;

        virtual ~DeserializeObjectVectorTest1() = default;


        void SetUp() override {
        }

        void TearDown() override {
        }

    }; // class DeserializeObjectVectorTest1

    void check(const BaseClass &v, const nlohmann::json &jsonObject) {
        ASSERT_DOUBLE_EQ(v.GetScore(), jsonObject["score"].template get<double>());
        ASSERT_EQ(0, v.GetGrade().compare(jsonObject["grade"].template get<std::string>()));
    }

    TEST_F(DeserializeObjectVectorTest1, VectorObject) {
        nlohmann::json jsonObject = nlohmann::json::array();

        jsonObject[0]["score"] = 90;
        jsonObject[0]["grade"] = "A+";
        jsonObject[1]["score"] = 80;
        jsonObject[1]["grade"] = "A";
        jsonObject[2]["score"] = 70;
        jsonObject[2]["grade"] = "A-";

        std::vector<BaseClass> vec = open_json::FromJson<std::vector<BaseClass>>(jsonObject);

        ASSERT_TRUE(vec.size() == 3);
        auto itr = vec.begin();
        for (auto &obj: jsonObject) {
            check(*itr, obj);
            ++itr;
        }

        std::vector<BaseClass *> vecPtr = open_json::FromJson<std::vector<BaseClass *>>(jsonObject);

        ASSERT_TRUE(vecPtr.size() == 3);
        auto itr2 = vecPtr.begin();
        for (auto &obj: jsonObject) {
            check(*(*itr2), obj);
            ++itr2;
        }

        for (auto p: vecPtr) {
            delete p;
        }

        std::vector<BaseClass **> **vecPtrPtr = open_json::FromJson<std::vector<BaseClass **> **>(jsonObject);

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
