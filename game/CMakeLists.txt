cmake_minimum_required(VERSION 3.9)
project(game)

include_directories(${PROJECT_SOURCE_DIR}/includes)

file(GLOB SOURCES "main.cpp" "src/*.cpp")

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME})
