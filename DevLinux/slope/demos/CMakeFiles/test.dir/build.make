# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.0

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
CMAKE_SOURCE_DIR = /media/DATA/projects/spl/SmartStreetLight/slope

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /media/DATA/projects/spl/SmartStreetLight/slope

# Include any dependencies generated for this target.
include demos/CMakeFiles/test.dir/depend.make

# Include the progress variables for this target.
include demos/CMakeFiles/test.dir/progress.make

# Include the compile flags for this target's objects.
include demos/CMakeFiles/test.dir/flags.make

demos/CMakeFiles/test.dir/test.c.o: demos/CMakeFiles/test.dir/flags.make
demos/CMakeFiles/test.dir/test.c.o: demos/test.c
	$(CMAKE_COMMAND) -E cmake_progress_report /media/DATA/projects/spl/SmartStreetLight/slope/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object demos/CMakeFiles/test.dir/test.c.o"
	cd /media/DATA/projects/spl/SmartStreetLight/slope/demos && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/test.dir/test.c.o   -c /media/DATA/projects/spl/SmartStreetLight/slope/demos/test.c

demos/CMakeFiles/test.dir/test.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/test.dir/test.c.i"
	cd /media/DATA/projects/spl/SmartStreetLight/slope/demos && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /media/DATA/projects/spl/SmartStreetLight/slope/demos/test.c > CMakeFiles/test.dir/test.c.i

demos/CMakeFiles/test.dir/test.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/test.dir/test.c.s"
	cd /media/DATA/projects/spl/SmartStreetLight/slope/demos && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /media/DATA/projects/spl/SmartStreetLight/slope/demos/test.c -o CMakeFiles/test.dir/test.c.s

demos/CMakeFiles/test.dir/test.c.o.requires:
.PHONY : demos/CMakeFiles/test.dir/test.c.o.requires

demos/CMakeFiles/test.dir/test.c.o.provides: demos/CMakeFiles/test.dir/test.c.o.requires
	$(MAKE) -f demos/CMakeFiles/test.dir/build.make demos/CMakeFiles/test.dir/test.c.o.provides.build
.PHONY : demos/CMakeFiles/test.dir/test.c.o.provides

demos/CMakeFiles/test.dir/test.c.o.provides.build: demos/CMakeFiles/test.dir/test.c.o

# Object files for target test
test_OBJECTS = \
"CMakeFiles/test.dir/test.c.o"

# External object files for target test
test_EXTERNAL_OBJECTS =

demos/test: demos/CMakeFiles/test.dir/test.c.o
demos/test: demos/CMakeFiles/test.dir/build.make
demos/test: src/libslope.so
demos/test: demos/CMakeFiles/test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C executable test"
	cd /media/DATA/projects/spl/SmartStreetLight/slope/demos && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
demos/CMakeFiles/test.dir/build: demos/test
.PHONY : demos/CMakeFiles/test.dir/build

demos/CMakeFiles/test.dir/requires: demos/CMakeFiles/test.dir/test.c.o.requires
.PHONY : demos/CMakeFiles/test.dir/requires

demos/CMakeFiles/test.dir/clean:
	cd /media/DATA/projects/spl/SmartStreetLight/slope/demos && $(CMAKE_COMMAND) -P CMakeFiles/test.dir/cmake_clean.cmake
.PHONY : demos/CMakeFiles/test.dir/clean

demos/CMakeFiles/test.dir/depend:
	cd /media/DATA/projects/spl/SmartStreetLight/slope && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /media/DATA/projects/spl/SmartStreetLight/slope /media/DATA/projects/spl/SmartStreetLight/slope/demos /media/DATA/projects/spl/SmartStreetLight/slope /media/DATA/projects/spl/SmartStreetLight/slope/demos /media/DATA/projects/spl/SmartStreetLight/slope/demos/CMakeFiles/test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : demos/CMakeFiles/test.dir/depend
