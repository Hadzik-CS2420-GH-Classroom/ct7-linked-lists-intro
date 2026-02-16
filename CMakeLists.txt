cmake_minimum_required(VERSION 3.24)
project(ct7-linked-lists-intro LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(${PROJECT_NAME}
    src/main.cpp
    src/SinglyLinkedList.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE include)
