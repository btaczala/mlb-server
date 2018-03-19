project(rdm-server)

cmake_minimum_required(VERSION 3.7)

find_program(IWYU_PATH NAMES include-what-you-use iwyu)
message(STATUS ${IWYU_PATH})

option(ENABLE_TESTING "Enables unit tests" ON)
set(CMAKE_CXX_STANDARD 17)

include(cmake/clang-tidy.cmake)

add_subdirectory(3rdParty)
add_subdirectory(src)

if(ENABLE_TESTING)
    enable_testing()
    add_subdirectory(tests)
endif()
