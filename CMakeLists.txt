cmake_minimum_required(VERSION 3.22)
project(RAN)

set(CMAKE_CXX_STANDARD 20)

add_executable(ranp src/preprocessor/main.cc)
add_executable(ranc src/compiler/main.cc)
