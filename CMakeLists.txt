cmake_minimum_required(VERSION 3.9)
project(embed_cpp)

add_executable(${PROJECT_NAME} main.cpp)

configure_file("${PROJECT_SOURCE_DIR}/config.json" "${PROJECT_BINARY_DIR}/config.json" COPYONLY)

add_subdirectory( utils/json )

target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json)