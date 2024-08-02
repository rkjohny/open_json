# open_json
A modern c++ library to serialize and deserialize c++ objects to and from <a href = "https://github.com/nlohmann/json"> nlhomann::json</a> object.
* Free, open source, lightweight, headers-only json serializer/deserializer for c++ objects using <b>getter</b>, <b>setter</b> and <b>default constructor</b>.
* Just include the header files or only the <b>open_json.h</b> file (in include directory) in your project
* <b>This library converts nlohmann::json objects to and from c++ objects</B>
  * Serialization:
    * convert c++ object to nlohmann::json objects.
  * Deserialization:
    * convert nlohmann::json objects to c++ objects.
* nlohmann::json library can be replaced by any other json library, like <b>cpprestsdk::json</b>

## Toolset:
* MinGW64 version 11.0 w64

## Language Standard:
* C++17

## Build tool:
* cmake version 3.28.1
* ninja

## Debugger:
* GDB 14.1

## Dependencies:
* <a href="https://github.com/nlohmann/json">nlohmann-json</a>

## Prepare environment:

* ### Install MSYS2 (64 bit):
  * https://www.msys2.org

* ### Install MinGW64:
  * pacman -S mingw-w64-x86_64-toolchain

    * #### Install gcc
      * pacman -S mingw-w64-x86_64-gcc
    
    * #### install GDB
      * pacman -S mingw-w64-x86_64-gdb

* ### Install cmake
  * pacman -S mingw-w64-x86_64-cmake

     * #### Install ninja
       * pacman -S mingw-w64-x86_64-ninja
   
* ### Install nlohmann json library:
  * pacman -S mingw-w64-x86_64-nlohmann-json


# How to use:

* ## Serializing
* Serializing is done by open_json::ToJson method. It takes a C++ object and returns a nlohmann::json object.
* This method supports any level of pointer

* ### Primitive integer
````
#include "open_json.h"

nlohmann::json jsonObject;

int intValue = 10;
jsonObject = open_json::ToJson(intValue);

int *ptrInt = new int(-45);
jsonObject = open_json::ToJson(ptrInt);
delete ptrInt;
````

* ### Primitive char
````
nlohmann::json jsonObject;

char charValue = 'A';

jsonObject = open_json::ToJson(charValue);
````

* ### String
````
nlohmann::json jsonObject;

std::string str = "Hello World!";

jsonObject = open_json::ToJson(str);
````

* ### Vector
````
std::vector<int> vecInt;

vecInt.push_back(1);
vecInt.push_back(2);
vecInt.push_back(3);

nlohmann::json jsonArray = open_json::ToJson(vecInt);
````
#### vector of object can be serialized in the same way

* ### Custom Class
* To serialize a custom object, you need to write getter methods of the member variable those you want to serialize.
* Then register the getter method as bellow:
````
REGISTER_GETTER_START
GETTER(<class>, <return type of the getterr>, <json property>, <getter method>)
REGISTER_GETTER_END
````

#### Example:
````
class Person {
    protected:
        int age;
        std::string name;

    public:
        Person() = default;
        virtual ~Person() = default;

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
};
````

#### Now serialize a person object:
````
nlohmann::json jsonObject;

Person person;

person.SetAge(20);
person.SetName("David Beckham");

jsonObject = open_json::ToJson(person);

// it supports any level of pointer
Person *p = new Person();
p->SetAge(30);
p->SetName("Lionel Messi");

jsonObject = open_json::ToJson(p);
delete p;
````

#### Content of jsonObject
````
{
    "age": 20,
    "name": "David Beckham"
}
````

* ### Derived Class
* To serialize ab object of derived class, if you want to serialize the member variables you need to register the getters in derived class as bellow:
* Base class must have the getters registered
````
REGISTER_GETTER_INCLUDING_BASE_START(<Base Class>)
GETTER(.....
REGISTER_GETTER_INCLUDING_BASE_END
````

##### Example
````
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
        
        const int* GetId() const {
            return id;
        }

        void SetId(const int* id) {
            this->id = const_cast<int*>(id);
        }

        REGISTER_GETTER_INCLUDING_BASE_START(Person)
        GETTER(Student, const int*, "id", &Student::GetId)
        REGISTER_GETTER_INCLUDING_BASE_END
};
````

#### To serialize
````
nlohmann::json jsonObject;

Student student;
student.SetAge(30);
student.SetName("Leonel Messi");
student.SetId(new int(10));

jsonObject = open_json::ToJson(student);

// supports any level of pointer
Student *p = new Student();
p->SetAge(40);
p->SetName("David Beckham");
p->SetId(new int(20));

jsonObject = open_json::ToJson(p);
delete p;
````

#### Content of jsonObject
````
{
    "age": 30,
    "id": 10,
    "name": "Leonel Messi"
}
````

* ### Serializing enum
````
enum EnumTest {
    A = 10,
    B = 20,
    C = 30,
};

EnumTest enm = EnumTest::B;
nlohmann::json jsonObject = open_json::ToJson(enm);
````

* ### Serializing array
````
nlohmann::json jsonObject;

int intArr[] = {10, 20, 30, 40};

jsonObject = open_json::ToJson(intArr, 4);
````

* ### Char array
* #### string literal will be treated as character array;
````
nlohmann::json jsonArray;

// string literal will be treated as character array;
char *charPtr = "Hello World!";
jsonArray = open_json::ToJson(charPtr, strlen(charPtr));

char charArr[] = {'a', 'b', 'c', 'd'};
jsonArray = open_json::ToJson(charArr, 4);
````

* ### String array
````
nlohmann::json jsonArray;

std::string strArray[] = {"Hi there!", "How are you?", "How is going?"};

jsonArray = open_json::ToJson(strArray, 3);
````
#### array of object can be serialized in the same way

* ### Map
````
std::map<std::string, Student> mapObj;

// insert into map like:
//mapObj["first"] = student1;
//mapObj["second"] = student2;
//mapObj["third"] = student3;
                
jsonObject = open_json::ToJson(mapObj);
````

* ### UniquePtr
````
std::unique_ptr<Person> ptr = std::make_unique<Person>();
ptr->SetName("Rezaul Karim");
ptr->SetAge(40);

nlohmann::json jsonObject = open_json::ToJson(ptr);
````

* ### SharedPtr
````
std::shared_ptr<Person> ptr = std::make_shared<Person>();
ptr->SetName("Rezaul Karim");
ptr->SetAge(40);

nlohmann::json jsonObject = open_json::ToJson(ptr);
````

* ### WeakPtr
````
std::shared_ptr<Person> sp = std::make_shared<Person>();
sp->SetName("Rezaul Karim");
sp->SetAge(40);

std::weak_ptr<Person> wp = sp;

// if wp can be locked, person object will be serilazied and returned, otherwise an empty json objetc will be returned
nlohmann::json jsonObject = open_json::ToJson(wp);
````

