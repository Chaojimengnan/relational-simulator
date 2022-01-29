
project(relational_simulator_utility)


# ---------------------------------------------------------------------------------------
# Utility Library
# ---------------------------------------------------------------------------------------
add_library(${PROJECT_NAME} STATIC 
    exception.cpp log.cpp utility.cpp
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${PROJECT_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC 
        nlohmann_json nlohmann_json::nlohmann_json
        spdlog::spdlog
)

add_library(rela::utility ALIAS ${PROJECT_NAME})