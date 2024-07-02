cmake_minimum_required(VERSION 3.9)
project(sub_client)

include_directories(
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/lib/includes
)

link_directories(
    ${PROJECT_SOURCE_DIR}/lib
)

configure_file("${PROJECT_SOURCE_DIR}/config.json" "${PROJECT_BINARY_DIR}/config.json" COPYONLY)

add_subdirectory(
    utils/json
)

# add_subdirectory(
#     utils/mosquitto
# )

# find_package(mosquitto REQUIRED)

add_executable(${PROJECT_NAME}
    "sub_client.cpp"
)

target_link_libraries(${PROJECT_NAME}
    ssl
    crypto
    pthread
    nlohmann_json
    mosquitto
)

file(COPY "${PROJECT_SOURCE_DIR}/ca_certificates/ca.crt" DESTINATION "${PROJECT_BINARY_DIR}")
file(COPY "${PROJECT_SOURCE_DIR}/certs/client.crt" DESTINATION "${PROJECT_BINARY_DIR}")
file(COPY "${PROJECT_SOURCE_DIR}/certs/client.key" DESTINATION "${PROJECT_BINARY_DIR}")
