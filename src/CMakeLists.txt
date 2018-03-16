find_package(cpprestsdk REQUIRED)
find_package(Boost REQUIRED COMPONENTS system)
find_package(OpenSSL REQUIRED)

add_library(mlb-core logger.cpp server.cpp database.cpp responseconverter.cpp)

target_include_directories(mlb-core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(mlb-core PRIVATE  cpprestsdk::cpprest Boost::system OpenSSL::SSL PUBLIC spdlog)

add_executable(mlb-server main.cpp)
target_link_libraries(mlb-server mlb-core)
