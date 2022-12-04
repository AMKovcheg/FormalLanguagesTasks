cmake_minimum_required(VERSION 3.8)
project(Task1)

set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH}" ${CMAKE_SOURCE_DIR}/cmake)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

find_package(GTest REQUIRED)
find_package(GMock REQUIRED)
find_package(Threads REQUIRED)

include_directories(${GTEST_INCLUDE_DIRS})
include_directories(${GMOCK_INCLUDE_DIRS})

add_subdirectory(Tests)

enable_testing()

add_test(testNode ${Testing_SOURCE_DIR}/bin/Tests)

add_executable(Task1
        ./Code/main.cpp
        ./Code/RegularExpression.cpp ./Code/RegularExpression.h
        ./Code/Node.cpp ./Code/Node.h)
