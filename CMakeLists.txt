cmake_minimum_required(VERSION 3.24)
project(ct7-linked-lists-intro LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Source files (excluding main.cpp for tests)
set(LIB_SOURCES
    src/SinglyLinkedList.cpp
)

# Main executable
add_executable(${PROJECT_NAME}
    src/main.cpp
    ${LIB_SOURCES}
)

target_include_directories(${PROJECT_NAME} PRIVATE include)

# ==================== Google Test ====================
# Fetch GoogleTest
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Test executable
add_executable(run_tests
    tests/singly_linked_list_test.cpp
    ${LIB_SOURCES}
)

target_include_directories(run_tests PRIVATE include)
target_link_libraries(run_tests GTest::gtest_main)
