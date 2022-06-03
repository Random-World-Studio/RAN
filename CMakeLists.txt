cmake_minimum_required(VERSION 3.22)
project(RAN)

set(CMAKE_CXX_STANDARD 20)

add_executable(ranp src/preprocessor/main.cc src/global/log.cc)
add_executable(ranc src/compiler/compilerdef.cc src/compiler/main.cc src/compiler/maketree.cc src/global/log.cc src/compiler/lex.cc src/compiler/syntaxtree.cc src/debug/sttree.cc)
