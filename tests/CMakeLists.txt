cmake_minimum_required(VERSION VERSION 3.28)

set(PROJECT_NAME open_json_test)

project(${PROJECT_NAME} CXX)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_BUILD_TYPE Debug)

add_compile_options(-c -O1 -g3 -Wall -Wextra -Wno-unused-variable -Wno-unused-parameter -Wno-write-strings -Wno-unused-local-typedefs -std=c++17)

# Set the output directory for executables
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../build)

# setting header and source file location
set(PROJECT_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

set(LIB_OPEN_JSON_INCLUDE_DIR, ${CMAKE_CURRENT_SOURCE_DIR}/../include)


# Find GTest
find_package(GTest REQUIRED)

# Find nlohmann-json
find_package(nlohmann_json REQUIRED)

# Find Boost.Thread
set(Boost_USE_STATIC_LIBS OFF) # Enable dynamic linking
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost REQUIRED COMPONENTS system)


#link_directories(${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
#
#find_library(open_json REQUIRED)

# including header files for this target
include_directories(${PROJECT_INCLUDE_DIR})

# include open_json header files
include_directories(${LIB_OPEN_JSON_INCLUDE_DIR})


file(GLOB OPEN_JSON_TEST_HEADER ${PROJECT_INCLUDE_DIR}/*.h)
file(GLOB OPEN_JSON_TEST_SRCS ${PROJECT_SOURCE_DIR}/*.cpp)


# creating JonTest target
add_executable(${PROJECT_NAME} ${OPEN_JSON_TEST_HEADER} ${OPEN_JSON_TEST_SRCS})


#if (OPEN_JSON_FOUND)
#    target_link_libraries(${PROJECT_NAME} ${GTEST_LIBRARIES} open_json)
#    # Include nlohmann_json headers
#    target_include_directories(${PROJECT_NAME} PRIVATE ${open_json_INCLUDE_DIRS})
#else ()
#    message(FATAL_ERROR "Could not find open_json library.")
#endif ()


if (nlohmann_json_FOUND)
    target_link_libraries(${PROJECT_NAME} nlohmann_json)
    # Include nlohmann_json headers
    target_include_directories(${PROJECT_NAME} PRIVATE ${nlohmann_json_INCLUDE_DIRS})
else ()
    message(FATAL_ERROR "Could not find nlohmann_json library.")
endif ()

if (GTEST_FOUND)
    target_link_libraries(${PROJECT_NAME} ${GTEST_LIBRARIES} GTest::Main GTest::GTest)
    target_include_directories(${PROJECT_NAME} PRIVATE ${GTEST_INCLUDE_DIRS})
else ()
    message(FATAL_ERROR "Could not find Gtest library.")
endif ()

if(BOOST_FOUND)
    target_link_libraries(${PROJECT_NAME} ${GTEST_LIBRARIES} Boost::system)
    target_link_libraries(${PROJECT_NAME} ${GTEST_LIBRARIES} pthread)
    target_include_directories(${PROJECT_NAME} PRIVATE ${boost_INCLUDE_DIR})
else ()
    message(FATAL_ERROR "Could not find Boost library.")
endif ()
