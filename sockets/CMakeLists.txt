cmake_minimum_required(VERSION 3.9)
project(sockets)

include_directories(${PROJECT_SOURCE_DIR})

add_executable(server server.cpp)

add_executable(client client.cpp)

add_executable(clientTwo clientTwo.cpp)
