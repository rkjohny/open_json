#include <gtest/gtest.h>
#include <string>
#include "../../include/open_json.h"

namespace open_json_test::tutorial {

    class Person {
    protected:
        int age;
        std::string name;

    public:
        Person() = default;

        virtual ~Person() = default;

        Person(const Person &person) {
            this->age = person.age;
            this->name = person.name;
        }

        Person(Person &&person) {
            this->age = std::move(person.age);
            this->name = std::move(person.name);
        }

        Person &operator=(const Person &person){
            this->age = person.age;
            this->name = person.name;
            return *this;
        }

        Person &operator=(Person &&person){
            this->age = std::move(person.age);
            this->name = std::move(person.name);
            return *this;
        }

        int GetAge() const {
            return age;
        }

        void SetAge(int age) {
            this->age = age;
        }

        const std::string &GetName() const {
            return name;
        }

        void SetName(const std::string &name) {
            this->name = name;
        }

        REGISTER_GETTER_START
        GETTER(Person, int, "age", &Person::GetAge),
        GETTER(Person, const std::string&, "name", &Person::GetName)
        REGISTER_GETTER_END

        REGISTER_SETTER_START
        SETTER(Person, int, "age", &Person::SetAge),
        SETTER(Person, const std::string&, "name", &Person::SetName)
        REGISTER_SETTER_END
    };

    class Student : public Person {
    protected:
        int *id;

    public:
        Student() {
            id = nullptr;
        }

        virtual ~Student() {
            if(id) {
                delete id;
            }
        }

        Student(const Student &student) : Person(student) {
            this->id = new int(*student.id);
        }

        Student(Student &&student) : Person(std::move(student)) {
            this->id = new int(std::move(*student.id));
        }

        Student &operator=(const Student &student) {
            this->age = student.age;
            this->name = student.name;
            this->id = new int(*student.id);
            return *this;
        }

        Student& operator=(Student &&student) {
            this->age = std::move(student.age);
            this->name = std::move(student.name);
            this->id = new int(std::move(*student.id));
            return *this;
        }

        const int* GetId() const {
            return id;
        }

        void SetId(const int* id) {
            this->id = const_cast<int*>(id);
        }

        REGISTER_GETTER_INCLUDING_BASE_START(Person)
        GETTER(Student, const int*, "id", &Student::GetId)
        REGISTER_GETTER_INCLUDING_BASE_END

        REGISTER_SETTER_INCLUDING_BASE_START(Person)
        SETTER(Student, const int*, "id", &Student::SetId)
        REGISTER_SETTER_INCLUDING_BASE_END
    };

    TEST(Person, Serialize) {
        nlohmann::json jsonObject;

        Person person;
        person.SetAge(20);
        person.SetName("David Beckham");

        jsonObject = open_json::ToJson(person);

        ASSERT_EQ(person.GetAge(), jsonObject["age"].template get<int>());
        ASSERT_EQ(0, person.GetName().compare(jsonObject["name"].template get<std::string>()));

        Person *p = new Person();
        p->SetAge(30);
        p->SetName("Lionel Messi");

        jsonObject = open_json::ToJson(p);

        ASSERT_EQ(p->GetAge(), jsonObject["age"].template get<int>());
        ASSERT_EQ(0, p->GetName().compare(jsonObject["name"].template get<std::string>()));
        delete p;
    }

    TEST(Person, Deserialize) {
        nlohmann::json jsonObject;

        jsonObject["age"] = 20;
        jsonObject["name"] = "David Beckham";

        Person person = open_json::FromJson<Person>(jsonObject);

        ASSERT_EQ(jsonObject.at("age").template get<int>(), person.GetAge());
        ASSERT_EQ(0, jsonObject.at("name").template get<std::string>().compare(person.GetName()));

        Person *p = open_json::FromJson<Person*>(jsonObject);

        ASSERT_EQ(jsonObject["age"].template get<int>(), p->GetAge());
        ASSERT_EQ(0, jsonObject["name"].template get<std::string>().compare(p->GetName()));
        delete p;
    }

    TEST(Student, Serialize) {
        nlohmann::json jsonObject;

        Student student;
        student.SetAge(30);
        student.SetName("Leonel Messi");
        student.SetId(new int(10));

        jsonObject = open_json::ToJson(student);
        ASSERT_EQ(student.GetAge(), jsonObject["age"].template get<int>());
        ASSERT_EQ(0, student.GetName().compare(jsonObject["name"].template get<std::string>()));
        ASSERT_EQ(*student.GetId(), jsonObject["id"].template get<int>());

        Student *p = new Student();
        p->SetAge(40);
        p->SetName("David Beckham");
        p->SetId(new int(20));

        jsonObject = open_json::ToJson(p);
        ASSERT_EQ(p->GetAge(), jsonObject["age"].template get<int>());
        ASSERT_EQ(0, p->GetName().compare(jsonObject["name"].template get<std::string>()));
        ASSERT_EQ(*p->GetId(), jsonObject["id"].template get<int>());
        delete p;
    }

    TEST(Student, Deserialize) {
        nlohmann::json jsonObject;

        jsonObject["age"] = 30;
        jsonObject["name"] = "Leonel Messi";
        jsonObject["id"] = 10;

        Student student = open_json::FromJson<Student>(jsonObject);

        ASSERT_EQ(jsonObject["age"].template get<int>(), student.GetAge());
        ASSERT_EQ(0, jsonObject["name"].template get<std::string >().compare(student.GetName()));
        ASSERT_EQ(jsonObject["id"].template get<int>(), *student.GetId());

        Student *p = open_json::FromJson<Student*>(jsonObject);
        ASSERT_EQ(jsonObject["age"].template get<int>(), p->GetAge());
        ASSERT_EQ(0, jsonObject["name"].template get<std::string >().compare(p->GetName()));
        ASSERT_EQ(jsonObject["id"].template get<int>(), *p->GetId());
        delete p;
    }
}