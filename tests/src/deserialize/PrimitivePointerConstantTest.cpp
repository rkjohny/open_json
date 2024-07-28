#include <gtest/gtest.h>
#include <string>
#include "../../include/CommonDef.h"
#include "../../../include/open_json.h"

namespace open_json_test::deserialize::primitive_pointer::constant {

    class PrimitivePointerTest {
    private:
        long *id;
        std::string *name;
        double **score;
        int ***age;
        std::vector<int*> *codes;
        std::vector<std::string*> *members;
        std::vector<std::string**> **subjects;
        std::vector<int***> ***points;
        std::vector<std::string ***> ***cities;

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

            for(auto p : ***points) {
                delete **p;
                delete *p;
                delete p;
            }
            delete **points;
            delete *points;
            delete points;

            for (auto p : ***cities) {
                delete **p;
                delete *p;
                delete p;
            }
        }

        const long* GetId() const {
            return id;
        }

        void SetId(const long *n) {
            this->id = const_cast<long*>(n);
        }

        const std::string* GetName() const {
            return name;
        }

        void SetName(const std::string *s) {
            this->name = const_cast<std::string*>(s);
        }

        const double **GetScore() const {
            return const_cast<const double**>(score);
        }

        void SetScore(const double **s) {
            this->score = const_cast<double **>(s);
        }

        const int ***GetAge() const {
            return const_cast<const int***>(age);
        }

        void SetAge(const int ***a) {
            this->age = const_cast<int ***>(a);
        }

        const std::vector<int*>* GetCodes() const {
            return codes;
        }

        void SetCodes(const std::vector<int*> *v) {
            codes = const_cast<std::vector<int*> *>(v);
        }

        const std::vector<std::string*>* GetMembers() const {
            return members;
        }

        void SetMembers(const std::vector<std::string*> *v) {
            members = const_cast<std::vector<std::string*> *>(v);
        }

        const std::vector<std::string**> ** GetSubjects() const {
            return const_cast<const std::vector<std::string**> **>(subjects);
        }

        void SetSubjects(const std::vector<std::string**> **v) {
            subjects = const_cast<std::vector<std::string**> **>(v);
        }

        const std::vector<int***> *** GetPoints() const {
            return const_cast<const std::vector<int***> ***>(points);
        }

        void SetPoints(const std::vector<int***> ***p) {
            points = const_cast<std::vector<int***> ***>(p);
        }

        const std::vector<std::string ***> ***GetCities() const {
            return const_cast<const std::vector<std::string ***> ***>(cities);
        }

        void SetCities(const std::vector<std::string ***> ***c) {
            cities = const_cast<std::vector<std::string ***> ***>(c);
        }

        REGISTER_GETTER_START
        GETTER(PrimitivePointerTest, const long*, "id", &PrimitivePointerTest::GetId),
        GETTER(PrimitivePointerTest, const std::string*, "name", &PrimitivePointerTest::GetName),
        GETTER(PrimitivePointerTest, const double **, "score", &PrimitivePointerTest::GetScore),
        GETTER(PrimitivePointerTest, const int***, "age", &PrimitivePointerTest::GetAge),
        GETTER(PrimitivePointerTest, const std::vector<int*>*, "codes", &PrimitivePointerTest::GetCodes),
        GETTER(PrimitivePointerTest, const std::vector<std::string*>*, "members", &PrimitivePointerTest::GetMembers),
        GETTER(PrimitivePointerTest, const std::vector<std::string**>**, "subjects", &PrimitivePointerTest::GetSubjects),
        GETTER(PrimitivePointerTest, const std::vector<int***>***, "points", &PrimitivePointerTest::GetPoints),
        GETTER(PrimitivePointerTest, const std::vector<std::string***>***, "cities", &PrimitivePointerTest::GetCities)
        REGISTER_GETTER_END

