# open_json
A modern c++ library to serialize and deserialize c++ objects to and from <a href = "https://github.com/nlohmann/json"> nlhoman::json</a> object.
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
* <a href="https://github.com/boostorg/boost">boost.optional</a>

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

* ### Install boost (installing only boost::optional is sufficient):
  * pacman -S mingw-w64-x86_64-boost

# Example:

* ## Serializing
* ### Primitive integer
````
#include "open_json.h"

nlohmann::json jsonObject;

jsonObject = open_json::ToJson(10);
ASSERT_EQ(10, jsonObject.template get<int>());

int intValue = 10;
jsonObject = open_json::ToJson(intValue);
ASSERT_EQ(intValue, jsonObject.template get<int>());


int *ptrInt = new int(-45);
jsonObject = open_json::ToJson(ptrInt);
ASSERT_EQ(*ptrInt, jsonObject.template get<int>());
delete ptrInt;

int **ptr2Int = new int*(new int(-50));
jsonObject = open_json::ToJson(ptr2Int);
ASSERT_EQ(**ptr2Int, jsonObject.template get<int>());
delete *ptr2Int;
delete ptr2Int;

````

* ### Primitive double
````
nlohmann::json jsonObject;

jsonObject = open_json::ToJson(10.51);
ASSERT_DOUBLE_EQ(10.51, jsonObject.template get<double>());

double decimalVal = 10.51;
jsonObject = open_json::ToJson(decimalVal);
ASSERT_DOUBLE_EQ(decimalVal, jsonObject.template get<double>());

const double *decimalPtr2 = &decimalVal;
jsonObject = open_json::ToJson(decimalPtr2);
ASSERT_DOUBLE_EQ(*decimalPtr2, jsonObject.template get<double>());

const double * const *decimalPtr5 = new double*(new double(-30.51));
jsonObject = open_json::ToJson(decimalPtr5);
ASSERT_DOUBLE_EQ(**decimalPtr5, jsonObject.template get<double>());
delete *decimalPtr5;
delete decimalPtr5;
````

* ### Primitive char
````
nlohmann::json jsonObject;
int intVal = 'A';
char charValue = 'A';

jsonObject = open_json::ToJson(charValue);
ASSERT_EQ(intVal, jsonObject.template get<int>());
ASSERT_EQ(charValue, jsonObject.template get<char>());

unsigned char ucharVal = 'A';
jsonObject = open_json::ToJson(ucharVal);
ASSERT_EQ(intVal, jsonObject.template get<int>());
ASSERT_EQ(ucharVal, jsonObject.template get<unsigned char>());

jsonObject = open_json::ToJson(charValue);
ASSERT_EQ(intVal, jsonObject.template get<int>());
ASSERT_EQ(charValue, jsonObject.template get<char>());
ASSERT_EQ(charValue, jsonObject.template get<int32_t>());

unsigned char ucharVal = 'A';
jsonObject = open_json::ToJson(ucharVal);
ASSERT_EQ(intVal, jsonObject.template get<int>());
ASSERT_EQ(ucharVal, jsonObject.template get<unsigned char>());
ASSERT_EQ(ucharVal, jsonObject.template get<uint32_t>());
````

* ### string and string
````
nlohmann::json jsonObject;

std::string str = "Hello World!";
jsonObject = open_json::ToJson(str);
ASSERT_EQ(0, str.compare(jsonObject.template get<std::string>()));

const std::string str2 = "C++ is awesome!";
jsonObject = open_json::ToJson(std::move(str2));
ASSERT_EQ(0, str2.compare(jsonObject.template get<std::string>()));

std::string *str3 = &str;
jsonObject = open_json::ToJson(str3);
ASSERT_EQ(0, str3->compare(jsonObject.template get<std::string>()));

std::string **str7 = new std::string*(new std::string("Hi there!"));
jsonObject = open_json::ToJson(str7);
ASSERT_EQ(0, (*str7)->compare(jsonObject.template get<std::string>()));
delete *str7;
delete str7;
````
#### For more test cases of primitive types look into file <a href="./tests/src/SerializePrimitiveTest.cpp">SerializePrimitiveTest.cpp</a>

* ### Vector&lt;int&gt;
````
std::vector<int> vecInt;

vecInt.push_back(1);
vecInt.push_back(2);
vecInt.push_back(3);

nlohmann::json jsonArr = open_json::ToJson(vecInt);
ASSERT_TRUE(jsonArr.is_array());
ASSERT_TRUE(jsonArr.size() == vecInt.size());
auto itr1 = vecInt.begin();
for (auto &arrItem: jsonArr) {
    ASSERT_EQ(*itr1, arrItem.template get<int>());
    ++itr1;
}
````

* ### Vector&lt;double&#42;&gt;&#42;
````
std::vector<double *> *m_scores;

m_scores = new vector<double *>;
m_scores->push_back(new double(9.9));
m_scores->push_back(new double(10.01));
m_scores->push_back(new double(10.1));
            
