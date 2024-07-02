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

configure_file("${PROJECT_SOURCE_DIR}/config.json" "${PROJECT_BINARY_DIR}/config.json" COPYONLY)

add_subdirectory( utils/json )

target_link_libraries(${PROJECT_NAME}
    mosquitto
    ssl
    crypto
    pthread
    nlohmann_json
)

file(COPY  "${PROJECT_SOURCE_DIR}/ca_certificates" DESTINATION "${PROJECT_BINARY_DIR}")
file(COPY  "${PROJECT_SOURCE_DIR}/certs" DESTINATION "${PROJECT_BINARY_DIR}")
