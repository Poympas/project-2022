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
CMAKE_SOURCE_DIR = /home/users/sdi1800217/Code/Project/ass1/take8

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/users/sdi1800217/Code/Project/ass1/take8

# Include any dependencies generated for this target.
include CMakeFiles/to_polygon.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/to_polygon.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/to_polygon.dir/flags.make

CMakeFiles/to_polygon.dir/main.cpp.o: CMakeFiles/to_polygon.dir/flags.make
CMakeFiles/to_polygon.dir/main.cpp.o: main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/users/sdi1800217/Code/Project/ass1/take8/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/to_polygon.dir/main.cpp.o"
	/usr/bin/X11/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/to_polygon.dir/main.cpp.o -c /home/users/sdi1800217/Code/Project/ass1/take8/main.cpp

CMakeFiles/to_polygon.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/to_polygon.dir/main.cpp.i"
	/usr/bin/X11/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/users/sdi1800217/Code/Project/ass1/take8/main.cpp > CMakeFiles/to_polygon.dir/main.cpp.i

CMakeFiles/to_polygon.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/to_polygon.dir/main.cpp.s"
	/usr/bin/X11/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/users/sdi1800217/Code/Project/ass1/take8/main.cpp -o CMakeFiles/to_polygon.dir/main.cpp.s

# Object files for target to_polygon
to_polygon_OBJECTS = \
"CMakeFiles/to_polygon.dir/main.cpp.o"

# External object files for target to_polygon
to_polygon_EXTERNAL_OBJECTS =

to_polygon: CMakeFiles/to_polygon.dir/main.cpp.o
to_polygon: CMakeFiles/to_polygon.dir/build.make
to_polygon: includes/cgal_config/libcgal_config.a
to_polygon: includes/visibility/libvisibility.a
to_polygon: includes/io_manip/libio_manip.a
to_polygon: includes/poly_incremental/libpoly_incremental.a
to_polygon: /usr/lib/x86_64-linux-gnu/libgmpxx.so
to_polygon: /usr/lib/x86_64-linux-gnu/libmpfr.so
to_polygon: /usr/lib/x86_64-linux-gnu/libgmp.so
to_polygon: CMakeFiles/to_polygon.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/users/sdi1800217/Code/Project/ass1/take8/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable to_polygon"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/to_polygon.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/to_polygon.dir/build: to_polygon

.PHONY : CMakeFiles/to_polygon.dir/build

CMakeFiles/to_polygon.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/to_polygon.dir/cmake_clean.cmake
.PHONY : CMakeFiles/to_polygon.dir/clean

CMakeFiles/to_polygon.dir/depend:
	cd /home/users/sdi1800217/Code/Project/ass1/take8 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/users/sdi1800217/Code/Project/ass1/take8 /home/users/sdi1800217/Code/Project/ass1/take8 /home/users/sdi1800217/Code/Project/ass1/take8 /home/users/sdi1800217/Code/Project/ass1/take8 /home/users/sdi1800217/Code/Project/ass1/take8/CMakeFiles/to_polygon.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/to_polygon.dir/depend

