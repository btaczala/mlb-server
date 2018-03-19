set(SPDLOG_BUILD_TESTING CACHE FORCE OFF)
set(SPDLOG_BUILD_EXAMPLES CACHE FORCE OFF)
add_subdirectory(spdlog)

if(ENABLE_TESTING)
    set(BUILD_GTEST ON)
    set(BUILD_GMOCK ON)
    set(BUILD_GTEST CACHE FORCE ON)
    set(BUILD_GMOCK CACHE FORCE ON)
    add_subdirectory(gtest)
    add_subdirectory(curlpp)
    target_sources(curlpp PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/curlpp/include)
endif()

