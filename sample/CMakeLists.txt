cmake_minimum_required(VERSION 2.6)
project(libadt)
set(LIB_NAME adt)

# Change here if test directory moves
set(BASE_DIR ..)

# include
set(INCLUDE_DIR ${BASE_DIR}/include)

# sample
set(SAMPLE_DIR ${BASE_DIR}/sample)

# lib
include_directories(${INCLUDE_DIR})
set(LIB_DIR ${BASE_DIR}/lib)
FILE(GLOB SOURCES ${LIB_DIR}/*.c)
add_library(${LIB_NAME} ${SOURCES})


FILE(GLOB SAMPLES ${SAMPLE_DIR}/*.c)
foreach(SAMPLE_PATH ${SAMPLES})
    get_filename_component(SAMPLE_EXEC ${SAMPLE_PATH} NAME_WE)
    add_executable(${SAMPLE_EXEC} ${SAMPLE_PATH})
    target_link_libraries(${SAMPLE_EXEC} ${LIB_NAME})
endforeach(SAMPLE_PATH)
