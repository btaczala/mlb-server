find_package(GTest REQUIRED)

add_executable(ServerTest servertests.cpp)
target_link_libraries(ServerTest mlb-core gtest curlpp gmock)
target_include_directories(ServerTest PRIVATE ${CMAKE_SOURCE_DIR}/3rdParty/curlpp/include)
gtest_add_tests(ServerTest "" servertests.cpp)

add_executable(JsonConverterTest jsonconvertertests.cpp)
target_link_libraries(JsonConverterTest mlb-core gtest curlpp gmock)
target_include_directories(JsonConverterTest PRIVATE ${CMAKE_SOURCE_DIR}/3rdParty/curlpp/include)
gtest_add_tests(JsonConverterTest "" jsonconvertertests.cpp)

add_executable(MultipleRequestsTest multiplerequeststests.cpp)
target_link_libraries(MultipleRequestsTest mlb-core gtest curlpp gmock)
target_include_directories(MultipleRequestsTest PRIVATE ${CMAKE_SOURCE_DIR}/3rdParty/curlpp/include)
gtest_add_tests(MultipleRequestsTest "" multiplerequeststests.cpp)
