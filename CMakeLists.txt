include(supermarine_build_env.cmake)

add_library(auto_test SHARED src/auto_test/to_string.cpp)

add_subdirectory(${PROJECT_INCLUDE})
target_include_directories(auto_test PUBLIC ${PROJECT_INCLUDE})
target_link_libraries(auto_test
        PUBLIC auto_test_src_module)
