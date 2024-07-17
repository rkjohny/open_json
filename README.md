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

* ### Primitive char and char&#42;
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

char *ptr1 = "Hello world!";
jsonObject = open_json::ToJson(ptr1);
ASSERT_EQ(ptr1, jsonObject.template get<std::string>());

char **ptr2 = &ptr1;
jsonObject = open_json::ToJson(ptr2);
ASSERT_EQ(*ptr2, jsonObject.template get<std::string>());
````

* ### string and string&#42;
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

* ### Vector&lt;char&#42;&gt;
````
std::vector<char *> m_cities;

char *p = new char[100];
strcpy(p, "New York");
m_cities.push_back(p);

p = new char[100];
strcpy(p, "Boston");
m_cities.push_back(p);

p = new char[100];
strcpy(p, "Paris");
m_cities.push_back(p);

nlohmann::json jsonArr = open_json::ToJson(m_cities);
ASSERT_TRUE(jsonArr.is_array());
ASSERT_TRUE(jsonArr.size() == m_cities.size());
auto itr = m_cities.begin();
for (auto &arrItem: jsonArr) {
    ASSERT_EQ(0, std::string(*itr).compare(arrItem.template get<string>()));
    ++itr;
}

for (auto p: m_cities) {
    delete p;
}
````
#### For more test cases of vector types look into file <a href="./tests/src/SerializeVectorTest.cpp">SerializeVectorTest.cpp</a>

