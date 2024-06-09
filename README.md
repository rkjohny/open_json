# open_json
A modern c++ library to serialize and deserialize c++ objects to and from Json string
* Free, open source, lightweight, header-only json serializer/deserializer for c++ objects
* nlohmann::json library has been used:
  * to parse json string and building nlohmann::json object
  * to serialize nlohmann::json object to string
* This library converts nlohmann::json objects to and from c++ objects
  * Serialization:
    * step1: convert c++ object to nlohmann::json objects. <b>(done by this library)</b>
    * step2: convert nlohmann::json to std::string (by nlohmann::json library)
  * Deserialization:
    * step1: parse std::string and create nlohmann::json object (by nlohmann::json library)
    * step2: convert nlohmann::json objects to c++ objects. <b>(done by this library)</b>
* nlohmann::json library can be replaced by any other json library like <b>cpprest::json</b>

## Toolset:
* MinGW64 version 11.0 w64

## Language Standard:
* C++17

## Build tool:
* cmake version 3.28.1 (bundled with MinGW64)
* ninja (bundled with MinGW64)

## Debugger:
* GDB 14.1

## Dependencies:
* <a href="https://github.com/gabime/spdlog">spdlog</a>
* <a href="https://github.com/nlohmann/json">nlohmann-json</a>
* <a href="https://github.com/boostorg/boost">boost.thread</a>
* <a href="https://github.com/boostorg/boost">boost.optional</a>

## Prepare environment:

* ### Install MSYS2 (64 bit):
  * https://www.msys2.org

* ### Install MinGW64:
  * pacman -S mingw-w64-ucrt-x86_64-toolchain

* ### Install spdlog:
  * pacman -S mingw-w64-x86_64-spdlog

* ### Install nlohmann json library:
  * pacman -S mingw-w64-x86_64-nlohmann-json

* ### Install boost:
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
