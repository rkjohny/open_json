cmake_minimum_required(VERSION 3.28)

set(LIB_OPEN_JSON open_json)

project(${LIB_OPEN_JSON} CXX)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_BUILD_TYPE Debug)

add_compile_options(-c -O1 -g3 -Wall -Wextra -Wno-unused-variable -Wno-unused-parameter -Wno-write-strings -Wno-unused-local-typedefs -std=c++17)

set(EXTERNAL_DEPENDENCIES ${CMAKE_CURRENT_SOURCE_DIR}/lib)

set (PROJECT_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set (PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

# exposing the header location to be included by other targets
#set(LIB_OPEN_JSON_INCLUDE_DIR ${LIB_OPEN_JSON_INCLUDE_DIR})
#set(LIB_OPEN_JSON_INCLUDE_DIR ${LIB_OPEN_JSON_INCLUDE_DIR} PARENT_SCOPE)

if(TARGET ${PROJECT_NAME})
    message("libopen_json is already defined")
else()
    message("building libopen_json ...")

    # Find spdlog
    find_package(spdlog REQUIRED)

    # Find nlohmann-json
    find_package(nlohmann_json REQUIRED)

# Set the path to the MSYS2 mingw64 or mingw32
#    if (MINGW)
#        set(BOOST_ROOT "C:/msys64/mingw64")
#        # For 32-bit MSYS2, use: set(BOOST_ROOT "C:/msys64/mingw32")
#    endif()

    # Find Boost.Thread
    find_package(Boost REQUIRED COMPONENTS thread)

    # Install Guidelines Support Library (GSL) by Microsoft
    include(FetchContent)
    FetchContent_Declare(
            gsl
            GIT_REPOSITORY https://github.com/microsoft/GSL.git
            GIT_TAG main # Use the main branch or specify a specific tag/commit
    )
    FetchContent_MakeAvailable(gsl)

    # including header files
    include_directories(${PROJECT_INCLUDE_DIR})

    file(GLOB LIB_OPEN_JSON_HEADER_FILES ${PROJECT_INCLUDE_DIR}/*.h)
    file(GLOB LIB_OPEN_JSON_TYPE_TRAITS_HEADER_FILES ${PROJECT_INCLUDE_DIR}/type_traits/*.h)
    file(GLOB LIB_OPEN_JSON_SOURCE_FILES ${PROJECT_SOURCE_DIR}/*.cpp)

    #creating target libJson
    add_library(${PROJECT_NAME} STATIC ${LIB_OPEN_JSON_HEADER_FILES} ${LIB_OPEN_JSON_TYPE_TRAITS_HEADER_FILES} ${LIB_OPEN_JSON_SOURCE_FILES})

    # Link the spdlog library
    target_link_libraries(${PROJECT_NAME} PRIVATE spdlog)

    # Include spdlog headers
    target_include_directories(${PROJECT_NAME} PRIVATE ${spdlog_INCLUDE_DIR})

    # Link the nlohmann_json library
    target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json)

    # Include nlohmann_json headers
    target_include_directories(${PROJECT_NAME} PRIVATE $nlohmann_json_INCLUDE_DIRS})

    # Link the Boost.Thread library
    target_link_libraries(${PROJECT_NAME} PRIVATE Boost::thread)

    # Include Boost headers
    target_include_directories(${PROJECT_NAME} PRIVATE ${boost_INCLUDE_DIR})

    # Link GSL
    target_link_libraries(${PROJECT_NAME} PRIVATE Microsoft.GSL::GSL)

    # Include GSL headers
    target_include_directories(${PROJECT_NAME} PRIVATE ${gsl_INCLUDE_DIR})

endif()
