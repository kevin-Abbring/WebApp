# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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
CMAKE_SOURCE_DIR = /home/zt/temp1/kde_prj/server32

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/zt/temp1/kde_prj/server32/build

# Include any dependencies generated for this target.
include CMakeFiles/server32.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/server32.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/server32.dir/flags.make

CMakeFiles/server32.dir/server302.o: CMakeFiles/server32.dir/flags.make
CMakeFiles/server32.dir/server302.o: ../server302.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/zt/temp1/kde_prj/server32/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/server32.dir/server302.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/server32.dir/server302.o -c /home/zt/temp1/kde_prj/server32/server302.cpp

CMakeFiles/server32.dir/server302.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server32.dir/server302.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/zt/temp1/kde_prj/server32/server302.cpp > CMakeFiles/server32.dir/server302.i

CMakeFiles/server32.dir/server302.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server32.dir/server302.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/zt/temp1/kde_prj/server32/server302.cpp -o CMakeFiles/server32.dir/server302.s

CMakeFiles/server32.dir/server302.o.requires:
.PHONY : CMakeFiles/server32.dir/server302.o.requires

CMakeFiles/server32.dir/server302.o.provides: CMakeFiles/server32.dir/server302.o.requires
	$(MAKE) -f CMakeFiles/server32.dir/build.make CMakeFiles/server32.dir/server302.o.provides.build
.PHONY : CMakeFiles/server32.dir/server302.o.provides

CMakeFiles/server32.dir/server302.o.provides.build: CMakeFiles/server32.dir/server302.o

CMakeFiles/server32.dir/main.o: CMakeFiles/server32.dir/flags.make
CMakeFiles/server32.dir/main.o: ../main.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/zt/temp1/kde_prj/server32/build/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/server32.dir/main.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/server32.dir/main.o -c /home/zt/temp1/kde_prj/server32/main.cpp

CMakeFiles/server32.dir/main.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server32.dir/main.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/zt/temp1/kde_prj/server32/main.cpp > CMakeFiles/server32.dir/main.i

CMakeFiles/server32.dir/main.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server32.dir/main.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/zt/temp1/kde_prj/server32/main.cpp -o CMakeFiles/server32.dir/main.s

CMakeFiles/server32.dir/main.o.requires:
.PHONY : CMakeFiles/server32.dir/main.o.requires

CMakeFiles/server32.dir/main.o.provides: CMakeFiles/server32.dir/main.o.requires
	$(MAKE) -f CMakeFiles/server32.dir/build.make CMakeFiles/server32.dir/main.o.provides.build
.PHONY : CMakeFiles/server32.dir/main.o.provides

CMakeFiles/server32.dir/main.o.provides.build: CMakeFiles/server32.dir/main.o

# Object files for target server32
server32_OBJECTS = \
"CMakeFiles/server32.dir/server302.o" \
"CMakeFiles/server32.dir/main.o"

# External object files for target server32
server32_EXTERNAL_OBJECTS =

server32: CMakeFiles/server32.dir/server302.o
server32: CMakeFiles/server32.dir/main.o
server32: CMakeFiles/server32.dir/build.make
server32: CMakeFiles/server32.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable server32"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/server32.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/server32.dir/build: server32
.PHONY : CMakeFiles/server32.dir/build

CMakeFiles/server32.dir/requires: CMakeFiles/server32.dir/server302.o.requires
CMakeFiles/server32.dir/requires: CMakeFiles/server32.dir/main.o.requires
.PHONY : CMakeFiles/server32.dir/requires

CMakeFiles/server32.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/server32.dir/cmake_clean.cmake
.PHONY : CMakeFiles/server32.dir/clean

CMakeFiles/server32.dir/depend:
	cd /home/zt/temp1/kde_prj/server32/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/zt/temp1/kde_prj/server32 /home/zt/temp1/kde_prj/server32 /home/zt/temp1/kde_prj/server32/build /home/zt/temp1/kde_prj/server32/build /home/zt/temp1/kde_prj/server32/build/CMakeFiles/server32.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/server32.dir/depend

