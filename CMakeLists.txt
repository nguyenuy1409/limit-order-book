cmake_minimum_required(VERSION 3.30)
project(LimitOrderBook)

set(CMAKE_CXX_STANDARD 17)

add_executable(LimitOrderBook src/main.cpp)

target_include_directories(LimitOrderBook PRIVATE include)