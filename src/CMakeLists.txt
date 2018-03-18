find_package(cpprestsdk REQUIRED)
find_package(Boost REQUIRED COMPONENTS system)
find_package(OpenSSL REQUIRED)

add_library(mlb-core
    logger.cpp
    server.cpp
    database.cpp
    restparsers/articles.cpp
    restparsers/schedule.cpp
)

target_include_directories(mlb-core 
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/3rdParty/metastuff/include
    ${CMAKE_SOURCE_DIR}/3rdParty/json/include
)
target_link_libraries(mlb-core
  PRIVATE
    cpprestsdk::cpprest
    Boost::system
    OpenSSL::SSL
  PUBLIC
    spdlog
)

add_executable(mlb-server main.cpp)
target_link_libraries(mlb-server mlb-core)
