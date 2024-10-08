cmake_minimum_required(VERSION 3.9)
project(mosquitto_client)

include_directories(
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/lib/mosquitto
    ${PROJECT_SOURCE_DIR}/lib/mosquitto/lib
    ${PROJECT_SOURCE_DIR}/lib/mosquitto/lib/cpp
    ${PROJECT_SOURCE_DIR}/lib/mosquitto/include
    ${PROJECT_SOURCE_DIR}/lib/json/include
    ${PROJECT_SOURCE_DIR}/lib/civetweb
    ${PROJECT_SOURCE_DIR}/lib/civetweb/src
    ${PROJECT_SOURCE_DIR}/lib/civetweb/include
)

link_directories(
    ${PROJECT_SOURCE_DIR}/lib/mosquitto/lib/cpp
)

configure_file("${PROJECT_SOURCE_DIR}/config.json" "${PROJECT_BINARY_DIR}/config.json" COPYONLY)

add_subdirectory(
    lib
)

add_executable(sub_client
    "sub_client/sub_client_nonssl.cpp"
)
target_link_libraries(sub_client
    mosquittopp
    ssl
    crypto
    pthread
    nlohmann_json::nlohmann_json
    wiringPi
    wiringPiDev
)

add_executable(pub_client
    "pub_client/pub_client_nonssl.cpp"
)
target_link_libraries(pub_client
    mosquittopp
    ssl
    crypto
    pthread
    nlohmann_json::nlohmann_json
)

file(COPY "${PROJECT_SOURCE_DIR}/ca_certificates/ca.crt" DESTINATION "${PROJECT_BINARY_DIR}")
file(COPY "${PROJECT_SOURCE_DIR}/certs/client.crt" DESTINATION "${PROJECT_BINARY_DIR}")
file(COPY "${PROJECT_SOURCE_DIR}/certs/client.key" DESTINATION "${PROJECT_BINARY_DIR}")
