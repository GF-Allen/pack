cmake_minimum_required(VERSION 3.6)
project(pack)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.c pack.c pack.h)
add_executable(pack ${SOURCE_FILES})