cmake_minimum_required(VERSION 2.6)
project(libadt-test)

# Change here if test directory moves
set(BASE_DIR ..)

set(INCLUDE_DIR ${BASE_DIR}/include)
set(LIB_DIR ${BASE_DIR}/lib)
set(TEST_DIR ${BASE_DIR}/test)
FILE(GLOB SOURCES ${LIB_DIR}/*.c)
FILE(GLOB TESTS ${TEST_DIR}/*.cpp)

include_directories(${INCLUDE_DIR})
add_library(adt ${SOURCES})

add_subdirectory(${TEST_DIR}/lib/googletest/googletest)
add_executable(${PROJECT_NAME} ${TESTS})

target_link_libraries(${PROJECT_NAME} adt gtest_main)

