CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(clang-faces)

SET( PREFIX ${CMAKE_INSTALL_PREFIX} )

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake )

SET(CMAKE_BUILD_TYPE "debug")
ENABLE_TESTING()

# find_package(LLVM REQUIRED)
# find_package(Clang REQUIRED)

message(STATUS "LLVM LDFLAGS = ${LLVM_MODULE_LIBS}")

#FILE( GLOB_RECURSE ALL_SRC "${CMAKE_SOURCE_DIR}/*.cpp" )
FILE( GLOB ALL_SRC "${CMAKE_SOURCE_DIR}/*.cpp" )
string(REGEX REPLACE ".*/CMakeFiles/[^;]+;?" "" ALL_SRC "${ALL_SRC}")

message(STATUS "Source files found: ${ALL_SRC}")

execute_process(
  COMMAND clang++ -print-search-dirs
  COMMAND grep libraries
  COMMAND grep -o "/.*"
  OUTPUT_VARIABLE CLANG_LIBRARY_DIRS
  OUTPUT_STRIP_TRAILING_WHITESPACE)
set(CLANG_LIBRARY_INCLUDES "${CMAKE_SOURCE_DIR}/llvm")
set(CLANG_LIBRARY_LIBS "${CLANG_LIBRARY_DIRS}/../../")
set(CLANG_LIBS "-lclang")

message(STATUS "Library dirs found: ${CLANG_LIBRARY_DIRS}")

include_directories(
  ${PROJECT_SOURCE_DIR}/include
  ${LLVM_INCLUDE_DIRS}
  ${CLANG_LIBRARY_INCLUDES})

message(STATUS "LLVM LIB DIR: ${LLVM_LIBRARY_DIRS}")

link_directories( 
${LLVM_LIBRARY_DIRS}
${CLANG_LIBRARY_LIBS}
)

add_executable( 
${PROJECT_NAME}

main.cpp
#${ALL_SRC}
)

target_link_libraries( ${PROJECT_NAME} 
${LLVM_LIBNAMES}
${CLANG_LIBS} 
)

add_definitions(
  ${LLVM_CFLAGS}
  -Wall
  -std=c++11
  )

add_executable( 
sniper

sniper.cpp
)

target_link_libraries( sniper
${LLVM_LIBNAMES}
${CLANG_LIBS} 
)

add_definitions(
  ${LLVM_CFLAGS}
  -Wall
  -std=c++11
  )

INSTALL( TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_PREFIX} )

# LDLIBS := $(shell llvm-config --ldflags) $(shell llvm-config --libs all) -lstdc++ -lclang
# CFLAGS += $(shell llvm-config --cflags) -Wall -Wextra -pedantic -O1 -g

