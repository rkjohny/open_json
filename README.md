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
* ### primitive integer

<div class="highlight highlight-source-c++ notranslate position-relative overflow-auto" dir="auto">
<pre>
<span class="pl-k">#include</span><span class="pl-s"><span class="pl-pds">&lt;</span>open_json.h<span class="pl-pds">&gt;</span></span>

<div class="pl-c">
nlohmann::json jsonObject;

//serialize integer

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