# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 4.0

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/sumair/prog/memcache

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/sumair/prog/memcache/build

# Include any dependencies generated for this target.
include CMakeFiles/memcache.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/memcache.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/memcache.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/memcache.dir/flags.make

CMakeFiles/memcache.dir/codegen:
.PHONY : CMakeFiles/memcache.dir/codegen

CMakeFiles/memcache.dir/src/baseCommand.cpp.o: CMakeFiles/memcache.dir/flags.make
CMakeFiles/memcache.dir/src/baseCommand.cpp.o: /home/sumair/prog/memcache/src/baseCommand.cpp
CMakeFiles/memcache.dir/src/baseCommand.cpp.o: CMakeFiles/memcache.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/sumair/prog/memcache/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/memcache.dir/src/baseCommand.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/memcache.dir/src/baseCommand.cpp.o -MF CMakeFiles/memcache.dir/src/baseCommand.cpp.o.d -o CMakeFiles/memcache.dir/src/baseCommand.cpp.o -c /home/sumair/prog/memcache/src/baseCommand.cpp

CMakeFiles/memcache.dir/src/baseCommand.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/memcache.dir/src/baseCommand.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sumair/prog/memcache/src/baseCommand.cpp > CMakeFiles/memcache.dir/src/baseCommand.cpp.i

CMakeFiles/memcache.dir/src/baseCommand.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/memcache.dir/src/baseCommand.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sumair/prog/memcache/src/baseCommand.cpp -o CMakeFiles/memcache.dir/src/baseCommand.cpp.s

CMakeFiles/memcache.dir/src/main.cpp.o: CMakeFiles/memcache.dir/flags.make
CMakeFiles/memcache.dir/src/main.cpp.o: /home/sumair/prog/memcache/src/main.cpp
CMakeFiles/memcache.dir/src/main.cpp.o: CMakeFiles/memcache.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/sumair/prog/memcache/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/memcache.dir/src/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/memcache.dir/src/main.cpp.o -MF CMakeFiles/memcache.dir/src/main.cpp.o.d -o CMakeFiles/memcache.dir/src/main.cpp.o -c /home/sumair/prog/memcache/src/main.cpp

CMakeFiles/memcache.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/memcache.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sumair/prog/memcache/src/main.cpp > CMakeFiles/memcache.dir/src/main.cpp.i

CMakeFiles/memcache.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/memcache.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sumair/prog/memcache/src/main.cpp -o CMakeFiles/memcache.dir/src/main.cpp.s

CMakeFiles/memcache.dir/src/string.cpp.o: CMakeFiles/memcache.dir/flags.make
CMakeFiles/memcache.dir/src/string.cpp.o: /home/sumair/prog/memcache/src/string.cpp
CMakeFiles/memcache.dir/src/string.cpp.o: CMakeFiles/memcache.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/sumair/prog/memcache/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/memcache.dir/src/string.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/memcache.dir/src/string.cpp.o -MF CMakeFiles/memcache.dir/src/string.cpp.o.d -o CMakeFiles/memcache.dir/src/string.cpp.o -c /home/sumair/prog/memcache/src/string.cpp

CMakeFiles/memcache.dir/src/string.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/memcache.dir/src/string.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sumair/prog/memcache/src/string.cpp > CMakeFiles/memcache.dir/src/string.cpp.i

CMakeFiles/memcache.dir/src/string.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/memcache.dir/src/string.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sumair/prog/memcache/src/string.cpp -o CMakeFiles/memcache.dir/src/string.cpp.s

# Object files for target memcache
memcache_OBJECTS = \
"CMakeFiles/memcache.dir/src/baseCommand.cpp.o" \
"CMakeFiles/memcache.dir/src/main.cpp.o" \
"CMakeFiles/memcache.dir/src/string.cpp.o"

# External object files for target memcache
memcache_EXTERNAL_OBJECTS =

memcache: CMakeFiles/memcache.dir/src/baseCommand.cpp.o
memcache: CMakeFiles/memcache.dir/src/main.cpp.o
memcache: CMakeFiles/memcache.dir/src/string.cpp.o
memcache: CMakeFiles/memcache.dir/build.make
memcache: CMakeFiles/memcache.dir/compiler_depend.ts
memcache: CMakeFiles/memcache.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/sumair/prog/memcache/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable memcache"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/memcache.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/memcache.dir/build: memcache
.PHONY : CMakeFiles/memcache.dir/build

CMakeFiles/memcache.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/memcache.dir/cmake_clean.cmake
.PHONY : CMakeFiles/memcache.dir/clean

CMakeFiles/memcache.dir/depend:
	cd /home/sumair/prog/memcache/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/sumair/prog/memcache /home/sumair/prog/memcache /home/sumair/prog/memcache/build /home/sumair/prog/memcache/build /home/sumair/prog/memcache/build/CMakeFiles/memcache.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/memcache.dir/depend

