set(CLANG_TIDY_PARAMS "-checks=*,-clang-analyzer-alpha.*")

macro(clang_tidy_library libraryName)
    if(USE_CLANG_TIDY AND CLANG_TIDY)
        set_target_properties(
            ${libraryName} PROPERTIES
            CXX_CLANG_TIDY "${DO_CLANG_TIDY}"
        )
    endif()
endmacro()

if(USE_CLANG_TIDY)
    find_program(CLANG_TIDY
        NAMES clang-tidy
    )

    if(NOT CLANG_TIDY)
        message(STATUS "clang-tidy not found, will not enable clang-tidy")
    else()
        set(DO_CLANG_TIDY "${CLANG_TIDY}" "${CLANG_TIDY_PARAMS}")
    endif()
endif()
