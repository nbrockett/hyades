cmake_minimum_required(VERSION 3.10)

# set project name
project(Hyades VERSION 0.1 DESCRIPTION "small real-time graphics engine")

# specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(Hyades)
add_subdirectory(client)