nlohmann::json jsonArr = open_json::ToJson(m_scores);
ASSERT_TRUE(jsonArr.is_array());
ASSERT_TRUE(jsonArr.size() == m_scores->size());
auto itr = m_scores->begin();
for (auto &arrItem: jsonArr) {
    ASSERT_DOUBLE_EQ(arrItem.template get<double>(), **itr);
    ++itr;
}

for (auto p: *m_scores) {
    delete p;
}
delete m_scores;
````

* ### Vector&lt;std::string&gt;&#42;
````
std::vector<std::string> *m_names;

m_names = new std::vector<std::string>();
m_names->push_back(string("John Carry"));
m_names->push_back(string("David Jonson"));
m_names->push_back(string("Emma Martin"));

nlohmann::json jsonArr = open_json::ToJson(m_names);
ASSERT_TRUE(jsonArr.is_array());
ASSERT_TRUE(jsonArr.size() == m_names->size());
auto itr = m_names->begin();
for (auto &arrItem: jsonArr) {
    ASSERT_EQ(0, (*itr).compare(arrItem.template get<string>()));
    ++itr;
}

delete m_names;
````

* ### Vector&lt;std::string&#42;&gt;&#42;
````
std::vector<std::string *> *m_emails;

m_emails = new std::vector<std::string *>();
m_emails->push_back(new string("john@sample.com"));
m_emails->push_back(new string("david@sample.com"));
m_emails->push_back(new string("emma@sample.com"));

nlohmann::json jsonArr = open_json::ToJson(m_emails);
ASSERT_TRUE(jsonArr.is_array());
ASSERT_TRUE(jsonArr.size() == m_emails->size());
auto itr = m_emails->begin();
for (auto &arrItem: jsonArr) {
    ASSERT_EQ(0, (**itr).compare(arrItem.template get<string>()));
    ++itr;
}

for (auto p: *m_emails) {
    delete p;
}
delete m_emails;
````

* ### Vector&lt;string&#42;&gt;&#42;&#42;
````
std::vector<std::string *> **m_cities;

 m_cities = new std::vector<std::string *> * (new std::vector<std::string*>());

std::string *p = new std::string("New York");
(*m_cities)->push_back(p);

p = new std::string("Boston, USA");
(*m_cities)->push_back(p);

p = new std::string("Paris");
(*m_cities)->push_back(p);

jsonArr = open_json::ToJson(std::vector<std::string *>(**m_cities));
ASSERT_TRUE(jsonArr.is_array());
ASSERT_TRUE(jsonArr.size() == (**m_cities).size());
auto itr = (**m_cities).begin();
for (auto &arrItem: jsonArr) {
    ASSERT_EQ(0, std::string(**itr).compare(arrItem.template get<string>()));
    ++itr;
}

jsonArr = open_json::ToJson(m_cities);
ASSERT_TRUE(jsonArr.is_array());
ASSERT_TRUE(jsonArr.size() == (**m_cities).size());
itr = (**m_cities).begin();
for (auto &arrItem: jsonArr) {
    ASSERT_EQ(0, std::string(**itr).compare(arrItem.template get<string>()));
    ++itr;
}

jsonArr = open_json::ToJson(&m_cities);
ASSERT_TRUE(jsonArr.is_array());
ASSERT_TRUE(jsonArr.size() == (**m_cities).size());
itr = (**m_cities).begin();
for (auto &arrItem: jsonArr) {
    ASSERT_EQ(0, std::string(**itr).compare(arrItem.template get<string>()));
    ++itr;
}

for (auto p: **m_cities) {
    delete p;
}
delete *m_cities;
delete m_cities;
````
#### For more test cases of vector types look into file <a href="./tests/src/SerializeVectorTest.cpp">SerializeVectorTest.cpp</a>

* ### Custom Class
* #### You must declare a static public std::tuple member named 'getters' inside the class which contains the list of getters those will be serialized. 

There are three ways to declare the std::tuple filed

* ### Use macro
````
class ClassA {
  private:
    int id;
    std::string name;
    
  public:
    int GetId() const {
      return id;
    }
    
    const std::string &GetName() const {
      return name;
    }
    
    REGISTER_GETTER_START
    GETTER(ClassA, int, "id", &ClassA::GetId),
    GETTER(ClassA, const std::string&, "name", &ClassA::GetName)
    REGISTER_GETTER_END
}
````
Here the two getter methods will be registered with the keys "id" and "name" respectively. 
* To serialize:
````
ClassA a;
nlohmann::json jsonObject = open_json::ToJson(a);
````
Now value of id and name can be accessed as follows:
````
int id = jsonObject.at("id").template get<int>();
std::string name = jsonObject.at("name").template get<std::string>();
````

* ### Use macro and Extending Serializable class:
````
class ClassB : open_json::Serializable {
    private:
        int id;
        std::string name;

    public:
        int GetId() const {
            return id;
        }

        const std::string &GetName() const {
            return name;
        }

        [[nodiscard]]
        const nlohmann::json ToJson() override {
          return open_json::serializer::ToJsonObject(this);
        }
            
        REGISTER_GETTER_START
        GETTER(ClassB, int, "id", &ClassB::GetId),
        GETTER(ClassB, const std::string&, "name", &ClassB::GetName)
        REGISTER_GETTER_END
    };
