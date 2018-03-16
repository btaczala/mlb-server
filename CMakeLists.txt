
project(rdm-server)

cmake_minimum_required(VERSION 3.7)

option(ENABLE_TESTING "Enables unit tests" ON)
set(CMAKE_CXX_STANDARD 14)

add_subdirectory(3rdParty)
add_subdirectory(src)

if(ENABLE_TESTING)
    enable_testing()
    add_subdirectory(tests)
endif()
