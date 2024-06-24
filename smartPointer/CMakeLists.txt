cmake_minimum_required(VERSION 3.9)
project(smartPointer)

include_directories(${PROJECT_SOURCE_DIR}/includes)

add_executable(uniquePointer
    "uniquePointer.cpp"
    "src/UniquePointer.cpp"
)

add_executable(sharedPointer
    "sharedPointer.cpp"
    "src/SharedPointer.cpp"
)
