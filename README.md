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

* ### Primitive char and char*
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

* ### string and string*
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