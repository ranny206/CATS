cmake_minimum_required(VERSION 3.15)
project(CATS_4A)

SET(CMAKE_CXX_FLAGS -pthread)

find_package(Threads)

set(CMAKE_CXX_STANDARD 14)

add_executable(CATS_4A main.cpp)