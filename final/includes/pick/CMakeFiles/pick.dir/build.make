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
include includes/pick/CMakeFiles/pick.dir/depend.make

# Include the progress variables for this target.
include includes/pick/CMakeFiles/pick.dir/progress.make

# Include the compile flags for this target's objects.
include includes/pick/CMakeFiles/pick.dir/flags.make

includes/pick/CMakeFiles/pick.dir/pick.cpp.o: includes/pick/CMakeFiles/pick.dir/flags.make
includes/pick/CMakeFiles/pick.dir/pick.cpp.o: includes/pick/pick.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/users/sdi1800217/Code/Project/ass1/current/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object includes/pick/CMakeFiles/pick.dir/pick.cpp.o"
	cd /home/users/sdi1800217/Code/Project/ass1/current/includes/pick && /usr/bin/X11/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/pick.dir/pick.cpp.o -c /home/users/sdi1800217/Code/Project/ass1/current/includes/pick/pick.cpp

includes/pick/CMakeFiles/pick.dir/pick.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/pick.dir/pick.cpp.i"
	cd /home/users/sdi1800217/Code/Project/ass1/current/includes/pick && /usr/bin/X11/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/users/sdi1800217/Code/Project/ass1/current/includes/pick/pick.cpp > CMakeFiles/pick.dir/pick.cpp.i

includes/pick/CMakeFiles/pick.dir/pick.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/pick.dir/pick.cpp.s"
	cd /home/users/sdi1800217/Code/Project/ass1/current/includes/pick && /usr/bin/X11/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/users/sdi1800217/Code/Project/ass1/current/includes/pick/pick.cpp -o CMakeFiles/pick.dir/pick.cpp.s

# Object files for target pick
pick_OBJECTS = \
"CMakeFiles/pick.dir/pick.cpp.o"

# External object files for target pick
pick_EXTERNAL_OBJECTS =

includes/pick/libpick.a: includes/pick/CMakeFiles/pick.dir/pick.cpp.o
includes/pick/libpick.a: includes/pick/CMakeFiles/pick.dir/build.make
includes/pick/libpick.a: includes/pick/CMakeFiles/pick.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/users/sdi1800217/Code/Project/ass1/current/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libpick.a"
	cd /home/users/sdi1800217/Code/Project/ass1/current/includes/pick && $(CMAKE_COMMAND) -P CMakeFiles/pick.dir/cmake_clean_target.cmake
	cd /home/users/sdi1800217/Code/Project/ass1/current/includes/pick && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/pick.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
includes/pick/CMakeFiles/pick.dir/build: includes/pick/libpick.a

.PHONY : includes/pick/CMakeFiles/pick.dir/build

includes/pick/CMakeFiles/pick.dir/clean:
	cd /home/users/sdi1800217/Code/Project/ass1/current/includes/pick && $(CMAKE_COMMAND) -P CMakeFiles/pick.dir/cmake_clean.cmake
.PHONY : includes/pick/CMakeFiles/pick.dir/clean

includes/pick/CMakeFiles/pick.dir/depend:
	cd /home/users/sdi1800217/Code/Project/ass1/current && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/users/sdi1800217/Code/Project/ass1/current /home/users/sdi1800217/Code/Project/ass1/current/includes/pick /home/users/sdi1800217/Code/Project/ass1/current /home/users/sdi1800217/Code/Project/ass1/current/includes/pick /home/users/sdi1800217/Code/Project/ass1/current/includes/pick/CMakeFiles/pick.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : includes/pick/CMakeFiles/pick.dir/depend

