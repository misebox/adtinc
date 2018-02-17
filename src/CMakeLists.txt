cmake_minimum_required(VERSION 2.6)
project(libadt-main)

# Change here if test directory moves
set(BASE_DIR ..)

# include
set(INCLUDE_DIR ${BASE_DIR}/include)

# lib
include_directories(${INCLUDE_DIR})
set(LIB_DIR ${BASE_DIR}/lib)
FILE(GLOB SOURCES ${LIB_DIR}/*.c)
add_library(adt ${SOURCES})

# main
add_executable(${PROJECT_NAME} main.c)
target_link_libraries(${PROJECT_NAME} adt)
