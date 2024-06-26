cmake_minimum_required(VERSION 3.9)
project(sockets)

include_directories(${PROJECT_SOURCE_DIR}/includes)

add_executable(server
    "server.cpp"
    "src/TcpServer.cpp"
    "src/ClientHandler.cpp"
)

target_link_libraries(server pthread)

add_executable(client client.cpp)

target_link_libraries(client pthread)

add_executable(clientTwo clientTwo.cpp)

target_link_libraries(clientTwo pthread)
