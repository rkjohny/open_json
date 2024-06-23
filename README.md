# open_json
A modern c++ library to serialize and deserialize c++ objects to and from <a href = "https://github.com/nlohmann/json"> nlhoman::json</a> object.
* Free, open source, lightweight, headers-only json serializer/deserializer for c++ objects using <b>getter</b>, <b>setter</b> and <b>default constructor</b>.
* Just include the header files or only the <b>open_json.h</b> file (in include directory) in your project
* <b>This library converts nlohmann::json objects to and from c++ objects</B>
  * Serialization:
    * step1: convert c++ object to nlohmann::json objects.
  * Deserialization:
    * step1: convert nlohmann::json objects to c++ objects.
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
    * #### install dependencies of boost:
      * ##### install python:
        * pacman -S mingw-w64-x86_64-python
        * pacman -S mingw-w64-x86_64-python-numpy
      * ##### install bzip2:
        * pacman -S mingw-w64-x86_64-bzip2
      * ##### install gcc-libs:
        * pacman -S mingw-w64-x86_64-gcc-libs
      * ##### install icu:
        * pacman -S mingw-w64-x86_64-icu
      * ##### install xz:
        * pacman -S mingw-w64-x86_64-xz
      * ##### install zlib:
        * pacman -S mingw-w64-x86_64-zlib
      * ##### install zstd:
        * pacman -S mingw-w64-x86_64-zstd

# Example:

* ## Serializing
* ### Primitive integer

<div class="highlight highlight-source-c++ notranslate position-relative overflow-auto" dir="auto">
<pre>
<span class="pl-k">#include</span><span class="pl-s"><span class="pl-pds">&lt;</span>open_json.h<span class="pl-pds">&gt;</span></span>

<div class="pl-c">
nlohmann::json jsonObject;

jsonObject = open_json::ToJson(10);
ASSERT_EQ(10, jsonObject.template get&lt;int&gt;());

int intValue = 10;
jsonObject = open_json::ToJson(intValue);
ASSERT_EQ(intValue, jsonObject.template get&lt;int&gt;());


int &#42;ptrInt = new int(-45);
jsonObject = open_json::ToJson(ptrInt);
ASSERT_EQ(*ptrInt, jsonObject.template get&lt;int&gt;());
delete ptrInt;

int &#42;&#42;ptr2Int = new int&#42;(new int(-50));
jsonObject = open_json::ToJson(ptr2Int);
ASSERT_EQ(**ptr2Int, jsonObject.template get&lt;int&gt;());
delete &#42;ptr2Int;
delete ptr2Int;

</div>
</pre>
</div>

* ### Primitive double
<div class="highlight highlight-source-c++ notranslate position-relative overflow-auto" dir="auto">
<pre>
<span class="pl-k">#include</span><span class="pl-s"><span class="pl-pds">&lt;</span>open_json.h<span class="pl-pds">&gt;</span></span>

<div class="pl-c">
nlohmann::json jsonObject;

jsonObject = open_json::ToJson(10.51);
ASSERT_DOUBLE_EQ(10.51, jsonObject.template get&lt;double&gt;());

double decimalVal = 10.51;
jsonObject = open_json::ToJson(decimalVal);
ASSERT_DOUBLE_EQ(decimalVal, jsonObject.template get&lt;double&gt;());

const double &#42;decimalPtr2 = &decimalVal;
jsonObject = open_json::ToJson(decimalPtr2);
ASSERT_DOUBLE_EQ(&#42;decimalPtr2, jsonObject.template get&lt;double&gt;());

const double &#42; const &#42;decimalPtr5 = new double&#42;(new double(-30.51));
jsonObject = open_json::ToJson(decimalPtr5);
ASSERT_DOUBLE_EQ(&#42;&#42;decimalPtr5, jsonObject.template get&lt;double&gt;());
delete &#42;decimalPtr5;
delete decimalPtr5;

</div>
</pre>
</div>

* ### Primitive char and char&#42;
<div class="highlight highlight-source-c++ notranslate position-relative overflow-auto" dir="auto">
<pre>
<span class="pl-k">#include</span><span class="pl-s"><span class="pl-pds">&lt;</span>open_json.h<span class="pl-pds">&gt;</span></span>

<div class="pl-c">
nlohmann::json jsonObject;
int intVal = 'A';
char charValue = 'A';

jsonObject = open_json::ToJson(charValue);
ASSERT_EQ(intVal, jsonObject.template get&lt;int&gt;());
ASSERT_EQ(charValue, jsonObject.template get&lt;char&gt;());

unsigned char ucharVal = 'A';
jsonObject = open_json::ToJson(ucharVal);
ASSERT_EQ(intVal, jsonObject.template get&lt;int&gt;());
ASSERT_EQ(ucharVal, jsonObject.template get&lt;unsigned char&gt;());

char &#42;ptr1 = "Hello world!";
jsonObject = open_json::ToJson(ptr1);
ASSERT_EQ(ptr1, jsonObject.template get&lt;std::string&gt;());

char &#42;&#42;ptr2 = &ptr1;
jsonObject = open_json::ToJson(ptr2);
ASSERT_EQ(&#42;ptr2, jsonObject.template get&lt;std::string&gt;());

</div>
</pre>
</div>

* ### Primitive string and string&#42;
<div class="highlight highlight-source-c++ notranslate position-relative overflow-auto" dir="auto">
<pre>
<span class="pl-k">#include</span><span class="pl-s"><span class="pl-pds">&lt;</span>open_json.h<span class="pl-pds">&gt;</span></span>

<div class="pl-c">
nlohmann::json jsonObject;

std::string str = "Hello World!";
jsonObject = open_json::ToJson(str);
ASSERT_EQ(0, str.compare(jsonObject.template get&lt;std::string&gt;()));

const std::string str2 = "C++ is awesome!";
jsonObject = open_json::ToJson(std::move(str2));
ASSERT_EQ(0, str2.compare(jsonObject.template get&lt;std::string&gt;()));

std::string &#42;str3 = &str;
jsonObject = open_json::ToJson(str3);
ASSERT_EQ(0, str3->compare(jsonObject.template get&lt;std::string&gt;()));

std::string &#42;&#42;str7 = new std::string&#42;(new std::string("Hi there!"));
jsonObject = open_json::ToJson(str7);
ASSERT_EQ(0, (&#42;str7)->compare(jsonObject.template get&lt;std::string&gt;()));
delete *str7;
delete str7;

</div>
</pre>
</div>