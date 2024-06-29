cmake_minimum_required(VERSION 3.9)
project(pub_client)

include_directories(
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/lib/includes
)

link_directories(
    ${PROJECT_SOURCE_DIR}/lib
)

add_executable(${PROJECT_NAME}
    "pub_client.cpp"
)

target_link_libraries(${PROJECT_NAME}
    mosquitto
    ssl
    crypto
    pthread
)
