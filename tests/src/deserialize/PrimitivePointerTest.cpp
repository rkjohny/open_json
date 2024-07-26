#include <gtest/gtest.h>
#include <string>
#include "../../../include/open_json.h"

namespace open_json_test::deserialize::primitive_pointer {

    class PrimitivePointerTest {
    private:
        long *id;
        std::string *name;
        double **score;
        int ***age;
        std::vector<int*> *codes;
        std::vector<std::string*> *members;
        std::vector<std::string**> **subjects;


    public:
        PrimitivePointerTest() {
        };

        virtual ~PrimitivePointerTest() {
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

            for (auto p : *members) {
                delete p;
            }
            delete members;

            for (auto p : **subjects) {
                delete *p;
                delete p;
            }
            delete *subjects;
            delete subjects;
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

        std::vector<std::string*>* GetMembers() const {
            return members;
        }

        void SetMembers(std::vector<std::string*> *v) {
            members = v;
        }

        std::vector<std::string**>** GetSubjects() const {
            return subjects;
        }

        void SetSubjects(std::vector<std::string**> **v) {
            subjects = v;
        }

        REGISTER_GETTER_START
        GETTER(PrimitivePointerTest, long*, "id", &PrimitivePointerTest::GetId),
        GETTER(PrimitivePointerTest, std::string*, "name", &PrimitivePointerTest::GetName),
        GETTER(PrimitivePointerTest, double **, "score", &PrimitivePointerTest::GetScore),
        GETTER(PrimitivePointerTest, int***, "age", &PrimitivePointerTest::GetAge),
        GETTER(PrimitivePointerTest, std::vector<int*>*, "codes", &PrimitivePointerTest::GetCodes),
        GETTER(PrimitivePointerTest, std::vector<std::string*>*, "members", &PrimitivePointerTest::GetMembers),
        GETTER(PrimitivePointerTest, std::vector<std::string**>**, "subjects", &PrimitivePointerTest::GetSubjects)
        REGISTER_GETTER_END

        REGISTER_SETTER_START
        SETTER(PrimitivePointerTest, long*, "id", &PrimitivePointerTest::SetId),
        SETTER(PrimitivePointerTest, std::string*, "name", &PrimitivePointerTest::SetName),
        SETTER(PrimitivePointerTest, double **, "score", &PrimitivePointerTest::SetScore),
        SETTER(PrimitivePointerTest, int***, "age", &PrimitivePointerTest::SetAge),
        SETTER(PrimitivePointerTest, std::vector<int*>*, "codes", &PrimitivePointerTest::SetCodes),
        SETTER(PrimitivePointerTest, std::vector<std::string*>*, "members", &PrimitivePointerTest::SetMembers),
        SETTER(PrimitivePointerTest, std::vector<std::string**>**, "subjects", &PrimitivePointerTest::SetSubjects)
        REGISTER_SETTER_END
    };

    TEST(PrimitivePointerTest, SerializeTest) {
        PrimitivePointerTest *p = new PrimitivePointerTest();
        p->SetId(new long(100));
        p->SetName(new std::string("Rezaul karim"));
        p->SetScore(new double*(new double (100.5)));
        p->SetAge(new int**(new int*(new int(45))));

        p->SetCodes(new std::vector<int*> {
            new int(10),
            new int(20),
            new int(30)
        });

        p->SetMembers(new std::vector<std::string*> {
            new std::string("First member"),
            new std::string("Second member"),
            new std::string("Third member")
        });

        p->SetSubjects(new std::vector<std::string**>*(new std::vector<std::string**>{
            new std::string*(new std::string("Physics")),
            new std::string*(new std::string("Math")),
            new std::string*(new std::string("Chemistry"))
        }));


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

        ASSERT_TRUE(jsonObject["members"].is_array());
        ASSERT_TRUE(jsonObject["members"].size() == 3);
        ASSERT_EQ(0, std::string("First member").compare(jsonObject["members"][0].template get<std::string>()));
        ASSERT_EQ(0, std::string("Second member").compare(jsonObject["members"][1].template get<std::string>()));
        ASSERT_EQ(0, std::string("Third member").compare(jsonObject["members"][2].template get<std::string>()));

        ASSERT_TRUE(jsonObject["subjects"].is_array());
        ASSERT_TRUE(jsonObject["subjects"].size() == 3);
        ASSERT_TRUE(jsonObject["subjects"][0].template get<std::string>().compare("Physics") ==0);
        ASSERT_TRUE(jsonObject["subjects"][1].template get<std::string>().compare("Math") ==0);
        ASSERT_TRUE(jsonObject["subjects"][2].template get<std::string>().compare("Chemistry") ==0);
        delete p;
    }


