cmake_minimum_required(VERSION 3.10)
project(memcache)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_SOURCE_DIR}/include)
file(GLOB SOURCES
    "src/*.cpp"
    "include/*.h"
)

add_executable(memcache ${SOURCES})
