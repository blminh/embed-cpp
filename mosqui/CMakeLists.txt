cmake_minimum_required(VERSION 3.9)
project(mosquitto_client)

include_directories(
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/lib/mosquitto
    ${PROJECT_SOURCE_DIR}/lib/mosquitto/lib
    ${PROJECT_SOURCE_DIR}/lib/mosquitto/lib/cpp
    ${PROJECT_SOURCE_DIR}/lib/mosquitto/include
    ${PROJECT_SOURCE_DIR}/lib/json/include
)

link_directories(
    ${PROJECT_SOURCE_DIR}/lib/mosquitto
    ${PROJECT_SOURCE_DIR}/lib/json
)

configure_file("${PROJECT_SOURCE_DIR}/config.json" "${PROJECT_BINARY_DIR}/config.json" COPYONLY)

add_subdirectory(
    lib
)

file(GLOB SOURCES "lib/mosquitto/lib/*.c")

add_library(sub_client_lib SHARED
    "lib/mosquitto/lib/cpp/mosquittopp.cpp"
)
add_executable(sub_client
    "sub_client/sub_client.cpp"
    ${SOURCES}
)
target_link_libraries(sub_client
    INTERFACE mosquitto
    sub_client_lib
    ssl
    crypto
    pthread
    nlohmann_json::nlohmann_json
)

add_library(pub_client_lib SHARED
    "lib/mosquitto/lib/cpp/mosquittopp.cpp"
)
add_executable(pub_client
    "pub_client/pub_client.cpp"
    ${SOURCES}
)
target_link_libraries(pub_client
    INTERFACE mosquitto
    pub_client_lib
    ssl
    crypto
    pthread
    nlohmann_json::nlohmann_json
)

file(COPY "${PROJECT_SOURCE_DIR}/ca_certificates/ca.crt" DESTINATION "${PROJECT_BINARY_DIR}")
file(COPY "${PROJECT_SOURCE_DIR}/certs/client.crt" DESTINATION "${PROJECT_BINARY_DIR}")
file(COPY "${PROJECT_SOURCE_DIR}/certs/client.key" DESTINATION "${PROJECT_BINARY_DIR}")
