cmake_minimum_required(VERSION 2.6)
project(libadt)

set(LIB_NAME adt)

# Change here if test directory moves
set(BASE_DIR ..)

# include
set(INCLUDE_DIR ${BASE_DIR}/include)

# lib
include_directories(${INCLUDE_DIR})
set(LIB_DIR ${BASE_DIR}/lib)
FILE(GLOB SOURCES ${LIB_DIR}/*.c)
add_library(${LIB_NAME} ${SOURCES})

# setting for installation
INSTALL(
  TARGETS ${LIB_NAME}
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  COMPONENT library
)
FILE(GLOB INCLUDE_HEADERS ${INCLUDE_DIR}/*.h)
INSTALL(
  FILES ${INCLUDE_HEADERS}
  DESTINATION include
)
