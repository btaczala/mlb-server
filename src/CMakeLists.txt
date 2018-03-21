find_package(cpprestsdk REQUIRED)
find_package(Boost REQUIRED COMPONENTS system)
find_package(OpenSSL REQUIRED)

add_library(mlb-core
    logger.cpp
    server.cpp
    restparsers/articles.cpp
    restparsers/schedule.cpp
    restparsers/gamereports.cpp
)

clang_tidy_library(mlb-core)

target_include_directories(mlb-core 
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/3rdParty/metastuff/include
    ${CMAKE_SOURCE_DIR}/3rdParty/json/include
    ${CMAKE_BINARY_DIR}
)
target_link_libraries(mlb-core
  PRIVATE
    cpprestsdk::cpprest
    Boost::system
    OpenSSL::SSL
  PUBLIC
    spdlog
    date
)

add_executable(mlb-server main.cpp)
target_link_libraries(mlb-server mlb-core)
clang_tidy_library(mlb-server)