````
* You need to overwrite the ToJson method as above. Just copy and paste the ToJson method in your class. To serialize:
````
ClassB b;
nlohmann::json jsonObject = b.ToJson();
````
or including getters in base class Serializable 
````
class ClassB : public open_json::Serializable {
private:
    int id = 100;
    std::string name = "Rezaul karim";

public:
    ClassB() = default;

    int GetId() const {
        return id;
    }

    const std::string &GetName() const {
        return name;
    }
    
    [[nodiscard]]
    const nlohmann::json ToJson() override {
        return open_json::serializer::ToJsonObject(this);
    }
            
    REGISTER_GETTER_INCLUDING_BASE_START(open_json::Serializable)
    GETTER(ClassB, int, "id", &ClassB::GetId),
    GETTER(ClassB, const std::string&, "name", &ClassB::GetName)
    REGISTER_GETTER_INCLUDING_BASE_END
};

````
Value of id and name can be accessed as the same way mentioned above

* ### Declaring a tuple of getters:
````
class ClassC {
private:
    int id;
    std::string name;

public:
    int GetId() const {
        return id;
    }

    const std::string &GetName() const {
        return name;
    }

    static constexpr std::tuple getters = std::make_tuple(
            open_json::Getter<ClassC, int>(&ClassC::GetId, "id"),
            open_json::Getter<ClassC, const std::string &>(&ClassC::GetName, "name")
    );
};
````
Here the name of the tuple member which is "getters" is important. The register macro declares the tuple inside.
* To Serialize:
````
ClassC c;
nlohmann::json jsonObject = open_json::ToJson(c);
````

* ### Serializing empty class:
Even the class is an empty class you need to declare the tuple 'getters' with empty getters list
````
class SerializeEmptyClass2 {
public:
    SerializeEmptyClass2() = default;

    REGISTER_GETTER_START
    REGISTER_GETTER_END
};


using Type = typename open_json::Remove_CVR<SerializeEmptyClass2>::Type;
auto getters = Type::getters;
const size_t lengthGetter = std::tuple_size<decltype(getters)>::value;

ASSERT_TRUE(lengthGetter == 0);

SerializeEmptyClass2 emptyObject;
nlohmann::json jsonbObject = open_json::ToJson(emptyObject);

ASSERT_FALSE(jsonbObject.is_null());
ASSERT_TRUE(jsonbObject.is_object());
ASSERT_TRUE(jsonbObject.begin() == jsonbObject.end());

````
or extending Serializable class which actually declares the 'getters'
````
class SerializeEmptyClass : public open_json::Serializable {
public:
    SerializeEmptyClass() = default;
    
    [[nodiscard]]
    const nlohmann::json ToJson() override {
        return open_json::serializer::ToJsonObject(this);
    }
};


using Type = typename open_json::Remove_CVR<SerializeEmptyClass>::Type;
auto getters = Type::getters;
const size_t lengthGetter = std::tuple_size<decltype(getters)>::value;

ASSERT_TRUE(lengthGetter == 0);

SerializeEmptyClass emptyObject;
nlohmann::json jsonbObject = emptyObject.ToJson();

ASSERT_FALSE(jsonbObject.is_null());
ASSERT_TRUE(jsonbObject.is_object());
ASSERT_TRUE(jsonbObject.begin() == jsonbObject.end());

````

* ### Serialize custom class
````
class Person {
private:
    std::string m_name;
    int m_age;
    std::vector<double> m_scores;

public:
    Person() {
        m_name = "Rezaul Karim";
        m_age = 43;
        m_scores.push_back(10.5);
        m_scores.push_back(20.1);
        m_scores.push_back(30.9);
    }

    virtual ~Person() = default;

    const std::string &GetName() const {
        return m_name;
    }

    int GetAge() const {
        return m_age;
    }

    const std::vector<double> &GetScores() const {
        return m_scores;
    }

    static constexpr std::tuple getters = std::make_tuple(
            open_json::Getter<Person, const std::string &>(&Person::GetName, "name"),
            open_json::Getter<Person, int>(&Person::GetAge, "age"),
            open_json::Getter<Person, const std::vector<double> &>(&Person::GetScores, "scores")
    );
};

Person person;
nlohmann::json jsonObject;

jsonObject = open_json::ToJson(person);
ASSERT_TRUE(jsonObject.is_object());
ASSERT_EQ(0, person.GetName().compare(jsonObject.at("name").template get<std::string>()));
ASSERT_EQ(person.GetAge(), jsonObject.at("age").template get<int>());
ASSERT_TRUE(jsonObject.at("scores").is_array());
auto itr = person.GetScores().begin();
for(auto &arrItem : jsonObject.at("scores")) {
    ASSERT_DOUBLE_EQ(*itr, arrItem.template get<double>());
    ++itr;
}
````

* ### Custom Class Using Macro
````
class Student {
private:
    std::string m_name;
    long m_id;
    std::vector<std::string> m_subjects;

public:
    Student() {
        m_name = "Rezaul Karim";
        m_id = 100;
        m_subjects.push_back("Math");
        m_subjects.push_back("Calculus");
        m_subjects.push_back("Geometry");
    }

