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
    ${PROJECT_SOURCE_DIR}/lib/mosquitto/lib/cpp
)

configure_file("${PROJECT_SOURCE_DIR}/config.json" "${PROJECT_BINARY_DIR}/config.json" COPYONLY)

add_subdirectory(
    lib
)

add_executable(sub_client
    "sub_client/sub_client.cpp"
<<<<<<< HEAD
)

target_link_libraries(sub_client PRIVATE
=======
)
target_link_libraries(sub_client
    mosquittopp
    ssl
    crypto
    pthread
    nlohmann_json::nlohmann_json
)

add_executable(pub_client
    "pub_client/pub_client.cpp"
)
target_link_libraries(pub_client
    mosquittopp
>>>>>>> 7bce2c1 (fix cmakelists.txt, clean sub_client)
    ssl
    crypto
    pthread
    mosquittopp
)

file(COPY "${PROJECT_SOURCE_DIR}/ca_certificates/ca.crt" DESTINATION "${PROJECT_BINARY_DIR}")
file(COPY "${PROJECT_SOURCE_DIR}/certs/client.crt" DESTINATION "${PROJECT_BINARY_DIR}")
file(COPY "${PROJECT_SOURCE_DIR}/certs/client.key" DESTINATION "${PROJECT_BINARY_DIR}")
