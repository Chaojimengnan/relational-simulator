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
    set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Choose Release or Debug" FORCE)
endif()

if(NOT CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(${PROJECT_NAME}_lib PUBLIC NDEBUG)
endif()

message(STATUS "CMAKE_BUILD_TYPE:${CMAKE_BUILD_TYPE}")

project(relational_simulator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ---------------------------------------------------------------------------------------
# Third party and Project and Unit test
# ---------------------------------------------------------------------------------------

# JSON support
find_package(nlohmann_json CONFIG REQUIRED)

# Logging support
find_package(spdlog CONFIG REQUIRED)

# Project
add_subdirectory(src)

# Unit test
if (TEST)
    find_package(GTest CONFIG REQUIRED)
    enable_testing()
    add_subdirectory(test)
endif()