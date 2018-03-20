find_package(GTest REQUIRED)

function(mlb_add_test testName)
    string(TOLOWER ${testName} lowerTestName)
    set(test_filename ${lowerTestName}s.cpp)
    add_executable(${testName} ${test_filename})
    target_link_libraries(${testName} mlb-core curlpp gtest gmock)
    target_include_directories(${testName} 
      PRIVATE 
        ${CMAKE_SOURCE_DIR}/3rdParty/curlpp/include
        ${CMAKE_SOURCE_DIR}/3rdParty/gtest/googlemock/include
    )
    gtest_add_tests(${testName} "" ${test_filename})
endfunction()

mlb_add_test(ServerTest)
mlb_add_test(JsonConverterTest)
mlb_add_test(MultipleRequestsTest)