    virtual ~Student() = default;

    const std::string &GetName() const {
        return m_name;
    }

    long GetId() const {
        return m_id;
    }

    const std::vector<std::string> &GetSubjects() const {
        return m_subjects;
    }

    REGISTER_GETTER_START
    GETTER(Student, const std::string &, "name", &Student::GetName),
    GETTER(Student, long, "id", &Student::GetId),
    GETTER(Student, const std::vector<std::string>&, "subjects", &Student::GetSubjects)
    REGISTER_GETTER_END
};

Student student;
nlohmann::json jsonObject;

jsonObject = open_json::ToJson(student);
ASSERT_TRUE(jsonObject.is_object());
ASSERT_EQ(0, student.GetName().compare(jsonObject.at("name").template get<std::string>()));
ASSERT_EQ(student.GetId(), jsonObject.at("id").template get<long>());
ASSERT_TRUE(jsonObject.at("subjects").is_array());
auto itr = student.GetSubjects().begin();
for (auto &arrItem: jsonObject.at("subjects")) {
    ASSERT_EQ(0,  itr->compare(arrItem.template get<std::string>()));
    ++itr;
}
````

* ### Derived Class
````
class BaseClass {
private:
    double score;
    bool is_valid;

public:
    BaseClass() : score{24.5678}, is_valid{true} {
    }

    BaseClass(double d, bool b) : score{d}, is_valid{b} {
    }

    double GetScore() const {
        return score;
    }

    bool IsValid() const {
        return is_valid;
    }

    REGISTER_GETTER_START
    GETTER(BaseClass, double, "score", &BaseClass::GetScore),
    GETTER(BaseClass, bool, "is_valid", &BaseClass::IsValid)
    REGISTER_GETTER_END
};

class DerivedClass : public BaseClass {
private:
    long id;
    std::string name;

public:
    DerivedClass() : BaseClass(), id{10L}, name{"name1"} {
    }

    long GetId() const {
        return id;
    }

    std::string GetName() const {
        return name;
    }

    REGISTER_GETTER_INCLUDING_BASE_START(BaseClass)
    GETTER(DerivedClass, long, "id", &DerivedClass::GetId),
    GETTER(DerivedClass, std::string, "name", &DerivedClass::GetName)
    REGISTER_GETTER_INCLUDING_BASE_END
};

class DerivedClass2 : public DerivedClass {
private:
    int code;

public:
    DerivedClass2() : DerivedClass(), code{200} {
    }

    int GetCode() const {
        return code;
    }

    REGISTER_GETTER_INCLUDING_BASE_START(DerivedClass)
    GETTER(DerivedClass2, int, "code", &DerivedClass2::GetCode)
    REGISTER_GETTER_INCLUDING_BASE_END
};

BaseClass *base = new BaseClass();
DerivedClass *derived = new DerivedClass();
DerivedClass2 *derived2 new DerivedClass2();

// BaseClass Test
nlohmann::json jsonObject = open_json::ToJson(base);

ASSERT_TRUE(jsonObject.is_object());
ASSERT_DOUBLE_EQ(base->GetScore(), jsonObject.at("score").template get<double>());
ASSERT_TRUE(base->IsValid() == jsonObject.at("is_valid").template get<bool>());

// DerivedClass Test
 nlohmann::json jsonObject = open_json::ToJson(derived);

ASSERT_TRUE(jsonObject.is_object());
ASSERT_DOUBLE_EQ(derived->GetId(), jsonObject.at("id").template get<long>());
ASSERT_TRUE(0 ==  derived->GetName().compare(jsonObject.at("name").template get<std::string>()));
ASSERT_DOUBLE_EQ(derived->GetScore(), jsonObject.at("score").template get<double>());
ASSERT_TRUE(derived->IsValid() == jsonObject.at("is_valid").template get<bool>());

// DerivedClass2 Test
nlohmann::json jsonObject = open_json::ToJson(derived2);

ASSERT_TRUE(jsonObject.is_object());
ASSERT_EQ(derived2->GetCode(), jsonObject.at("code").template get<int>());
ASSERT_DOUBLE_EQ(derived2->GetId(), jsonObject.at("id").template get<long>());
ASSERT_TRUE(0 ==  derived2->GetName().compare(jsonObject.at("name").template get<std::string>()));
ASSERT_DOUBLE_EQ(derived2->GetScore(), jsonObject.at("score").template get<double>());
ASSERT_TRUE(derived2->IsValid() == jsonObject.at("is_valid").template get<bool>());
        
delete base;
delete derived;
delete derived2;            
````

* ### Derived Class Extending Serializable
````
class BaseClass2 : public open_json::Serializable {
private:
    double score;
    bool is_valid;

public:
    BaseClass2() : score{24.5678}, is_valid{true} {
    }

    [[nodiscard]]
    const nlohmann::json ToJson() override {
        return open_json::serializer::ToJsonObject(this);
    }

    double GetScore() const {
        return score;
    }

    bool IsValid() const {
        return is_valid;
    }

