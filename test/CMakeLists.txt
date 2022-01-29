
project(relational_simulator_test)


# ---------------------------------------------------------------------------------------
# Core test
# ---------------------------------------------------------------------------------------
add_executable(${PROJECT_NAME}_core
    core/world_test.cpp core/entity_test.cpp
    core/trait_test.cpp core/point_test.cpp)

target_link_libraries(${PROJECT_NAME}_core
    PRIVATE
        rela::core
        GTest::gtest
        GTest::gtest_main
)

add_test(${PROJECT_NAME}_core ${PROJECT_NAME}_core)

# ---------------------------------------------------------------------------------------
# Utility test
# ---------------------------------------------------------------------------------------