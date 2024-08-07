#include <iostream>

#include <gtest/gtest.h>
#include <vector>
#include <string>
#include <tuple>
#include "../../../include/open_json.h"


namespace open_json_test::serialize::custom_object {


    class SimpleClass {
    private:
        long m_id;
        std::string m_name;
        std::string *m_address;
        int *m_age;
        double m_score;
        bool m_isValid;

        std::vector<int> m_vecInt;
        std::vector<std::string> m_vecString;
        std::vector<std::string *> *m_vecStringPtr;
        std::vector<double> *m_vecDouble;
        std::vector<long *> m_vecLong;

    public:

        SimpleClass() {
            m_id = 10;
            m_name = "rezaul";
            m_address = new std::string("Dhaka, Bangladesh");
            m_age = new int(43);
            m_score = 15.3;
            m_isValid = true;

            m_vecInt.push_back(10);
            m_vecInt.push_back(11);
            m_vecInt.push_back(12);

            m_vecString.push_back("first string");
            m_vecString.push_back("second string");
            m_vecString.push_back("third string");

            m_vecStringPtr = new std::vector<std::string *>();
            m_vecStringPtr->push_back(new std::string("first string pointer"));
            m_vecStringPtr->push_back(new std::string("second string pointer"));
            m_vecStringPtr->push_back(new std::string("third string pointer"));

            m_vecDouble = new std::vector<double>();
            m_vecDouble->push_back(20.50);
            m_vecDouble->push_back(20.51);
            m_vecDouble->push_back(20.52);

            m_vecLong.push_back(new long(20L));
            m_vecLong.push_back(new long(21L));
            m_vecLong.push_back(new long(22L));
        }

        virtual ~SimpleClass() {
            delete m_address;
            delete m_age;

            for (auto &p: *m_vecStringPtr) {
                delete p;
            }
            delete m_vecStringPtr;

            delete m_vecDouble;

            for (auto &p: m_vecLong) {
                delete p;
            }
        }

        long GetId() const {
            return m_id;
        }

        const std::string &GetName() const {
            return m_name;
        }

        const std::string *GetAddress() const {
            return m_address;
        }

        const int *GetAge() const {
            return m_age;
        }

        double GetScore() const {
            return m_score;
        }

        bool IsValid() const {
            return m_isValid;
        }

        const std::vector<int> &GetVecInt() const {
            return m_vecInt;
        }

        const std::vector<std::string> &GetVecString() const {
            return m_vecString;
        }

        const std::vector<std::string *> *GetVecStringPtr() const {
            return m_vecStringPtr;
        }

        const std::vector<double> *GetVecDouble() const {
            return m_vecDouble;
        }


        const std::vector<long *> &GetVecLong() const {
            return m_vecLong;
        }

        static constexpr auto getters = std::make_tuple(
                open_json::Getter<SimpleClass, long>(&SimpleClass::GetId, "id"),
                open_json::Getter<SimpleClass, const std::string &>(&SimpleClass::GetName, "name"),
                open_json::Getter<SimpleClass, const std::string *>(&SimpleClass::GetAddress, "address"),
                open_json::Getter<SimpleClass, const int *>(&SimpleClass::GetAge, "age"),
                open_json::Getter<SimpleClass, double>(&SimpleClass::GetScore, "score"),
                open_json::Getter<SimpleClass, bool>(&SimpleClass::IsValid, "is_valid"),
                open_json::Getter<SimpleClass, const std::vector<int> &>(&SimpleClass::GetVecInt, "int_vector"),
                open_json::Getter<SimpleClass, const std::vector<std::string> &>(&SimpleClass::GetVecString,
                                                                                 "str_vector"),
                open_json::Getter<SimpleClass, const std::vector<std::string *> *>(&SimpleClass::GetVecStringPtr,
                                                                                   "str_ptr_vector"),
                open_json::Getter<SimpleClass, const std::vector<double> *>(&SimpleClass::GetVecDouble,
                                                                            "double_vector"),
                open_json::Getter<SimpleClass, const std::vector<long *> &>(&SimpleClass::GetVecLong, "long_vector")
        );
    };

