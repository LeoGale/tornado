# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.14

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


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
CMAKE_COMMAND = /Applications/CMake.app/Contents/bin/cmake

# The command to remove a file.
RM = /Applications/CMake.app/Contents/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/leo/code/workshop/tornado

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/leo/code/workshop/tornado

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/Applications/CMake.app/Contents/bin/cmake -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake cache editor..."
	/Applications/CMake.app/Contents/bin/ccmake -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /Users/leo/code/workshop/tornado/CMakeFiles /Users/leo/code/workshop/tornado/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /Users/leo/code/workshop/tornado/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean

.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named tornado

# Build rule for target.
tornado: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 tornado
.PHONY : tornado

# fast build rule for target.
tornado/fast:
	$(MAKE) -f CMakeFiles/tornado.dir/build.make CMakeFiles/tornado.dir/build
.PHONY : tornado/fast

#=============================================================================
# Target rules for targets named observer

# Build rule for target.
observer: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 observer
.PHONY : observer

# fast build rule for target.
observer/fast:
	$(MAKE) -f observer/CMakeFiles/observer.dir/build.make observer/CMakeFiles/observer.dir/build
.PHONY : observer/fast

main.o: main.cc.o

.PHONY : main.o

# target to build an object file
main.cc.o:
	$(MAKE) -f CMakeFiles/tornado.dir/build.make CMakeFiles/tornado.dir/main.cc.o
.PHONY : main.cc.o

main.i: main.cc.i

.PHONY : main.i

# target to preprocess a source file
main.cc.i:
	$(MAKE) -f CMakeFiles/tornado.dir/build.make CMakeFiles/tornado.dir/main.cc.i
.PHONY : main.cc.i

main.s: main.cc.s

.PHONY : main.s

# target to generate assembly for a file
main.cc.s:
	$(MAKE) -f CMakeFiles/tornado.dir/build.make CMakeFiles/tornado.dir/main.cc.s
.PHONY : main.cc.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... rebuild_cache"
	@echo "... edit_cache"
	@echo "... tornado"
	@echo "... observer"
	@echo "... main.o"
	@echo "... main.i"
	@echo "... main.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

