add_executable(ServerTest servertests.cpp)
target_link_libraries(ServerTest mlb-core gtest curlpp gmock)
target_include_directories(ServerTest PRIVATE ${CMAKE_SOURCE_DIR}/3rdParty/curlpp/include)
add_test(ServerTest ServerTest)

