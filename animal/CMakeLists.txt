cmake_minimum_required(VERSION 3.9)
project(animal)

include_directories(${PROJECT_SOURCE_DIR}/includes)
file(GLOB SOURCES "*.cpp")
add_library(applib SHARED ${SOURCES})
add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} applib)
