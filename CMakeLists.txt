cmake_minimum_required(VERSION 3.28)

set(LIB_OPEN_JSON open_json)

project(${LIB_OPEN_JSON} CXX)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_BUILD_TYPE Debug)

add_compile_options(-c -O1 -g3 -Wall -Wextra -Wno-unused-variable -Wno-unused-parameter -Wno-write-strings -Wno-unused-local-typedefs -std=c++17)


# Set the output directory for static libraries
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)


set (PROJECT_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set (PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)


if(TARGET ${PROJECT_NAME})
    message("libopen_json is already defined")
else()
    message("building libopen_json ...")

    # Find spdlog
    find_package(spdlog REQUIRED)

    # Find nlohmann-json
    find_package(nlohmann_json REQUIRED)

    # Find Boost.Thread
    set(Boost_USE_STATIC_LIBS OFF) # Enable dynamic linking
    set(Boost_USE_MULTITHREADED ON)
    set(Boost_USE_STATIC_RUNTIME OFF)
    find_package(Boost REQUIRED COMPONENTS thread)

    # including header files
    include_directories(${PROJECT_INCLUDE_DIR})

    file(GLOB LIB_OPEN_JSON_HEADER_FILES ${PROJECT_INCLUDE_DIR}/*.h)
    file(GLOB LIB_OPEN_JSON_SOURCE_FILES ${PROJECT_SOURCE_DIR}/*.cpp)

    #creating target libJson
    add_library(${PROJECT_NAME} STATIC ${LIB_OPEN_JSON_HEADER_FILES} ${LIB_OPEN_JSON_SOURCE_FILES})

    if(spdlog_FOUND)
        # Link the spdlog library
        target_link_libraries(${PROJECT_NAME} PRIVATE spdlog)
        # Include spdlog headers
        target_include_directories(${PROJECT_NAME} PRIVATE ${spdlog_INCLUDE_DIR})
    else ()
        message(FATAL_ERROR "Could not find spdlog libraries.")
    endif ()

    if (nlohmann_json_FOUND)
        # Link the nlohmann_json library
        target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json)
        # Include nlohmann_json headers
        target_include_directories(${PROJECT_NAME} PRIVATE ${nlohmann_json_INCLUDE_DIRS})
    else ()
        message(FATAL_ERROR "Could not find nlohmann_json libraries.")
    endif ()

    if (BOOST_FOUND)
        # Link the Boost.Thread library
        target_link_libraries(${PROJECT_NAME} PRIVATE Boost::thread)
        # Include Boost headers
        target_include_directories(${PROJECT_NAME} PRIVATE ${boost_INCLUDE_DIR})
    else ()
        message(FATAL_ERROR "Could not find boost.thread libraries.")
    endif ()
endif()

