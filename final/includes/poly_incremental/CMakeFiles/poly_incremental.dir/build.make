# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
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
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/users/sdi1800217/Code/Project/ass1/current

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/users/sdi1800217/Code/Project/ass1/current

# Include any dependencies generated for this target.
include includes/poly_incremental/CMakeFiles/poly_incremental.dir/depend.make

# Include the progress variables for this target.
include includes/poly_incremental/CMakeFiles/poly_incremental.dir/progress.make

# Include the compile flags for this target's objects.
include includes/poly_incremental/CMakeFiles/poly_incremental.dir/flags.make

includes/poly_incremental/CMakeFiles/poly_incremental.dir/poly_incremental.cpp.o: includes/poly_incremental/CMakeFiles/poly_incremental.dir/flags.make
includes/poly_incremental/CMakeFiles/poly_incremental.dir/poly_incremental.cpp.o: includes/poly_incremental/poly_incremental.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/users/sdi1800217/Code/Project/ass1/current/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object includes/poly_incremental/CMakeFiles/poly_incremental.dir/poly_incremental.cpp.o"
	cd /home/users/sdi1800217/Code/Project/ass1/current/includes/poly_incremental && /usr/bin/X11/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/poly_incremental.dir/poly_incremental.cpp.o -c /home/users/sdi1800217/Code/Project/ass1/current/includes/poly_incremental/poly_incremental.cpp

includes/poly_incremental/CMakeFiles/poly_incremental.dir/poly_incremental.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/poly_incremental.dir/poly_incremental.cpp.i"
	cd /home/users/sdi1800217/Code/Project/ass1/current/includes/poly_incremental && /usr/bin/X11/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/users/sdi1800217/Code/Project/ass1/current/includes/poly_incremental/poly_incremental.cpp > CMakeFiles/poly_incremental.dir/poly_incremental.cpp.i

includes/poly_incremental/CMakeFiles/poly_incremental.dir/poly_incremental.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/poly_incremental.dir/poly_incremental.cpp.s"
	cd /home/users/sdi1800217/Code/Project/ass1/current/includes/poly_incremental && /usr/bin/X11/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/users/sdi1800217/Code/Project/ass1/current/includes/poly_incremental/poly_incremental.cpp -o CMakeFiles/poly_incremental.dir/poly_incremental.cpp.s

# Object files for target poly_incremental
poly_incremental_OBJECTS = \
"CMakeFiles/poly_incremental.dir/poly_incremental.cpp.o"

# External object files for target poly_incremental
poly_incremental_EXTERNAL_OBJECTS =

includes/poly_incremental/libpoly_incremental.a: includes/poly_incremental/CMakeFiles/poly_incremental.dir/poly_incremental.cpp.o
includes/poly_incremental/libpoly_incremental.a: includes/poly_incremental/CMakeFiles/poly_incremental.dir/build.make
includes/poly_incremental/libpoly_incremental.a: includes/poly_incremental/CMakeFiles/poly_incremental.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/users/sdi1800217/Code/Project/ass1/current/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libpoly_incremental.a"
	cd /home/users/sdi1800217/Code/Project/ass1/current/includes/poly_incremental && $(CMAKE_COMMAND) -P CMakeFiles/poly_incremental.dir/cmake_clean_target.cmake
	cd /home/users/sdi1800217/Code/Project/ass1/current/includes/poly_incremental && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/poly_incremental.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
includes/poly_incremental/CMakeFiles/poly_incremental.dir/build: includes/poly_incremental/libpoly_incremental.a

.PHONY : includes/poly_incremental/CMakeFiles/poly_incremental.dir/build

includes/poly_incremental/CMakeFiles/poly_incremental.dir/clean:
	cd /home/users/sdi1800217/Code/Project/ass1/current/includes/poly_incremental && $(CMAKE_COMMAND) -P CMakeFiles/poly_incremental.dir/cmake_clean.cmake
.PHONY : includes/poly_incremental/CMakeFiles/poly_incremental.dir/clean

includes/poly_incremental/CMakeFiles/poly_incremental.dir/depend:
	cd /home/users/sdi1800217/Code/Project/ass1/current && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/users/sdi1800217/Code/Project/ass1/current /home/users/sdi1800217/Code/Project/ass1/current/includes/poly_incremental /home/users/sdi1800217/Code/Project/ass1/current /home/users/sdi1800217/Code/Project/ass1/current/includes/poly_incremental /home/users/sdi1800217/Code/Project/ass1/current/includes/poly_incremental/CMakeFiles/poly_incremental.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : includes/poly_incremental/CMakeFiles/poly_incremental.dir/depend