    class SerializeCustomObjectTest : public ::testing::Test {
    public:
        SerializeCustomObjectTest() = default;

        ~SerializeCustomObjectTest() = default;

        void SetUp() override {
        }

        void TearDown() override {
        }

        static void Validate(nlohmann::json &jsonObject, SimpleClass &obj) {
            nlohmann::json jsonObjectArr;

            ASSERT_TRUE(jsonObject.is_object());
            ASSERT_TRUE(jsonObject.at("id").is_number());
            ASSERT_TRUE(jsonObject.at("id").is_number_integer());
            ASSERT_TRUE(jsonObject.at("id").template get<long>() == obj.GetId());

            ASSERT_TRUE(jsonObject.at("name").template get<std::string>().compare(obj.GetName()) == 0);
            ASSERT_TRUE(jsonObject.at("address").template get<std::string>().compare(*obj.GetAddress()) == 0);
            ASSERT_TRUE(jsonObject.at("age").template get<int>() == *obj.GetAge());
            ASSERT_DOUBLE_EQ(jsonObject.at("score").template get<double>(), obj.GetScore());
            ASSERT_TRUE(jsonObject.at("is_valid").template get<bool>() == obj.IsValid());

            jsonObjectArr = jsonObject.at("int_vector");
            ASSERT_TRUE(jsonObjectArr.is_array());
            ASSERT_TRUE(jsonObjectArr.size() == obj.GetVecInt().size());
            auto itrIntVec = obj.GetVecInt().begin();
            for (auto &arrItem: jsonObjectArr) {
                ASSERT_EQ(arrItem.template get<int>(), *itrIntVec);
                ++itrIntVec;
            }

            jsonObjectArr = jsonObject.at("str_vector");
            ASSERT_TRUE(jsonObjectArr.is_array());
            ASSERT_TRUE(jsonObjectArr.size() == obj.GetVecString().size());
            auto itrStrVec = obj.GetVecString().begin();
            for (auto &arrItem: jsonObjectArr) {
                ASSERT_EQ(arrItem.template get<std::string>().compare(*itrStrVec), 0);
                ++itrStrVec;
            }

            jsonObjectArr = jsonObject.at("str_ptr_vector");
            ASSERT_TRUE(jsonObjectArr.is_array());
            ASSERT_TRUE(jsonObjectArr.size() == obj.GetVecStringPtr()->size());
            auto itrStrVecPtr = obj.GetVecStringPtr()->begin();
            for (auto &arrItem: jsonObjectArr) {
                ASSERT_EQ(arrItem.template get<std::string>().compare(**itrStrVecPtr), 0);
                ++itrStrVecPtr;
            }

            jsonObjectArr = jsonObject.at("double_vector");
            ASSERT_TRUE(jsonObjectArr.is_array());
            ASSERT_TRUE(jsonObjectArr.size() == obj.GetVecDouble()->size());
            auto itrDoubleVec = obj.GetVecDouble()->begin();
            for (auto &arrItem: jsonObjectArr) {
                ASSERT_DOUBLE_EQ(arrItem.template get<double>(), *itrDoubleVec);
                ++itrDoubleVec;
            }

            jsonObjectArr = jsonObject.at("long_vector");
            ASSERT_TRUE(jsonObjectArr.is_array());
            ASSERT_TRUE(jsonObjectArr.size() == obj.GetVecLong().size());
            auto itrLongVec = obj.GetVecLong().begin();
            for (auto &arrItem: jsonObjectArr) {
                ASSERT_EQ(arrItem.template get<long>(), **itrLongVec);
                ++itrLongVec;
            }
        }
    };

    TEST_F(SerializeCustomObjectTest, SimpleClassTest) {
        SimpleClass obj;
        nlohmann::json jsonObject;

        jsonObject = open_json::ToJson(SimpleClass());
        Validate(jsonObject, obj);


        jsonObject = open_json::ToJson(std::move(obj));
        Validate(jsonObject, obj);

        jsonObject = open_json::ToJson(obj);
        Validate(jsonObject, obj);

        jsonObject = open_json::ToJson(&obj);
        Validate(jsonObject, obj);
    }
}
