cmake_minimum_required(VERSION 3.10)
project(Parryater)
set(CMAKE_CXX_STANDARD 17)
file(GLOB_RECURSE SOURCES 
    "*.cpp"
    "*.h"
)
add_executable(Parryater ${SOURCES})