    REGISTER_GETTER_INCLUDING_BASE_START(open_json::Serializable)
    GETTER(BaseClass2, double, "score", &BaseClass2::GetScore),
    GETTER(BaseClass2, bool, "is_valid", &BaseClass2::IsValid)
    REGISTER_GETTER_INCLUDING_BASE_END
};

class DerivedClass2 : public BaseClass2 {
private:
    long id;
    std::string name;

public:
    DerivedClass2() : BaseClass2(), id{ 10 }, name{"name1"} {
    }

    [[nodiscard]]
    const nlohmann::json ToJson() override {
        return open_json::serializer::ToJsonObject(this);
    }

    long GetId() const {
        return id;
    }

    std::string GetName() const {
        return name;
    }

    REGISTER_GETTER_INCLUDING_BASE_START(BaseClass2)
    GETTER(DerivedClass2, long, "id", &DerivedClass2::GetId),
    GETTER(DerivedClass2, std::string, "name", &DerivedClass2::GetName)
    REGISTER_GETTER_INCLUDING_BASE_END
};

class DerivedClass3 : public DerivedClass2 {
private:
    int code;

public:
    DerivedClass3() : DerivedClass2(), code{200} {
    }

    [[nodiscard]]
    const nlohmann::json ToJson() override {
        return open_json::serializer::ToJsonObject(this);
    }

    int GetCode() const {
        return code;
    }

    REGISTER_GETTER_INCLUDING_BASE_START(DerivedClass2)
    GETTER(DerivedClass3, int, "code", &DerivedClass3::GetCode)
    REGISTER_GETTER_INCLUDING_BASE_END
};

class SerializeDerivedClassTest2 : public ::testing::Test {
public:
    BaseClass2 *base2;
    DerivedClass2 *derived2;
    DerivedClass3 *derived3;

    void SetUp() override {
        base2 = new BaseClass2();
        derived2 = new DerivedClass2();
        derived3 = new DerivedClass3();
    }

    void TearDown() override {
        delete base2;
        delete derived2;
        delete derived3;
    }
};

BaseClass2 *base2 = new BaseClass2();
DerivedClass2 *derived2 = new DerivedClass2();
DerivedClass3* derived3 = new DerivedClass3();

// Base class      
nlohmann::json jsonObject = base2->ToJson();

ASSERT_TRUE(jsonObject.is_object());
ASSERT_DOUBLE_EQ(base2->GetScore(), jsonObject.at("score").template get<double>());
ASSERT_TRUE(base2->IsValid() == jsonObject.at("is_valid").template get<bool>()); 

// Derived2 class
nlohmann::json jsonObject = derived2->ToJson();

ASSERT_TRUE(jsonObject.is_object());
ASSERT_DOUBLE_EQ(derived2->GetId(), jsonObject.at("id").template get<long>());
ASSERT_TRUE(0 == derived2->GetName().compare(jsonObject.at("name").template get<std::string>()));
ASSERT_DOUBLE_EQ(derived2->GetScore(), jsonObject.at("score").template get<double>());
ASSERT_TRUE(derived2->IsValid() == jsonObject.at("is_valid").template get<bool>());
            
// Derived3 class
nlohmann::json jsonObject = derived3->ToJson();

ASSERT_TRUE(jsonObject.is_object());
ASSERT_EQ(derived3->GetCode(), jsonObject.at("code").template get<int>());
ASSERT_DOUBLE_EQ(derived3->GetId(), jsonObject.at("id").template get<long>());
ASSERT_TRUE(0 == derived3->GetName().compare(jsonObject.at("name").template get<std::string>()));
ASSERT_DOUBLE_EQ(derived3->GetScore(), jsonObject.at("score").template get<double>());
ASSERT_TRUE(derived3->IsValid() == jsonObject.at("is_valid").template get<bool>());

delete base2;
delete derived2;
delete derived3;      
````

* ### Nested Class
````
class ClassA {
private:
    int id;
    std::string name;

public:
    ClassA() = default;
    virtual ~ClassA() = default;

    ClassA(int id, std::string name) : id{id}, name{name} {
    }

    int GetId() const {
        return id;
    }

    const std::string &GetName() const {
        return name;
    }

    REGISTER_GETTER_START
    GETTER(ClassA, int, "id", &ClassA::GetId),
    GETTER(ClassA, const std::string&, "name", &ClassA::GetName)
    REGISTER_GETTER_END
};

class ClassB {
private:
    ClassA m_obj;
    ClassA *m_objPtr;
    std::vector<ClassA> m_vecObj;
    std::vector<ClassA *> *m_vecObjPtr;

public:
    ClassB() {
        m_obj = ClassA(2, "object2");
        m_objPtr = new ClassA(3, "object3");
        m_vecObj.push_back(ClassA(4, "object4"));
        m_vecObj.push_back(ClassA(5, "object5"));
        m_vecObj.push_back(ClassA(6, "object6"));
        m_vecObjPtr = new std::vector<ClassA *>();
        m_vecObjPtr->push_back(new ClassA(7, "object7"));
        m_vecObjPtr->push_back(new ClassA(8, "object8"));
        m_vecObjPtr->push_back(new ClassA(9, "object9"));
    }

