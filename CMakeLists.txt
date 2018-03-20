project(rdm-server)

cmake_minimum_required(VERSION 3.7)

find_program(IWYU_PATH NAMES include-what-you-use iwyu)
message(STATUS ${IWYU_PATH})

set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH}" "${CMAKE_SOURCE_DIR}/cmake/modules")

option(ENABLE_TESTING "Enables unit tests" ON)
option(DISABLE_3rdParty "Disables 3rdParty packages" OFF)
set(CMAKE_CXX_STANDARD 17)

include(cmake/clang-tidy.cmake)

add_subdirectory(3rdParty)
add_subdirectory(src)

if(ENABLE_TESTING)
    enable_testing()
    add_subdirectory(tests)
endif()
