cmake_minimum_required(VERSION 3.22)
project(Labs)

set(CMAKE_CXX_STANDARD 20)

add_executable(Labs main.cpp sllist.h tests.cpp dictionary.h)
