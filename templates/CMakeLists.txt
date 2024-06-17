cmake_minimum_required(VERSION 3.9)
project(templates)

include_directories(${PROJECT_SOURCE_DIR}/includes)

file(GLOB SOURCES "*.cpp")

add_library(applib SHARED main.cpp storageTemplates.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} applib)
