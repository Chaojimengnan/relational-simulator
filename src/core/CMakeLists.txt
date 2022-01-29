
project(relational_simulator_core)


# ---------------------------------------------------------------------------------------
# Core Library
# ---------------------------------------------------------------------------------------
add_library(${PROJECT_NAME} STATIC 
    entity.cpp world.cpp
    trait.cpp point.cpp
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${PROJECT_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC 
        rela::utility
)

add_library(rela::core ALIAS ${PROJECT_NAME})