    TEST(PrimitivePointerTest, DeserializeTest) {
        nlohmann::json jsonObject = nlohmann::json::object();
        jsonObject["id"] = 200;
        jsonObject["name"] = "David Jonson";
        jsonObject["score"] = 10.5;
        jsonObject["age"] = 40;

        jsonObject["codes"] = nlohmann::json::array();
        jsonObject["codes"][0] = 100;
        jsonObject["codes"][1] = 200;
        jsonObject["codes"][2] = 300;

        jsonObject["members"] = nlohmann::json::array();
        jsonObject["members"][0] = "First member";
        jsonObject["members"][1] = "Second member";
        jsonObject["members"][2] = "Third member";

        jsonObject["subjects"] = nlohmann::json::array();
        jsonObject["subjects"][0] = "Physics";
        jsonObject["subjects"][1] = "Math";
        jsonObject["subjects"][2] = "Chemistry";


        PrimitivePointerTest a = open_json::FromJson<PrimitivePointerTest>(jsonObject);
        ASSERT_EQ(jsonObject.at("id").template get<long>(), *a.GetId());
        ASSERT_EQ(0, jsonObject.at("name").template get<std::string>().compare(*a.GetName()));
        ASSERT_DOUBLE_EQ(jsonObject.at("score").template get<double>(), **a.GetScore());
        ASSERT_EQ(jsonObject.at("age").template get<long>(), ***a.GetAge());

        ASSERT_TRUE(a.GetCodes()->size() == 3);
        ASSERT_TRUE(*(*a.GetCodes())[0] == 100);
        ASSERT_TRUE(*(*a.GetCodes())[1] == 200);
        ASSERT_TRUE(*(*a.GetCodes())[2] == 300);

        ASSERT_TRUE(a.GetMembers()->size() == 3);
        ASSERT_TRUE((*a.GetMembers())[0]->compare("First member") == 0);
        ASSERT_TRUE((*a.GetMembers())[1]->compare("Second member") == 0);
        ASSERT_TRUE((*a.GetMembers())[2]->compare("Third member") == 0);

        ASSERT_TRUE((**a.GetSubjects()).size() == 3);
        ASSERT_TRUE((**(**a.GetSubjects())[0]).compare("Physics")  == 0);
        ASSERT_TRUE((**(**a.GetSubjects())[1]).compare("Math")  == 0);
        ASSERT_TRUE((**(**a.GetSubjects())[2]).compare("Chemistry")  == 0);

        PrimitivePointerTest *p = open_json::FromJson<PrimitivePointerTest*>(jsonObject);
        ASSERT_EQ(jsonObject.at("id").template get<long>(), *p->GetId());
        ASSERT_EQ(0, jsonObject.at("name").template get<std::string>().compare(*p->GetName()));
        ASSERT_DOUBLE_EQ(jsonObject.at("score").template get<double>(), **p->GetScore());
        ASSERT_EQ(jsonObject.at("age").template get<long>(), ***p->GetAge());

        ASSERT_TRUE((*p->GetCodes()).size() == 3);
        ASSERT_TRUE(*(*p->GetCodes())[0] == 100);
        ASSERT_TRUE(*(*p->GetCodes())[1] == 200);
        ASSERT_TRUE(*(*p->GetCodes())[2] == 300);

        ASSERT_TRUE((*p->GetMembers()).size() == 3);
        ASSERT_TRUE((*p->GetMembers())[0]->compare("First member") == 0);
        ASSERT_TRUE((*p->GetMembers())[1]->compare("Second member") == 0);
        ASSERT_TRUE((*p->GetMembers())[2]->compare("Third member") == 0);

        ASSERT_TRUE((**p->GetSubjects()).size() == 3);
        ASSERT_TRUE((**(**p->GetSubjects())[0]).compare("Physics") == 0);
        ASSERT_TRUE((**(**p->GetSubjects())[1]).compare("Math") == 0);
        ASSERT_TRUE((**(**p->GetSubjects())[2]).compare("Chemistry") == 0);
        delete p;

        PrimitivePointerTest **pp = open_json::FromJson<PrimitivePointerTest**>(jsonObject);
        ASSERT_EQ(jsonObject.at("id").template get<long>(), *(*pp)->GetId());
        ASSERT_EQ(0, jsonObject.at("name").template get<std::string>().compare(*(*pp)->GetName()));
        ASSERT_DOUBLE_EQ(jsonObject.at("score").template get<double>(), **(*pp)->GetScore());
        ASSERT_EQ(jsonObject.at("age").template get<long>(), ***(*pp)->GetAge());

        ASSERT_TRUE((*pp)->GetCodes()->size() == 3);
        ASSERT_TRUE(*(*(*pp)->GetCodes())[0] == 100);
        ASSERT_TRUE(*(*(*pp)->GetCodes())[1] == 200);
        ASSERT_TRUE(*(*(*pp)->GetCodes())[2] == 300);

        ASSERT_TRUE((*pp)->GetMembers()->size() == 3);
        ASSERT_TRUE( (*(*(*pp)->GetMembers())[0]).compare("First member") == 0);
        ASSERT_TRUE( (*(*(*pp)->GetMembers())[1]).compare("Second member") == 0);
        ASSERT_TRUE( (*(*(*pp)->GetMembers())[2]).compare("Third member") == 0);

        ASSERT_TRUE((**(*pp)->GetSubjects()).size() == 3);
        ASSERT_TRUE((**(**(*pp)->GetSubjects())[0]).compare("Physics") == 0);
        ASSERT_TRUE((**(**(*pp)->GetSubjects())[1]).compare("Math") == 0);
        ASSERT_TRUE((**(**(*pp)->GetSubjects())[2]).compare("Chemistry") == 0);
        delete *pp;
        delete pp;
    }
}