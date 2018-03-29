set(ADDRESS_SANITIZER_CXX_FLAGS "-fsanitize=address" "-fno-omit-frame-pointer")
set(ADDRESS_SANITIZER_LD_FLAGS "-fsanitize=address")

set(MEMORY_SANITIZER_CXX_FLAGS "-fsanitize=memory" "")
set(MEMORY_SANITIZER_LD_FLAGS "-fsanitize=memory")

set(SANITIZER_CXX_FLAGS)
set(SANITIZER_LD_FLAGS)

function(add_mlb_sanitizers target)
    if(SANITIZER)
        message(STATUS "Target ${target} will be built with ${SANITIZER_CXX_FLAGS}")
        target_compile_options(${target} PRIVATE ${SANITIZER_CXX_FLAGS})
        target_link_libraries(${target} PRIVATE ${SANITIZER_LD_FLAGS})
    endif()
endfunction()

if(SANITIZER)

    if(NOT CMAKE_BUILD_TYPE MATCHES Debug)
        message(FATAL_ERROR "SANITIZERS are only allowed in Debug mode")
    endif()

    message(STATUS "Selected SANITIZER ${SANITIZER}")
    set(SANITIZER_CXX_FLAGS "-fsanitize=${SANITIZER}" "-fno-omit-frame-pointer")
    set(SANITIZER_LD_FLAGS "-fsanitize=${SANITIZER}")

endif()
