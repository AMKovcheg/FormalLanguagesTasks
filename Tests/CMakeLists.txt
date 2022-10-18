cmake_minimum_required(VERSION 3.8)

project(Tests)

find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

include_directories(${GTEST_INCLUDE_DIRS})

add_executable(
        Tests
        run-tests.cpp
        ../Code/RegularExpression.h ../Code/RegularExpression.cpp
        ../Code/Node.h ../Code/Node.cpp
        tests.cpp
)

target_link_libraries(Tests ${GTEST_LIBRARIES} Threads::Threads)