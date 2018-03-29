cmake_minimum_required(VERSION 3.7)
cmake_policy(SET CMP0048 NEW)
project(rdm-server VERSION 0.0.1)

find_program(IWYU_PATH NAMES include-what-you-use iwyu)
message(STATUS ${IWYU_PATH})

set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH}" "${CMAKE_SOURCE_DIR}/cmake/modules")
configure_file(${CMAKE_SOURCE_DIR}/src/version.hpp.cmake ${CMAKE_CURRENT_BINARY_DIR}/version.hpp)

set(MLB_VERSION "0.0.1")

option(ENABLE_TESTING "Enables unit tests" ON)
option(BUILD_ALL "Build 3rdParty packages also" ON)
set(CMAKE_CXX_STANDARD 17)

include(cmake/Sanitize.cmake)
include(cmake/clang-tidy.cmake)

add_subdirectory(3rdParty)
add_subdirectory(src)

if(ENABLE_TESTING)
    enable_testing()
    add_subdirectory(tests)
endif()
