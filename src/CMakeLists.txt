
project(relational_simulator_main)


# Core library, which contains code for some of the core game concepts
add_subdirectory(core)

# Utility library, which contains things like logging, exceptions, templates etc.
add_subdirectory(utility)

# ---------------------------------------------------------------------------------------
# Main target
# ---------------------------------------------------------------------------------------
add_executable(${PROJECT_NAME} main.cpp)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${PROJECT_SOURCE_DIR}
)

if(NOT CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(${PROJECT_NAME} PUBLIC NDEBUG)
endif()

target_link_libraries(${PROJECT_NAME} 
    PRIVATE
    rela::core
    rela::utility
)