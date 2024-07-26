#include <gtest/gtest.h>
#include <string>
#include "../../../include/open_json.h"

namespace open_json_test::deserialize::simple_class {

    class ClassD {
    private:
        int *id;
        std::string *name;
        double **score;
        long ***age;

    public:
        ClassD() {
            std::cout << "ClassD()" << std::endl;
        };

        void copy(ClassD &&obj) {
            this->id = new int();
            *this->id = std::move(*obj.id);

            this->name = new std::string;
            *this->name = std::move(*obj.name);

            this->score = new double*;
            *this->score = new double;
            **this->score = std::move(**obj.score);

            this->age = new long**;
            *this->age = new long*;
            **this->age = new long;
            ***this->age = std::move(***obj.age);
        }

        void copy(ClassD &obj) {
            this->id = new int();
            *this->id = *obj.id;

            this->name = new std::string;
            *this->name = *obj.name;

            this->score = new double*;
            *this->score = new double;
            **this->score = **obj.score;

            this->age = new long**;
            *this->age = new long*;
            **this->age = new long;
            ***this->age = ***obj.age;
        }

        ClassD(ClassD &&obj) {
            std::cout << "inside ClassD(ClassD &&obj)" << std::endl;
            //this->copy(std::move(obj));
        }

        ClassD(ClassD &obj) {
            std::cout << "inside ClassD(ClassD &obj)" << std::endl;
            //this->copy(obj);
        }

        ClassD& operator=(ClassD &&obj) {
            std::cout << "inside ClassD operator=(ClassD &&obj)" << std::endl;

//            std::cout << obj.id << std::endl;
//            std::cout << *obj.id << std::endl;

//            std::cout << id << std::endl;
//            std::cout << *id << std::endl;

            //this->copy(std::move(obj));
            return *this;
        }

        ClassD& operator=(ClassD &obj) {
            std::cout << "inside ClassD& operator=(ClassD &obj)" << std::endl;

            //this->copy(obj);
            return *this;
        }

        virtual ~ClassD() {
            std::cout << "~ClassD() " << id << std::endl;
            std::cout << "~ClassD() " << *id << std::endl;
//            if (id) {
//                delete id;
//            }
//            if (name) delete name;
//            if(score) {
//                delete *score;
//                delete score;
//            }
//            if(age) {
//                delete **age;
//                delete *age;
//                delete age;
//            }
        }

        int* GetId() const {
            return id;
        }

        const std::string* GetName() const {
            return name;
        }

        void SetId(int *n) {
            this->id = const_cast<int*>(n);
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

        long ***GetAge() const {
            return age;
        }

        void SetAge(long ***a) {
            this->age =  a;
        }

        REGISTER_SETTER_START
        SETTER(ClassD, int*, "id", &ClassD::SetId),
        SETTER(ClassD, std::string*, "name", &ClassD::SetName),
        SETTER(ClassD, double **, "score", &ClassD::SetScore),
        SETTER(ClassD, long***, "age", &ClassD::SetAge)
        REGISTER_GETTER_END
    };

    TEST(ClassD, Test) {
        nlohmann::json jsonObject = nlohmann::json::object();
        jsonObject["id"] = 200;
        jsonObject["name"] = "David Jonson";
        jsonObject["score"] = 10.5;
        jsonObject["age"] = 40;

//        ClassD a = open_json::FromJson<ClassD>(jsonObject);
//        ASSERT_EQ(jsonObject.at("id").template get<int>(), *a.GetId());
//        ASSERT_EQ(0, jsonObject.at("name").template get<std::string>().compare(*a.GetName()));
//        ASSERT_DOUBLE_EQ(jsonObject.at("score").template get<double>(), **a.GetScore());
//        ASSERT_EQ(jsonObject.at("age").template get<long>(), ***a.GetAge());

        ClassD *p = open_json::FromJson<ClassD*>(jsonObject);
        ASSERT_EQ(jsonObject.at("id").template get<int>(), *p->GetId());
        ASSERT_EQ(0, jsonObject.at("name").template get<std::string>().compare(*p->GetName()));
        ASSERT_DOUBLE_EQ(jsonObject.at("score").template get<double>(), **p->GetScore());
        ASSERT_EQ(jsonObject.at("age").template get<long>(), ***p->GetAge());
        delete p;
//
//        ClassD **pp = open_json::FromJson<ClassD**>(jsonObject);
//        ASSERT_EQ(jsonObject.at("id").template get<int>(), *(*pp)->GetId());
//        ASSERT_EQ(0, jsonObject.at("name").template get<std::string>().compare(*(*pp)->GetName()));
//        ASSERT_DOUBLE_EQ(jsonObject.at("score").template get<double>(), **(*pp)->GetScore());
//        ASSERT_EQ(jsonObject.at("age").template get<long>(), ***(*pp)->GetAge());
//        delete *pp;
//        delete pp;
    }
}