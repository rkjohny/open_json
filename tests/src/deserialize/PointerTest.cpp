#include <gtest/gtest.h>
#include <string>
#include "../../../include/open_json.h"

namespace open_json_test::deserialize::simple_class {

    class PointerTest {
    private:
        long *id;
        std::string *name;
        double **score;
        int ***age;
        std::vector<int*> *codes;

    public:
        PointerTest() {
            std::cout << "PointerTest()" << std::endl;
        };

        virtual ~PointerTest() {
            std::cout << "~PointerTest() " << id << " " << *id << std::endl;

            delete id;
            delete name;

            delete *score;
            delete score;

            delete **age;
            delete *age;
            delete age;

            for (auto p : *codes) {
                delete p;
            }
            delete codes;
        }

        long* GetId() const {
            return id;
        }

        void SetId(long *n) {
            this->id = const_cast<long*>(n);
        }

        std::string* GetName() const {
            return name;
        }

        void SetName(std::string *s) {
            this->name = const_cast<std::string*>(s);
        }

        double **GetScore() const {
            return score;
        }

        void SetScore(double **s) {
            this->score = const_cast<double **>(s);
        }

        int ***GetAge() const {
            return age;
        }

        void SetAge(int ***a) {
            this->age =  a;
        }

        std::vector<int*>* GetCodes() const {
            return codes;
        }

        void SetCodes(std::vector<int*> *v) {
            codes = v;
        }

        REGISTER_GETTER_START
        GETTER(PointerTest, long*, "id", &PointerTest::GetId),
        GETTER(PointerTest, std::string*, "name", &PointerTest::GetName),
        GETTER(PointerTest, double **, "score", &PointerTest::GetScore),
        GETTER(PointerTest, int***, "age", &PointerTest::GetAge),
        GETTER(PointerTest, std::vector<int*>*, "codes", &PointerTest::GetCodes)
        REGISTER_GETTER_END

        REGISTER_SETTER_START
        SETTER(PointerTest, long*, "id", &PointerTest::SetId),
        SETTER(PointerTest, std::string*, "name", &PointerTest::SetName),
        SETTER(PointerTest, double **, "score", &PointerTest::SetScore),
        SETTER(PointerTest, int***, "age", &PointerTest::SetAge),
        SETTER(PointerTest, std::vector<int*>*, "codes", &PointerTest::SetCodes)
        REGISTER_SETTER_END
    };

    TEST(PointerTest, SerializeTest) {
        PointerTest *p = new PointerTest();
        p->SetId(new long(100));
        p->SetName(new std::string("Rezaul karim"));
        p->SetScore(new double*(new double (100.5)));
        p->SetAge(new int**(new int*(new int(45))));
        p->SetCodes(new std::vector<int*> {new int(10), new int(20), new int(30)});

        nlohmann::json jsonObject = open_json::ToJson(p);
        ASSERT_EQ(*p->GetId(), jsonObject["id"].template get<long>());
        ASSERT_EQ(0, p->GetName()->compare(jsonObject["name"].template get<std::string>()));
        ASSERT_DOUBLE_EQ(**p->GetScore(), jsonObject["score"].template get<double>());
        ASSERT_EQ(***p->GetAge(), jsonObject["age"].template get<int>());
        ASSERT_TRUE(jsonObject["codes"].is_array());
        ASSERT_TRUE(jsonObject["codes"].size() == 3);
        ASSERT_TRUE(jsonObject["codes"][0] == 10);
        ASSERT_TRUE(jsonObject["codes"][1] == 20);
        ASSERT_TRUE(jsonObject["codes"][2] == 30);
        delete p;
    }


    TEST(PointerTest, DeserializeTest) {
        nlohmann::json jsonObject = nlohmann::json::object();
        jsonObject["id"] = 200;
        jsonObject["name"] = "David Jonson";
        jsonObject["score"] = 10.5;
        jsonObject["age"] = 40;
        jsonObject["codes"] = nlohmann::json::array();
        jsonObject["codes"][0] = 100;
        jsonObject["codes"][1] = 200;
        jsonObject["codes"][2] = 300;

        PointerTest a = open_json::FromJson<PointerTest>(jsonObject);
        ASSERT_EQ(jsonObject.at("id").template get<long>(), *a.GetId());
        ASSERT_EQ(0, jsonObject.at("name").template get<std::string>().compare(*a.GetName()));
        ASSERT_DOUBLE_EQ(jsonObject.at("score").template get<double>(), **a.GetScore());
        ASSERT_EQ(jsonObject.at("age").template get<long>(), ***a.GetAge());
        ASSERT_TRUE(a.GetCodes()->size() == 3);
        ASSERT_TRUE(*(*a.GetCodes())[0] == 100);
        ASSERT_TRUE(*(*a.GetCodes())[1] == 200);
        ASSERT_TRUE(*(*a.GetCodes())[2] == 300);

        PointerTest *p = open_json::FromJson<PointerTest*>(jsonObject);
        ASSERT_EQ(jsonObject.at("id").template get<long>(), *p->GetId());
        ASSERT_EQ(0, jsonObject.at("name").template get<std::string>().compare(*p->GetName()));
        ASSERT_DOUBLE_EQ(jsonObject.at("score").template get<double>(), **p->GetScore());
        ASSERT_EQ(jsonObject.at("age").template get<long>(), ***p->GetAge());
        ASSERT_TRUE(*(*p->GetCodes())[0] == 100);
        ASSERT_TRUE(*(*p->GetCodes())[1] == 200);
        ASSERT_TRUE(*(*p->GetCodes())[2] == 300);
        delete p;

        PointerTest **pp = open_json::FromJson<PointerTest**>(jsonObject);
        ASSERT_EQ(jsonObject.at("id").template get<long>(), *(*pp)->GetId());
        ASSERT_EQ(0, jsonObject.at("name").template get<std::string>().compare(*(*pp)->GetName()));
        ASSERT_DOUBLE_EQ(jsonObject.at("score").template get<double>(), **(*pp)->GetScore());
        ASSERT_EQ(jsonObject.at("age").template get<long>(), ***(*pp)->GetAge());
        ASSERT_TRUE(*(*(*pp)->GetCodes())[0] == 100);
        ASSERT_TRUE(*(*(*pp)->GetCodes())[1] == 200);
        ASSERT_TRUE(*(*(*pp)->GetCodes())[2] == 300);
        delete *pp;
        delete pp;
    }
}