cmake_minimum_required(VERSION 3.2)

project(advanced-fprintf)

add_library(afprintf SHARED
    afprintf/afprintf.c)
target_include_directories(afprintf PUBLIC afprintf)

add_executable(example example.c)
target_link_libraries(example PRIVATE afprintf)


# =============================================================================
# TESTS
# =============================================================================

include(ExternalProject)

set(EXTERNAL_INSTALL_LOCATION ${CMAKE_BINARY_DIR}/external)

ExternalProject_Add(googletest
    GIT_REPOSITORY https://github.com/google/googletest
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${EXTERNAL_INSTALL_LOCATION}
)

include_directories(${EXTERNAL_INSTALL_LOCATION}/include)
link_directories(${EXTERNAL_INSTALL_LOCATION}/lib)

add_executable(test test/test.cpp)
target_link_libraries(test PRIVATE afprintf)
target_link_libraries(test PRIVATE gtest gtest_main pthread)
add_dependencies(test googletest)


