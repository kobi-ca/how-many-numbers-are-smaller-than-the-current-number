cmake_minimum_required(VERSION 3.21)
project(how_many_numbers_are_smaller_than_the_current_number)

set(CMAKE_CXX_STANDARD 20)

find_package(fmt REQUIRED)
find_package(gtest REQUIRED)

add_executable(main main.cpp)
target_link_libraries(main PRIVATE fmt::fmt gtest::gtest)
