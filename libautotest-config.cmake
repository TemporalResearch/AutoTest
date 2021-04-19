if (TARGET libautotest::libautotest)
    return()
endif()

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/include ${CMAKE_CURRENT_LIST_DIR}/extern_build)

add_library(libautotest::libautotest INTERFACE IMPORTED)
SET_TARGET_PROPERTIES(libautotest::libautotest PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(libautotest::libautotest
        INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)
target_link_libraries(libautotest::libautotest
        INTERFACE auto_test_src_module)