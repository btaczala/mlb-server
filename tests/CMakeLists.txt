add_executable(ServerTests server-tests.cpp)
target_link_libraries(ServerTests mlb-core gtest curlpp)
target_include_directories(ServerTests PRIVATE ${CMAKE_SOURCE_DIR}/3rdParty/curlpp/include)
add_test(ServerTests ServerTests)
