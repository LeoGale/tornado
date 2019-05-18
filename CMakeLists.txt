cmake_minimum_required (VERSION 2.6)

#include (CheckFunctionExists)

project (tornado C CXX)

enable_testing()

#project (tornado)
#IF(APPLE)
#    set (CMAKE_CXX_COMPILER "g++")
#    set (CMAKE_C_COMPILER "Clang")
#    set (CMAKE_CXX_COMPILER_ID "g++")
#ENDIF(APPLE)

set (TORNADOR_VERSION_MAJOR 1)
set (TORNADOR_VERSION_MINOR 0)

IF(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
ENDIF()

set(CXX_FLAGS
	-g
#-o2
	-Wno-unused-parameter
	-Wno-sign-conversion
	-Wno-old-style-cast
	-Woverloaded-virtual
	-Wpointer-arith #for what?
	-Wshadow
	-std=c++0x
    )
IF(CMAKE_BUILD_BITES EQUAL 32)
    list(APPEND CXX_FLAGS "-m32")
ENDIF()

string(REPLACE ";" " " CMAKE_CXX_FLAGS "${CXX_FLAGS}")

set(CMAKE_CXX_FLAGS_DEBUG "-O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG")
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

message(STATUS "CXX DEBUG FLAGS ${CMAKE_CXX_FLAGS_DEBUG}")
message(STATUS "CXX RELEASE FLAGS ${CMAKE_CXX_FLAGS_RELEASE}")
message(STATUS "CXX FLAGS ${CMAKE_CXX_FLAGS}") 
message(STATUS "BUILD EXMAPLES ${CMAKE_BUILD_NO_EXAMPLES}")
message(STATUS "EXECUTABLE OUTPUT PATH ${EXECUTABLE_OUTPUT_PATH}")
message(STATUS "LIBRARY OUTPATH PATH ${LIBRARY_OUTPATH_PATH}")

#configure a header file to pass some of the CMake settings
# to source code 

# In Current project, 
# the variable PROJECT_BINARY_DIR is equal to PROJECT_SOURCE_DIR
# configure_file
# https://cmake.org/cmake/help/latest/command/configure_file.html

message(STATUS "PROJECT BINARY DIR ${PROJECT_BINARY_DIR}")
message(STATUS "PROJECT SOURCE DIR ${PROJECT_SOURCE_DIR}")

configure_file (
    "${PROJECT_SOURCE_DIR}/Config.h.in"
    "${PROJECT_SOURCE_DIR}/Config.h"
    @ONLY
)

#check_function_exists(log HAVE_LOG)

#option (SEE_OBSERVE "See observe pattern example." ON)

include_directories(${PROJECT_SOURCE_DIR})
# comment below code out, make them optional.
#include_directories("${PROJECT_BINARY_DIR}/observer")

add_subdirectory(tornado/base)
add_subdirectory(tornado/net)

if(NOT CMAKE_BUILD_NO_EXMAPLES)
    add_subdirectory(examples)
else()
    message(STATUS "Built with NO Examples")
endif()
# add the intall targets 
# CMAKE_INSTALL_PREFIX is used to determine 
# the root of where the files will be installed
#install (TARGETS tornado DESTINATION bin)
#install (FILES "${PROJECT_BINARY_DIR}/Config.h" DESTINATION include)
