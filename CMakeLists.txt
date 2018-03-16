
project(rdm-server)

cmake_minimum_required(VERSION 3.7)
enable_testing()
set(CMAKE_CXX_STANDARD 14)

add_subdirectory(3rdParty)
add_subdirectory(src)

add_subdirectory(tests)
