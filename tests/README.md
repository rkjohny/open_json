# open_json_test
Unit testing of open_json using Google Test <b>(gtest or googletest)</b>

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
* <a href="https://github.com/google/googletest">gtest</a>
* <a href="https://github.com/boostorg/boost">boost.system</a>
* <a href="https://github.com/boostorg/boost">boost.optional</a>
* pthread

## Prepare environment:

* ### Install MSYS2 (64 bit):
  * https://www.msys2.org

* ### Install MinGW64:
  * pacman -S mingw-w64-ucrt-x86_64-toolchain

* ### Install gtest:
  * pacman -S mingw-w64-x86_64-gtest

* ### Install boost (installing boost::optional and boost::system are sufficient):
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
