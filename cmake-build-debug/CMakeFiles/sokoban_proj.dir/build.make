# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

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
CMAKE_COMMAND = /opt/clion-2018.3.4/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /opt/clion-2018.3.4/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/akuznetsov/sokoban_proj

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/akuznetsov/sokoban_proj/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/sokoban_proj.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/sokoban_proj.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/sokoban_proj.dir/flags.make

CMakeFiles/sokoban_proj.dir/main.cpp.o: CMakeFiles/sokoban_proj.dir/flags.make
CMakeFiles/sokoban_proj.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/akuznetsov/sokoban_proj/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/sokoban_proj.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sokoban_proj.dir/main.cpp.o -c /home/akuznetsov/sokoban_proj/main.cpp

CMakeFiles/sokoban_proj.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sokoban_proj.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/akuznetsov/sokoban_proj/main.cpp > CMakeFiles/sokoban_proj.dir/main.cpp.i

CMakeFiles/sokoban_proj.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sokoban_proj.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/akuznetsov/sokoban_proj/main.cpp -o CMakeFiles/sokoban_proj.dir/main.cpp.s

CMakeFiles/sokoban_proj.dir/TwoDimArray.cpp.o: CMakeFiles/sokoban_proj.dir/flags.make
CMakeFiles/sokoban_proj.dir/TwoDimArray.cpp.o: TwoDimArray.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/akuznetsov/sokoban_proj/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/sokoban_proj.dir/TwoDimArray.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sokoban_proj.dir/TwoDimArray.cpp.o -c /home/akuznetsov/sokoban_proj/cmake-build-debug/TwoDimArray.cpp

CMakeFiles/sokoban_proj.dir/TwoDimArray.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sokoban_proj.dir/TwoDimArray.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/akuznetsov/sokoban_proj/cmake-build-debug/TwoDimArray.cpp > CMakeFiles/sokoban_proj.dir/TwoDimArray.cpp.i

CMakeFiles/sokoban_proj.dir/TwoDimArray.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sokoban_proj.dir/TwoDimArray.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/akuznetsov/sokoban_proj/cmake-build-debug/TwoDimArray.cpp -o CMakeFiles/sokoban_proj.dir/TwoDimArray.cpp.s

# Object files for target sokoban_proj
sokoban_proj_OBJECTS = \
"CMakeFiles/sokoban_proj.dir/main.cpp.o" \
"CMakeFiles/sokoban_proj.dir/TwoDimArray.cpp.o"

# External object files for target sokoban_proj
sokoban_proj_EXTERNAL_OBJECTS =

sokoban_proj: CMakeFiles/sokoban_proj.dir/main.cpp.o
sokoban_proj: CMakeFiles/sokoban_proj.dir/TwoDimArray.cpp.o
sokoban_proj: CMakeFiles/sokoban_proj.dir/build.make
sokoban_proj: CMakeFiles/sokoban_proj.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/akuznetsov/sokoban_proj/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable sokoban_proj"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/sokoban_proj.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/sokoban_proj.dir/build: sokoban_proj

.PHONY : CMakeFiles/sokoban_proj.dir/build

CMakeFiles/sokoban_proj.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/sokoban_proj.dir/cmake_clean.cmake
.PHONY : CMakeFiles/sokoban_proj.dir/clean

CMakeFiles/sokoban_proj.dir/depend:
	cd /home/akuznetsov/sokoban_proj/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/akuznetsov/sokoban_proj /home/akuznetsov/sokoban_proj /home/akuznetsov/sokoban_proj/cmake-build-debug /home/akuznetsov/sokoban_proj/cmake-build-debug /home/akuznetsov/sokoban_proj/cmake-build-debug/CMakeFiles/sokoban_proj.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/sokoban_proj.dir/depend
