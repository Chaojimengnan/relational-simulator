cmake_minimum_required(VERSION 3.5)

# ---------------------------------------------------------------------------------------
# Build options
# ---------------------------------------------------------------------------------------
option(TEST "Enable Unit Test" "ON")
option(USING_VCPKG "Using Vcpkg to management packages" "ON")


# ---------------------------------------------------------------------------------------
# Config
# ---------------------------------------------------------------------------------------
if (USING_VCPKG)
    message(STATUS "Using vcpkg")
    set (OPTION_DEPENDENCIES "")
    if (TEST)
        message(STATUS "Enable unit test")
        set(OPTION_DEPENDENCIES "${DEPENDENCIES} ,\"gtest\"")
    endif()

    configure_file(${CMAKE_SOURCE_DIR}/vcpkg/vcpkg.json.in ${CMAKE_SOURCE_DIR}/vcpkg/vcpkg.json)

    set(VCPKG_MANIFEST_DIR ${CMAKE_SOURCE_DIR}/vcpkg)
endif()

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose Release or Debug" FORCE)
endif()


message(STATUS "CMAKE_BUILD_TYPE:${CMAKE_BUILD_TYPE}")

project(relational_simulator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# JSON support
find_package(nlohmann_json CONFIG REQUIRED)
# Logging support
find_package(spdlog CONFIG REQUIRED)

# ---------------------------------------------------------------------------------------
# Core Library
# ---------------------------------------------------------------------------------------
add_library(${PROJECT_NAME}_lib STATIC 
    src/entity.cpp src/world.cpp src/log.cpp
    src/trait.cpp src/utility.cpp src/exception.cpp
    src/point.cpp
)

target_include_directories(${PROJECT_NAME}_lib
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(${PROJECT_NAME}_lib 
    PUBLIC 
        nlohmann_json nlohmann_json::nlohmann_json
        spdlog::spdlog
)

if(NOT CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(${PROJECT_NAME}_lib PUBLIC NDEBUG)
endif()

# ---------------------------------------------------------------------------------------
# Main target
# ---------------------------------------------------------------------------------------
add_executable(${PROJECT_NAME} src/main.cpp)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(${PROJECT_NAME} 
    PRIVATE
    ${PROJECT_NAME}_lib
)

# ---------------------------------------------------------------------------------------
# Unit test
# ---------------------------------------------------------------------------------------
if (TEST)
    find_package(GTest CONFIG REQUIRED)
    enable_testing()
    add_executable(${PROJECT_NAME}_test
        test/world_test.cpp test/entity_test.cpp
        test/trait_test.cpp test/point_test.cpp)

    target_link_libraries(${PROJECT_NAME}_test
        PRIVATE
            ${PROJECT_NAME}_lib
            GTest::gtest
            GTest::gtest_main
    )

    add_test(${PROJECT_NAME}_test ${PROJECT_NAME}_test)
endif()