cmake_minimum_required(VERSION 3.25)
project(register CXX)

set(CMAKE_CXX_STANDARD 14)
#set(CMAKE_CXX_FLAGS "-Wall -pedantic -Wextra")

add_library(mabe_register INTERFACE)
target_include_directories(mabe_register INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/include")
add_library(mabe::register ALIAS mabe_register)

add_subdirectory(example)

