cmake_minimum_required(VERSION 2.8)

project(aurigma CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS_DEBUG} -std=c++11 -Wall -Wextra -pedantic")

set(CMAKE_VERBOSE_MAKEFILE on)

file(GLOB HEADER_FILES src/*.h)
file(GLOB SOURCE_FILES src/*.cpp)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

include_directories(/usr/include)

add_executable(${PROJECT_NAME} ${HEADER_FILES} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} tiff stdc++)
