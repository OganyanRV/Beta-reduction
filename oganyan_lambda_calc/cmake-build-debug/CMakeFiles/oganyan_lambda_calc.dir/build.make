# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.17

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

# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2020.3.2\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2020.3.2\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = E:\Desktop\course\oganyan_lambda_calc

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = E:\Desktop\course\oganyan_lambda_calc\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/oganyan_lambda_calc.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/oganyan_lambda_calc.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/oganyan_lambda_calc.dir/flags.make

CMakeFiles/oganyan_lambda_calc.dir/main.cpp.obj: CMakeFiles/oganyan_lambda_calc.dir/flags.make
CMakeFiles/oganyan_lambda_calc.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=E:\Desktop\course\oganyan_lambda_calc\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/oganyan_lambda_calc.dir/main.cpp.obj"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\oganyan_lambda_calc.dir\main.cpp.obj -c E:\Desktop\course\oganyan_lambda_calc\main.cpp

CMakeFiles/oganyan_lambda_calc.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/oganyan_lambda_calc.dir/main.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E E:\Desktop\course\oganyan_lambda_calc\main.cpp > CMakeFiles\oganyan_lambda_calc.dir\main.cpp.i

CMakeFiles/oganyan_lambda_calc.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/oganyan_lambda_calc.dir/main.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S E:\Desktop\course\oganyan_lambda_calc\main.cpp -o CMakeFiles\oganyan_lambda_calc.dir\main.cpp.s

# Object files for target oganyan_lambda_calc
oganyan_lambda_calc_OBJECTS = \
"CMakeFiles/oganyan_lambda_calc.dir/main.cpp.obj"

# External object files for target oganyan_lambda_calc
oganyan_lambda_calc_EXTERNAL_OBJECTS =

oganyan_lambda_calc.exe: CMakeFiles/oganyan_lambda_calc.dir/main.cpp.obj
oganyan_lambda_calc.exe: CMakeFiles/oganyan_lambda_calc.dir/build.make
oganyan_lambda_calc.exe: CMakeFiles/oganyan_lambda_calc.dir/linklibs.rsp
oganyan_lambda_calc.exe: CMakeFiles/oganyan_lambda_calc.dir/objects1.rsp
oganyan_lambda_calc.exe: CMakeFiles/oganyan_lambda_calc.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=E:\Desktop\course\oganyan_lambda_calc\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable oganyan_lambda_calc.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\oganyan_lambda_calc.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/oganyan_lambda_calc.dir/build: oganyan_lambda_calc.exe

.PHONY : CMakeFiles/oganyan_lambda_calc.dir/build

CMakeFiles/oganyan_lambda_calc.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\oganyan_lambda_calc.dir\cmake_clean.cmake
.PHONY : CMakeFiles/oganyan_lambda_calc.dir/clean

CMakeFiles/oganyan_lambda_calc.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" E:\Desktop\course\oganyan_lambda_calc E:\Desktop\course\oganyan_lambda_calc E:\Desktop\course\oganyan_lambda_calc\cmake-build-debug E:\Desktop\course\oganyan_lambda_calc\cmake-build-debug E:\Desktop\course\oganyan_lambda_calc\cmake-build-debug\CMakeFiles\oganyan_lambda_calc.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/oganyan_lambda_calc.dir/depend