    virtual ~ClassB() {
        delete m_objPtr;
        for (auto p: *m_vecObjPtr) {
            if (p) {
                delete p;
            }
        }
        delete m_vecObjPtr;
    }
    
    const ClassA &GetObject() const {
        return m_obj;
    }

    const ClassA *GetObjectPtr() const {
        return m_objPtr;
    }

    const std::vector <ClassA> &GetVector() const {
        return m_vecObj;
    }

    const std::vector<ClassA *> *GetVectorPtr() const {
        return m_vecObjPtr;
    }

    // will be ignored in json object
    const ClassA *GetNullPtrObject() const {
        return nullptr;
    }

    // will be ignored in json object
    const int *GetNullPtrInt() const {
        return nullptr;
    }

    REGISTER_GETTER_START
    GETTER(ClassB, const ClassA&, "object", &ClassB::GetObject),
    GETTER(ClassB, const ClassA*, "object_ptr", &ClassB::GetObjectPtr),
    GETTER(ClassB, const std::vector <ClassA>&, "vector", &ClassB::GetVector),
    GETTER(ClassB, const std::vector<ClassA *>*, "vector_ptr", &ClassB::GetVectorPtr),
    GETTER(ClassB, const ClassA*, "null_object_ptr", &ClassB::GetNullPtrObject), // will be ignored
    GETTER(ClassB, const int*, "null_int_ptr", &ClassB::GetNullPtrInt) // will be ignored
    REGISTER_GETTER_END
};

class ClassC {
private:
    ClassB *objectB;

public:
    ClassC() {
        objectB = new ClassB();
    }

    virtual ~ClassC() {
        delete objectB;
    }

    const ClassB *GetObject() const {
        return objectB;
    }

    REGISTER_GETTER_START
    GETTER(ClassC, const ClassB*, "object", &ClassC::GetObject)
    REGISTER_GETTER_END
};

static void VerifyClassA(const ClassA &obj, const nlohmann::json &jsonObject) {
    ASSERT_TRUE(jsonObject.is_object());
    ASSERT_EQ(obj.GetId(), jsonObject.at("id").template get<int>());
    ASSERT_EQ(0, obj.GetName().compare(jsonObject.at("name").template get<std::string>()));
}

static void VerifyClassB(const ClassB &obj, const nlohmann::json &jsonObject) {
    ASSERT_TRUE(jsonObject.is_object());
    VerifyClassA(obj.GetObject(), jsonObject.at("object"));
    VerifyClassA(*obj.GetObjectPtr(), jsonObject.at("object_ptr"));

    const nlohmann::json &jsonVec = jsonObject.at("vector");
    ASSERT_TRUE(jsonVec.is_array());
    ASSERT_TRUE(jsonVec.size() == obj.GetVector().size());
    auto itr = obj.GetVector().begin();
    for (auto &arrItem: jsonVec) {
        VerifyClassA(*itr, arrItem);
        ++itr;
    }

    const nlohmann::json &jsonVecPtr = jsonObject.at("vector_ptr");
    ASSERT_TRUE(jsonVecPtr.is_array());
    ASSERT_TRUE(jsonVecPtr.size() == obj.GetVectorPtr()->size());
    auto itrp = obj.GetVectorPtr()->begin();
    for (auto &arrItem: jsonVecPtr) {
        VerifyClassA(**itrp, arrItem);
        ++itrp;
    }
}

static void VerifyClassC(const ClassC &obj, const nlohmann::json &jsonObject) {
    ASSERT_TRUE(jsonObject.is_object());
    VerifyClassB(*obj.GetObject(), jsonObject.at("object"));
}


ClassA *objectA = new ClassA(1, "object1");
ClassB *objectB = new ClassB();
ClassC *objectC = new ClassC();

// ClassA Test
nlohmann::json jsonObject;

jsonObject = open_json::ToJson(std::move(*objectA));
VerifyClassA(*objectA, jsonObject);

jsonObject = open_json::ToJson(*objectA);
VerifyClassA(*objectA, jsonObject);

jsonObject = open_json::ToJson(objectA);
VerifyClassA(*objectA, jsonObject);

// ClassB Test
nlohmann::json jsonObject;

jsonObject = open_json::ToJson(std::move(*objectB));
VerifyClassB(*objectB, jsonObject);

jsonObject = open_json::ToJson(*objectB);
VerifyClassB(*objectB, jsonObject);

jsonObject = open_json::ToJson(objectB);
VerifyClassB(*objectB, jsonObject);

// ClassC Test
nlohmann::json jsonObject;

jsonObject = open_json::ToJson(std::move(*objectC));
VerifyClassC(*objectC, jsonObject);

jsonObject = open_json::ToJson(*objectC);
VerifyClassC(*objectC, jsonObject);

jsonObject = open_json::ToJson(objectC);
VerifyClassC(*objectC, jsonObject);

delete objectA;
delete objectB;
delete objectC;
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
ASSERT_TRUE(jsonObject.template get<int>() == static_cast<int>(EnumTest::B));
````

