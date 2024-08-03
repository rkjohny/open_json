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
GETTER(<class>, <return type of the getter>, <json property>, <getter method>)
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
        // Important: assign null as the default value of any pointer member variable, so if we dont set a valid value, it will be ignored and will not be serialized
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
mapObj["first"] = student1;
mapObj["second"] = student2;
mapObj["third"] = student3;
                
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

* ## Deserializing
* Deserializing is done by open_json::FromJson<>() method. It takes a nlohmann::json object and returns a C++ object
* This method supports any level of pointer
* Use pointer to avoid copying

* ### Primitive Integer
````
nlohmann::json jsonObject = 10;

// deserializing        
int intValue = open_json::FromJson<int>(jsonObject);

jsonObject = -1;
// while getting pointer, memory will be allocated by the library so amke sure to free the allocated memory
int *minusOne = open_json::FromJson<int *>(jsonObject);
delete minusOne;

jsonObject = 1;
int **plusOne = open_json::FromJson<int **>(jsonObject);
delete *plusOne;
delete plusOne;
````

* ### Primitive char
````
nlohmann::json jsonObject = 'A';
              
char charValue = open_json::FromJson<char>(jsonObject);
````

* ### String
````
nlohmann::json jsonObject = "Hello World!";

std::string str = open_json::FromJson<std::string>(jsonObject);
````

* ### Vector 
````
nlohmann::json jsonArr = nlohmann::json::array();
jsonArr.push_back(10);
jsonArr.push_back(20);
jsonArr.push_back(30);

std::vector<int> intVec = open_json::FromJson<std::vector<int>>(jsonArr);

std::vector<int *> *ptrVec = open_json::FromJson<std::vector<int *> *>(jsonArr);
// Make sure to deallocate the memory
for (auto p: *ptrVec) {
    delete p;
}
delete ptrVec
````
#### Vector of object can be deserialized in the same way

* ### Custom Class
* To deserialize a custom object, you need to write setter methods of the member variable those you want to deserialize.
* Then register the setter method as bellow:
````
REGISTER_SETTER_START
SETTER(<Class>, <argument type of the setter>, <json priperty>, <setter method>),
REGISTER_SETTER_END
````
* #### To deserialize an object of a custom class you must follow some rules:
* #### Rule 1: The class must have a public default constructor
In our example of Person class:
````
class Person {
    public:
        Person() = default;
};
````
* #### Rule 2: The class must override default cpoy constructor, move constructor, copy assignment operator and move assignment operator
In our example of Person class:
````
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
};
````

* #### Rule 3: If there is any pointers in the class member do not allocate memory for that pointer, memory will be allocated by the library. And do not forget to deallocate the allocated memory. Also assign null as the default value of the member
In our example of Student class:
````
class Student : public Person {
protected:
    int *id;

public:
    Student() {
        // do not allocate memory. id will be allocated by the librray 
        id = nullptr;
    }

    virtual ~Student() {
        // do not forget to deallocate the allocated memory
        if(id) {
            delete id;
        }
    }
};
````

Now our Person class
````
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
    
    REGISTER_SETTER_START
    SETTER(Person, int, "age", &Person::SetAge),
    SETTER(Person, const std::string&, "name", &Person::SetName)
    REGISTER_SETTER_END
};
````

#### To deserialize
````
nlohmann::json jsonObject;

jsonObject["age"] = 20;
jsonObject["name"] = "David Beckham";

Person person = open_json::FromJson<Person>(jsonObject);

Person *p = open_json::FromJson<Person*>(jsonObject);
delete p;
````

* ### Derived Class
* To deserialize ab object of derived class, if you want to deserialize the member variables you need to register the setters in derived class as bellow:
* Base class must have the setters registered
````
REGISTER_SETTER_INCLUDING_BASE_START(<Base Class>)
SETTER(.....
REGISTER_SETTER_INCLUDING_BASE_END
````

#### Example
Now our Person and Student class
````
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
        // Imnportant: allocate new memory, do not directly assign pointer
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

    REGISTER_SETTER_INCLUDING_BASE_START(Person)
    SETTER(Student, const int*, "id", &Student::SetId)
    REGISTER_SETTER_INCLUDING_BASE_END
};
````

#### To deserialize
````
nlohmann::json jsonObject;

jsonObject["age"] = 30;
jsonObject["name"] = "Leonel Messi";
jsonObject["id"] = 10;

Student student = open_json::FromJson<Student>(jsonObject);

Student *p = open_json::FromJson<Student*>(jsonObject);
delete p;
````
#### See the file <a href="./tests/src/Tutorial.cpp">Tutorial.cpp</a> to see the full example

* ### Deserializing enum
````
enum EnumTest {
    A = 10,
    B = 20,
    C = 30,
};

nlohmann::json jsonObject = static_cast<int>(EnumTest::B);
EnumTest enm = open_json::FromJson<EnumTest>(jsonObject);    
````

* ### Deserializing Array
````
nlohmann::json jsonObject = nlohmann::json::array();
jsonObject[0]["age"] = 30;
jsonObject[0]["name"] = "David Jonson";

jsonObject[1]["age"] = 20;
jsonObject[1]["name"] = "Rezaul Karim";

jsonObject[2]["age"] = 40;
jsonObject[2]["name"] = "Mr. xyz";

Person *a = open_json::FromJson<Person*>(jsonObject, 3);
delete [] (a);
````

* ### Deserializing Map
````
nlohmann::json jsonObject;

// create json for the map
jsonObject["first"] = student1;
jsonObject["second"] = student2;
jsonObject["third"] = student3

std::map<std::string, Student> mapObject = open_json::FromJson<std::map<std::string, Student>>(jsonObject);
````

* ### Deserializing UniquePtr
````
nlohmann::json jsonObject;

jsonObject["age"] = 40;
jsonObject["name"] = "Rezaul karim";

std::unique_ptr<Person> ptr = open_json::FromJson<std::unique_ptr<Person>>(jsonObject);
````

* ### Deserializing SharedPtr
````
nlohmann::json jsonObject;

jsonObject["age"] = 40;
jsonObject["name"] = "Rezaul karim";

std::shared_ptr<Person> ptr = open_json::FromJson<std::shared_ptr<Person>>(jsonObject);
````

* ### Deserializing Rvalue Reference
````
class RvalueReference {
public:
    int id;
    std::string name;
    
    RvalueReference() = default;
    
    // Override default copy constructor, move constructor, copy assignment and move assignment operator
      
    void SetId(int &&id) {
        this->id = std::move(id);
    }

    void SetName(std::string &&name) {
        this->name = std::move(name);
    }

    REGISTER_SETTER_START
    SETTER(RvalueReference, int &&, "id", &RvalueReference::SetId),
    SETTER(RvalueReference, std::string &&, "name", &RvalueReference::SetName)
    REGISTER_SETTER_END
};

nlohmann::json jsonObject = nlohmann::json::object();
jsonObject["id"] = 10;
jsonObject["name"] = "Rezaul Karim";

RvalueReference obj = open_json::FromJson<RvalueReference>(jsonObject);
````

