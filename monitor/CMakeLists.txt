cmake_minimum_required(VERSION 2.8)

project(smon CXX)

#set(CMAKE_INSTALL_PREFIX ${smon_SOURCE_DIR})

set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

set(THIRD_PARTY ${PROJECT_SOURCE_DIR}/../third_party )
include_directories(${PROJECT_SOURCE_DIR})
include_directories(${THIRD_PARTY}/include)
link_directories(${THIRD_PARTY}/lib)

file(GLOB_RECURSE SRC "api/*.cpp" "util/*.cpp")
add_library(monapi ${SRC})

SET(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_FLAGS " -std=c++11 ")
set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "-O2")

add_subdirectory(util)
#add_subdirectory(api)
add_subdirectory(test)
add_subdirectory(agent)
#add_subdirectory(server)