        REGISTER_SETTER_START
        SETTER(PrimitivePointerTest, const long*, "id", &PrimitivePointerTest::SetId),
        SETTER(PrimitivePointerTest, const std::string*, "name", &PrimitivePointerTest::SetName),
        SETTER(PrimitivePointerTest, const double **, "score", &PrimitivePointerTest::SetScore),
        SETTER(PrimitivePointerTest, const int***, "age", &PrimitivePointerTest::SetAge),
        SETTER(PrimitivePointerTest, const std::vector<int*>*, "codes", &PrimitivePointerTest::SetCodes),
        SETTER(PrimitivePointerTest, const std::vector<std::string*>*, "members", &PrimitivePointerTest::SetMembers),
        SETTER(PrimitivePointerTest, const std::vector<std::string**>**, "subjects", &PrimitivePointerTest::SetSubjects),
        SETTER(PrimitivePointerTest, const std::vector<int***>***, "points", &PrimitivePointerTest::SetPoints),
        SETTER(PrimitivePointerTest, const std::vector<std::string***>***, "cities", &PrimitivePointerTest::SetCities)
        REGISTER_SETTER_END
    };

    TEST(PrimitivePointerTest, SerializeTest) {
        PrimitivePointerTest *p = new PrimitivePointerTest();
        p->SetId(new long(100));
        p->SetName(new std::string("Rezaul karim"));
        p->SetScore(const_cast<const double **>(new double*(new double (100.5))));
        p->SetAge(const_cast<const int***>(new int**(new int*(new int(45)))));

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

        auto sub = new std::vector<std::string**>*(new std::vector<std::string**>{
                new std::string*(new std::string("Physics")),
                new std::string*(new std::string("Math")),
                new std::string*(new std::string("Chemistry"))
        });
        p->SetSubjects(const_cast<const std::vector<std::string**> **>(sub));

        auto points = new std::vector<int***>**(new std::vector<int***>*(new std::vector<int***>{
                new int**(new int*(new int(1))),
                new int**(new int*(new int(2))),
                new int**(new int*(new int(3)))
        }));
        p->SetPoints(const_cast<const std::vector<int***> ***>(points));

        auto cities = new std::vector<std::string***>**(new std::vector<std::string***>*(new std::vector<std::string***>{
                new std::string**(new std::string*(new std::string("New York"))),
                new std::string**(new std::string*(new std::string("Paris"))),
                new std::string**(new std::string*(new std::string("London")))
        }));
        p->SetCities(const_cast<const std::vector<std::string ***> ***>(cities));

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

        ASSERT_TRUE(jsonObject["points"].is_array());
        ASSERT_TRUE(jsonObject["points"][0] == 1);
        ASSERT_TRUE(jsonObject["points"][1] == 2);
        ASSERT_TRUE(jsonObject["points"][2] == 3);

        ASSERT_TRUE(jsonObject["cities"].is_array());
        ASSERT_TRUE(jsonObject["cities"][0].template get<std::string>().compare("New York") == 0);
        ASSERT_TRUE(jsonObject["cities"][1].template get<std::string>().compare("Paris") == 0);
        ASSERT_TRUE(jsonObject["cities"][2].template get<std::string>().compare("London") == 0);
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

        jsonObject["points"] = nlohmann::json::array();
        jsonObject["points"][0] = 1;
        jsonObject["points"][1] = 2;
        jsonObject["points"][2] = 3;

        jsonObject["cities"] = nlohmann::json::array();
        jsonObject["cities"][0] = "New York";
        jsonObject["cities"][1] = "Paris";
        jsonObject["cities"][2] = "London";

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

        ASSERT_TRUE((***a.GetPoints()).size() == 3);
        ASSERT_TRUE(***(***a.GetPoints())[0] == 1);
        ASSERT_TRUE(***(***a.GetPoints())[1] == 2);
        ASSERT_TRUE(***(***a.GetPoints())[2] == 3);

        ASSERT_TRUE((***a.GetCities()).size() == 3);
        ASSERT_TRUE((***(***a.GetCities())[0]).compare("New York") == 0);
        ASSERT_TRUE((***(***a.GetCities())[1]).compare("Paris") == 0);
        ASSERT_TRUE((***(***a.GetCities())[2]).compare("London") == 0);

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

        ASSERT_TRUE((***p->GetPoints()).size() == 3);
        ASSERT_TRUE(***(***p->GetPoints())[0] == 1);
        ASSERT_TRUE(***(***p->GetPoints())[1] == 2);
        ASSERT_TRUE(***(***p->GetPoints())[2] == 3);

        ASSERT_TRUE((***p->GetCities()).size() == 3);
        ASSERT_TRUE((***(***p->GetCities())[0]).compare("New York") == 0);
        ASSERT_TRUE((***(***p->GetCities())[1]).compare("Paris") == 0);
        ASSERT_TRUE((***(***p->GetCities())[2]).compare("London") == 0);
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

        ASSERT_TRUE((***(*pp)->GetPoints()).size() == 3);
        ASSERT_TRUE(***(***(*pp)->GetPoints())[0] == 1);
        ASSERT_TRUE(***(***(*pp)->GetPoints())[1] == 2);
        ASSERT_TRUE(***(***(*pp)->GetPoints())[2] == 3);

        ASSERT_TRUE((***(*pp)->GetCities()).size() == 3);
        ASSERT_TRUE((***(***(*pp)->GetCities())[0]).compare("New York") == 0);
        ASSERT_TRUE((***(***(*pp)->GetCities())[1]).compare("Paris") == 0);
        ASSERT_TRUE((***(***(*pp)->GetCities())[2]).compare("London") == 0);
        delete *pp;
        delete pp;

        PrimitivePointerTest ***ppp = open_json::FromJson<PrimitivePointerTest***>(jsonObject);
        ASSERT_TRUE((**ppp)->GetCodes()->size() == 3);
        ASSERT_TRUE(*(*(**ppp)->GetCodes())[0] == 100);
        ASSERT_TRUE(*(*(**ppp)->GetCodes())[1] == 200);
        ASSERT_TRUE(*(*(**ppp)->GetCodes())[2] == 300);

        ASSERT_TRUE((**ppp)->GetMembers()->size() == 3);
        ASSERT_TRUE( (*(*(**ppp)->GetMembers())[0]).compare("First member") == 0);
        ASSERT_TRUE( (*(*(**ppp)->GetMembers())[1]).compare("Second member") == 0);
        ASSERT_TRUE( (*(*(**ppp)->GetMembers())[2]).compare("Third member") == 0);

        ASSERT_TRUE((**(**ppp)->GetSubjects()).size() == 3);
        ASSERT_TRUE((**(**(**ppp)->GetSubjects())[0]).compare("Physics") == 0);
        ASSERT_TRUE((**(**(**ppp)->GetSubjects())[1]).compare("Math") == 0);
        ASSERT_TRUE((**(**(**ppp)->GetSubjects())[2]).compare("Chemistry") == 0);

        ASSERT_TRUE((***(**ppp)->GetPoints()).size() == 3);
        ASSERT_TRUE(***(***(**ppp)->GetPoints())[0] == 1);
        ASSERT_TRUE(***(***(**ppp)->GetPoints())[1] == 2);
        ASSERT_TRUE(***(***(**ppp)->GetPoints())[2] == 3);

        ASSERT_TRUE((***(**ppp)->GetCities()).size() == 3);
        ASSERT_TRUE((***(***(**ppp)->GetCities())[0]).compare("New York") == 0);
        ASSERT_TRUE((***(***(**ppp)->GetCities())[1]).compare("Paris") == 0);
        ASSERT_TRUE((***(***(**ppp)->GetCities())[2]).compare("London") == 0);
        delete **ppp;
        delete *ppp;
        delete ppp;
    }
}