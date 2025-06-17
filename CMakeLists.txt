cmake_minimum_required(VERSION 3.10)
project(memcache)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ThreadSanitizer for detecting race conditions
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=thread -g -O1")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=thread")

# Include headers from include/
include_directories(${CMAKE_SOURCE_DIR}/include)

# Add your source files explicitly
add_executable(memcache
        src/main.cpp
        src/string.cpp
        src/baseCommand.cpp
        # Add other .cpp files if needed
)

# Link pthread (required for threads)
target_link_libraries(memcache pthread)
