cmake_minimum_required(VERSION 3.9)
project(monitor)

include_directories(${PROJECT_SOURCE_DIR})

add_executable(${PROJECT_NAME}
    "main.cpp"
    "Monitor.cpp"
    "TimeSlot.cpp"
)