* ### Serializing array
* ### Integer array
````
nlohmann::json jsonObject;

int intArr[] = {10, 20, 30, 40};

jsonObject = open_json::ToJson(intArr, 4);
ASSERT_TRUE(jsonObject.is_array());
ASSERT_TRUE(jsonObject.size() == 4);
int i = 0;
for (auto &arrItem: intArr) {
    ASSERT_EQ(arrItem, jsonObject[i++].template get<int>());
}

int *intPtr = new int[]{10, 20, 30, 40};

jsonObject = open_json::ToJson(intPtr, 4);
ASSERT_TRUE(jsonObject.is_array());
i = 0;
for (auto &arrItem: jsonObject) {
    ASSERT_EQ(intPtr[i++], arrItem.template get<int>());
}
delete[] intPtr;

int **intPtrArray = new int *[4]{new int(10), new int(20), new int(30), new int(4)};
jsonObject = open_json::ToJson(intPtrArray, 4);
ASSERT_TRUE(jsonObject.is_array());
ASSERT_TRUE(jsonObject.size() == 4);
i = 0;
for (auto &arrItem: jsonObject) {
    ASSERT_EQ(*(intPtrArray[i++]), arrItem.template get<int>());
}
delete[] intPtrArray;

int *intArrayPtr[4] = {new int(10), new int(20), new int(30), new int(4)};
jsonObject = open_json::ToJson(intArrayPtr, 4);
ASSERT_TRUE(jsonObject.is_array());
ASSERT_TRUE(jsonObject.size() == 4);
i = 0;
for (auto &arrItem: jsonObject) {
    ASSERT_EQ(*(intArrayPtr[i++]), arrItem.template get<int>());
}
for (auto p: intArrayPtr) {
    delete p;
}
````

* ### Char array
* ### string literal will be treated as character array;
````
nlohmann::json jsonObject;

// string literal will be treated as character array;
char *charPtr = "Hello World!";
jsonObject = open_json::ToJson(charPtr, strlen(charPtr));
ASSERT_TRUE(jsonObject.is_array());
ASSERT_TRUE(jsonObject.size() == strlen(charPtr));
int i = 0;
for (auto &arrItem: jsonObject) {
    ASSERT_EQ(charPtr[i++], arrItem.template get<char>());
}

char charArr[] = {'a', 'b', 'c', 'd'};
jsonObject = open_json::ToJson(charArr, 4);
ASSERT_TRUE(jsonObject.is_array());
ASSERT_TRUE(jsonObject.size() == 4);
i = 0;
for (auto &arrItem: jsonObject) {
    ASSERT_EQ(charArr[i++], arrItem.template get<char>());
}
````

* ### std::string array
````
nlohmann::json jsonObject;

std::string strArray[] = {"Hi there!", "How are you?", "How is going?"};
jsonObject = open_json::ToJson(strArray, 3);
ASSERT_TRUE(jsonObject.is_array());
ASSERT_TRUE(jsonObject.size() == 3);
int i = 0;
for (auto &arrItem: jsonObject) {
    ASSERT_EQ(0, strArray[i++].compare(arrItem.template get<std::string>()));
}

std::string *strPtrArray[] = {new std::string("Hi there!"), new std::string("How are you?"), new std::string("How is going?")};
jsonObject = open_json::ToJson(strArray, 3);
ASSERT_TRUE(jsonObject.is_array());
ASSERT_TRUE(jsonObject.size() == 3);
i = 0;
for (auto &arrItem: jsonObject) {
    ASSERT_EQ(0, strPtrArray[i++]->compare(arrItem.template get<std::string>()));
}
for(auto p : strPtrArray) {
    delete p;
}

std::string **strArrayPtr = new std::string*[] {new std::string("Hi there!"), new std::string("How are you?"), new std::string("How is going?")};
jsonObject = open_json::ToJson(strArray, 3);
ASSERT_TRUE(jsonObject.is_array());
ASSERT_TRUE(jsonObject.size() == 3);
i = 0;
for (auto &arrItem: jsonObject) {
    ASSERT_EQ(0, strArrayPtr[i++]->compare(arrItem.template get<std::string>()));
}
delete[] strArrayPtr;
````

* ### Custom object array
````
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

    void setGrade(std::string grade) {
        this->grade = grade;
    }

    double GetScore() const {
        return score;
    }

    const std::string &GetGrade() const {
        return grade;
    }

    void operator=(const Value &v) {
        this->score = v.score;
        this->grade = v.grade;
    }

    REGISTER_GETTER_START
    GETTER(Value, double, "score", &Value::GetScore),
    GETTER(Value, const std::string&, "grade", &Value::GetGrade)
    REGISTER_GETTER_END
};
       
nlohmann::json jsonObject;

Value valueArr[3] = { {80, "A+"}, {70, "A"}, {60, "A-"} };

jsonObject = open_json::ToJson(valueArr, 3);
ASSERT_TRUE(jsonObject.is_array());
ASSERT_TRUE(jsonObject.size() == 3);

