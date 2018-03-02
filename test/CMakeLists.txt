cmake_minimum_required(VERSION 2.6)
project(libadt-test)

# for coverage
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fprofile-instr-generate -fcoverage-mapping")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11 -fprofile-instr-generate -fcoverage-mapping")
set(CMAKE_EXE_LINKER_FLAGS=" -fprofile-instr-generate -fcoverage-mapping")

# Change here if test directory moves
set(BASE_DIR ..)

# include
set(INCLUDE_DIR ${BASE_DIR}/include)

# lib
include_directories(${INCLUDE_DIR})
set(LIB_DIR ${BASE_DIR}/lib)
FILE(GLOB SOURCES ${LIB_DIR}/*.c)
add_library(adt ${SOURCES})

# test
set(TEST_DIR ${BASE_DIR}/test)
FILE(GLOB TESTS ${TEST_DIR}/*.cpp)
add_subdirectory(lib/googletest/googletest)
add_executable(${PROJECT_NAME} ${TESTS})
target_link_libraries(${PROJECT_NAME} adt gtest_main)
