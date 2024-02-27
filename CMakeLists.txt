cmake_minimum_required(VERSION 3.9)

project(hello_world)

include_directories(${PROJECT_SOURCE_DIR})
# add_library(applib foo.cpp)
add_executable(app main.cpp foo.cpp)
# target_link_libraries(app applib)