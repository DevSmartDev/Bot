# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.0

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list

# Suppress spl of executed commands.
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
CMAKE_SOURCE_DIR = /media/DATA/projects/bot/bot/slope

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /media/DATA/projects/bot/bot/slope

# Include any dependencies generated for this target.
include demos/CMakeFiles/plot_stack.dir/depend.make

# Include the progress variables for this target.
include demos/CMakeFiles/plot_stack.dir/progress.make

# Include the compile flags for this target's objects.
include demos/CMakeFiles/plot_stack.dir/flags.make

demos/CMakeFiles/plot_stack.dir/plot_stack.c.o: demos/CMakeFiles/plot_stack.dir/flags.make
demos/CMakeFiles/plot_stack.dir/plot_stack.c.o: demos/plot_stack.c
	$(CMAKE_COMMAND) -E cmake_progress_report /media/DATA/projects/bot/bot/slope/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object demos/CMakeFiles/plot_stack.dir/plot_stack.c.o"
	cd /media/DATA/projects/bot/bot/slope/demos && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/plot_stack.dir/plot_stack.c.o   -c /media/DATA/projects/bot/bot/slope/demos/plot_stack.c

demos/CMakeFiles/plot_stack.dir/plot_stack.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/plot_stack.dir/plot_stack.c.i"
	cd /media/DATA/projects/bot/bot/slope/demos && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /media/DATA/projects/bot/bot/slope/demos/plot_stack.c > CMakeFiles/plot_stack.dir/plot_stack.c.i

demos/CMakeFiles/plot_stack.dir/plot_stack.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/plot_stack.dir/plot_stack.c.s"
	cd /media/DATA/projects/bot/bot/slope/demos && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /media/DATA/projects/bot/bot/slope/demos/plot_stack.c -o CMakeFiles/plot_stack.dir/plot_stack.c.s

demos/CMakeFiles/plot_stack.dir/plot_stack.c.o.requires:
.PHONY : demos/CMakeFiles/plot_stack.dir/plot_stack.c.o.requires

demos/CMakeFiles/plot_stack.dir/plot_stack.c.o.provides: demos/CMakeFiles/plot_stack.dir/plot_stack.c.o.requires
	$(MAKE) -f demos/CMakeFiles/plot_stack.dir/build.make demos/CMakeFiles/plot_stack.dir/plot_stack.c.o.provides.build
.PHONY : demos/CMakeFiles/plot_stack.dir/plot_stack.c.o.provides

demos/CMakeFiles/plot_stack.dir/plot_stack.c.o.provides.build: demos/CMakeFiles/plot_stack.dir/plot_stack.c.o

# Object files for target plot_stack
plot_stack_OBJECTS = \
"CMakeFiles/plot_stack.dir/plot_stack.c.o"

# External object files for target plot_stack
plot_stack_EXTERNAL_OBJECTS =

demos/plot_stack: demos/CMakeFiles/plot_stack.dir/plot_stack.c.o
demos/plot_stack: demos/CMakeFiles/plot_stack.dir/build.make
demos/plot_stack: src/libslope.so
demos/plot_stack: demos/CMakeFiles/plot_stack.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C executable plot_stack"
	cd /media/DATA/projects/bot/bot/slope/demos && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/plot_stack.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
demos/CMakeFiles/plot_stack.dir/build: demos/plot_stack
.PHONY : demos/CMakeFiles/plot_stack.dir/build

demos/CMakeFiles/plot_stack.dir/requires: demos/CMakeFiles/plot_stack.dir/plot_stack.c.o.requires
.PHONY : demos/CMakeFiles/plot_stack.dir/requires

demos/CMakeFiles/plot_stack.dir/clean:
	cd /media/DATA/projects/bot/bot/slope/demos && $(CMAKE_COMMAND) -P CMakeFiles/plot_stack.dir/cmake_clean.cmake
.PHONY : demos/CMakeFiles/plot_stack.dir/clean

demos/CMakeFiles/plot_stack.dir/depend:
	cd /media/DATA/projects/bot/bot/slope && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /media/DATA/projects/bot/bot/slope /media/DATA/projects/bot/bot/slope/demos /media/DATA/projects/bot/bot/slope /media/DATA/projects/bot/bot/slope/demos /media/DATA/projects/bot/bot/slope/demos/CMakeFiles/plot_stack.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : demos/CMakeFiles/plot_stack.dir/depend

