cmake_minimum_required(VERSION 3.9)
project(threads)

include_directories(${PROJECT_SOURCE_DIR}/includes)

file(GLOB SOURCES "main.cpp" "src/*.cpp")

add_executable(${PROJECT_NAME} ${SOURCES})

add_executable(main conditionVariable.cpp)

target_link_libraries(${PROJECT_NAME} pthread)
