# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_SOURCE_DIR = /media/routhleck/Windows-SSD/Users/Routhleck/Documents/GitHub/c++_project/train_system

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /media/routhleck/Windows-SSD/Users/Routhleck/Documents/GitHub/c++_project/build-train_system-Desktop_Qt_6_4_0_GCC_64bit-Debug

# Utility rule file for train_system_autogen.

# Include any custom commands dependencies for this target.
include CMakeFiles/train_system_autogen.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/train_system_autogen.dir/progress.make

CMakeFiles/train_system_autogen:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/media/routhleck/Windows-SSD/Users/Routhleck/Documents/GitHub/c++_project/build-train_system-Desktop_Qt_6_4_0_GCC_64bit-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Automatic MOC and UIC for target train_system"
	/usr/bin/cmake -E cmake_autogen /media/routhleck/Windows-SSD/Users/Routhleck/Documents/GitHub/c++_project/build-train_system-Desktop_Qt_6_4_0_GCC_64bit-Debug/CMakeFiles/train_system_autogen.dir/AutogenInfo.json Debug

train_system_autogen: CMakeFiles/train_system_autogen
train_system_autogen: CMakeFiles/train_system_autogen.dir/build.make
.PHONY : train_system_autogen

# Rule to build all files generated by this target.
CMakeFiles/train_system_autogen.dir/build: train_system_autogen
.PHONY : CMakeFiles/train_system_autogen.dir/build

CMakeFiles/train_system_autogen.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/train_system_autogen.dir/cmake_clean.cmake
.PHONY : CMakeFiles/train_system_autogen.dir/clean

CMakeFiles/train_system_autogen.dir/depend:
	cd /media/routhleck/Windows-SSD/Users/Routhleck/Documents/GitHub/c++_project/build-train_system-Desktop_Qt_6_4_0_GCC_64bit-Debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /media/routhleck/Windows-SSD/Users/Routhleck/Documents/GitHub/c++_project/train_system /media/routhleck/Windows-SSD/Users/Routhleck/Documents/GitHub/c++_project/train_system /media/routhleck/Windows-SSD/Users/Routhleck/Documents/GitHub/c++_project/build-train_system-Desktop_Qt_6_4_0_GCC_64bit-Debug /media/routhleck/Windows-SSD/Users/Routhleck/Documents/GitHub/c++_project/build-train_system-Desktop_Qt_6_4_0_GCC_64bit-Debug /media/routhleck/Windows-SSD/Users/Routhleck/Documents/GitHub/c++_project/build-train_system-Desktop_Qt_6_4_0_GCC_64bit-Debug/CMakeFiles/train_system_autogen.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/train_system_autogen.dir/depend

