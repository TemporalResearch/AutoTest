set(PROJECT_HOME_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
set(PROJECT_SRC ${PROJECT_HOME_DIRECTORY}/src)
set(PROJECT_INCLUDE ${PROJECT_HOME_DIRECTORY}/include)
set(PROJECT_INTERNAL_LIBS ${PROJECT_HOME_DIRECTORY}/libs)

set(SUPERMARINE_MODULE_EXTENSION _module)

function(supermarine_add_internal_library target lib_name)
    target_include_directories(${target}${SUPERMARINE_MODULE_EXTENSION} PRIVATE ${PROJECT_INTERNAL_LIBS}/${lib_name}/include)
endfunction()

function(supermarine_add_internal_library_for_cmake_target target lib_name)
    target_include_directories(${target} PRIVATE ${PROJECT_INTERNAL_LIBS}/${lib_name}/include)
endfunction()

function(supermarine_add_leaf_module module_name)
    file(GLOB_RECURSE module_HEADERS CONFIGURE_DEPENDS "*.hpp")
    file(RELATIVE_PATH module_relative_pos ${PROJECT_INCLUDE} ${CMAKE_CURRENT_SOURCE_DIR})
    file(GLOB_RECURSE module_SRC CONFIGURE_DEPENDS "${PROJECT_SRC}/${module_relative_pos}/*.cpp")

    add_library(${module_name}${SUPERMARINE_MODULE_EXTENSION} ${module_SRC} ${module_HEADERS})

    target_include_directories(${module_name}${SUPERMARINE_MODULE_EXTENSION} PRIVATE ${PROJECT_INCLUDE})
endfunction()

MACRO(SUBDIRLIST result curdir)
    FILE(GLOB children RELATIVE ${curdir} ${curdir}/*)
    SET(dirlist "")
    FOREACH(child ${children})
        IF(IS_DIRECTORY ${curdir}/${child})
            LIST(APPEND dirlist ${child})
        ENDIF()
    ENDFOREACH()
    SET(${result} ${dirlist})
ENDMACRO()

function(supermarine_add_collate_module module_name)
    file(GLOB module_HEADERS CONFIGURE_DEPENDS "*.hpp")
    file(RELATIVE_PATH module_relative_pos ${PROJECT_INCLUDE} ${CMAKE_CURRENT_SOURCE_DIR})
    file(GLOB module_SRC CONFIGURE_DEPENDS "${PROJECT_SRC}/${module_relative_pos}/*.cpp")

    add_library(${module_name}${SUPERMARINE_MODULE_EXTENSION} ${module_SRC} ${module_HEADERS})

    subdirlist(subDirs ${CMAKE_CURRENT_SOURCE_DIR})
    foreach(subdir ${subDirs})
        add_subdirectory(${subdir})
        target_link_libraries(${module_name}${SUPERMARINE_MODULE_EXTENSION} PUBLIC ${subdir}_module)
    endforeach()

    target_include_directories(${module_name}${SUPERMARINE_MODULE_EXTENSION} PRIVATE ${PROJECT_INCLUDE})
endfunction()