int i = 0;
for(auto &arrItem : jsonObject) {
    ASSERT_DOUBLE_EQ(valueArr[i].GetScore(), arrItem.at("score").template get<double>());
    ASSERT_EQ(0, valueArr[i].GetGrade().compare(arrItem.at("grade").template get<std::string>()));
    ++i;
}

Value *ptrArr1 = new Value[] { {80, "A+"}, {70, "A"}, {60, "A-"} };

jsonObject = open_json::ToJson(ptrArr1, 3);
ASSERT_TRUE(jsonObject.is_array());
ASSERT_TRUE(jsonObject.size() == 3);
i = 0;
for(auto &arrItem : jsonObject) {
    ASSERT_DOUBLE_EQ(ptrArr1[i].GetScore(), arrItem.at("score").template get<double>());
    ASSERT_EQ(0, ptrArr1[i].GetGrade().compare(arrItem.at("grade").template get<std::string>()));
    ++i;
}
delete[] ptrArr1;

Value **ptrArr2 = new Value*[] { new Value(80, "A+"), new Value(70, "A"), new Value(60, "A-") };
jsonObject = open_json::ToJson(ptrArr2, 3);
ASSERT_TRUE(jsonObject.is_array());
ASSERT_TRUE(jsonObject.size() == 3);
i = 0;
for(auto &arrItem : jsonObject) {
    ASSERT_DOUBLE_EQ(ptrArr2[i]->GetScore(), arrItem.at("score").template get<double>());
    ASSERT_EQ(0, ptrArr2[i]->GetGrade().compare(arrItem.at("grade").template get<std::string>()));
    ++i;
}
delete[] ptrArr2;

Value *ptrArr3[3] = { new Value(80, "A+"), new Value(70, "A"), new Value(60, "A-") };
jsonObject = open_json::ToJson(ptrArr3, 3);
ASSERT_TRUE(jsonObject.is_array());
ASSERT_TRUE(jsonObject.size() == 3);
i = 0;
for(auto &arrItem : jsonObject) {
    ASSERT_DOUBLE_EQ(ptrArr3[i]->GetScore(), arrItem.at("score").template get<double>());
    ASSERT_EQ(0, ptrArr3[i]->GetGrade().compare(arrItem.at("grade").template get<std::string>()));
    ++i;
}
for (auto p: ptrArr3) {
    delete p;
}
````


* ### Map
````
std::map<std::string, int> mapObj;
mapObj["first"] = 1;
mapObj["second"] = 2;
mapObj["third"] = 3;
                
jsonObject = open_json::ToJson(mapObj);
ASSERT_TRUE(jsonObject.is_object());
ASSERT_EQ(mapObj.at("first"), jsonObject.at("first").template get<int>());
ASSERT_EQ(mapObj.at("second"), jsonObject.at("second").template get<int>());
ASSERT_EQ(mapObj.at("third"), jsonObject.at("third").template get<int>());                      
````

* ### Map&#42;
````
std::map<std::string, std::string> *mapPtr;
(*mapPtr)["first"] = "one";
(*mapPtr)["second"] = "two";
(*mapPtr)["third"] = "three";

jsonObject = open_json::ToJson(mapPtr);
ASSERT_EQ(0, mapPtr->at("first").compare(jsonObject.at("first").template get<std::string>()));
ASSERT_EQ(0, mapPtr->at("second").compare(jsonObject.at("second").template get<std::string>()));
ASSERT_EQ(0, mapPtr->at("third").compare(jsonObject.at("third").template get<std::string>()));
delete mapPtr;
````

* ### Map of object
````
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

    void setGrade(std::string grade) {
        this->grade = grade;
    }

    double GetScore() const {
        return score;
    }

    const std::string &GetGrade() const {
        return grade;
    }

    void operator=(const Value &v) {
        this->score = v.score;
        this->grade = v.grade;
    }

    REGISTER_GETTER_START
    GETTER(Value, double, "score", &Value::GetScore),
    GETTER(Value, const std::string&, "grade", &Value::GetGrade)
    REGISTER_GETTER_END
};

std::map<std::string, Value> mapObject;

mapObject.insert(std::pair<std::string, Value>("first", {80, "A+"}));
mapObject.insert(std::pair<std::string, Value>("second", {70, "A"}));
mapObject.insert(std::pair<std::string, Value>("third", {60, "A-"}));

jsonObject = open_json::ToJson(mapObject);
ASSERT_TRUE(jsonObject.is_object());
ASSERT_DOUBLE_EQ(mapObject.at("first").GetScore(), jsonObject["first"].at("score").template get<double>());
ASSERT_EQ(mapObject.at("first").GetGrade(), jsonObject["first"].at("grade").template get<std::string>());

ASSERT_DOUBLE_EQ(mapObject.at("second").GetScore(), jsonObject["second"].at("score").template get<double>());
ASSERT_EQ(mapObject.at("second").GetGrade(), jsonObject["second"].at("grade").template get<std::string>());

ASSERT_DOUBLE_EQ(mapObject.at("third").GetScore(), jsonObject["third"].at("score").template get<double>());
ASSERT_EQ(mapObject.at("third").GetGrade(), jsonObject["third"].at("grade").template get<std::string>());                
````
