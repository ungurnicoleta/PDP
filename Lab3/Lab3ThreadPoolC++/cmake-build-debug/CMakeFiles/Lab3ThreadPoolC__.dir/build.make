# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/nicoletaungur/FACULTATE/PPD/Lab3/Lab3ThreadPoolC++

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/nicoletaungur/FACULTATE/PPD/Lab3/Lab3ThreadPoolC++/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Lab3ThreadPoolC__.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Lab3ThreadPoolC__.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Lab3ThreadPoolC__.dir/flags.make

CMakeFiles/Lab3ThreadPoolC__.dir/main.cpp.o: CMakeFiles/Lab3ThreadPoolC__.dir/flags.make
CMakeFiles/Lab3ThreadPoolC__.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/nicoletaungur/FACULTATE/PPD/Lab3/Lab3ThreadPoolC++/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Lab3ThreadPoolC__.dir/main.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Lab3ThreadPoolC__.dir/main.cpp.o -c /Users/nicoletaungur/FACULTATE/PPD/Lab3/Lab3ThreadPoolC++/main.cpp

CMakeFiles/Lab3ThreadPoolC__.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Lab3ThreadPoolC__.dir/main.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/nicoletaungur/FACULTATE/PPD/Lab3/Lab3ThreadPoolC++/main.cpp > CMakeFiles/Lab3ThreadPoolC__.dir/main.cpp.i

CMakeFiles/Lab3ThreadPoolC__.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Lab3ThreadPoolC__.dir/main.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/nicoletaungur/FACULTATE/PPD/Lab3/Lab3ThreadPoolC++/main.cpp -o CMakeFiles/Lab3ThreadPoolC__.dir/main.cpp.s

CMakeFiles/Lab3ThreadPoolC__.dir/ThreadPool.cpp.o: CMakeFiles/Lab3ThreadPoolC__.dir/flags.make
CMakeFiles/Lab3ThreadPoolC__.dir/ThreadPool.cpp.o: ../ThreadPool.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/nicoletaungur/FACULTATE/PPD/Lab3/Lab3ThreadPoolC++/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Lab3ThreadPoolC__.dir/ThreadPool.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Lab3ThreadPoolC__.dir/ThreadPool.cpp.o -c /Users/nicoletaungur/FACULTATE/PPD/Lab3/Lab3ThreadPoolC++/ThreadPool.cpp

CMakeFiles/Lab3ThreadPoolC__.dir/ThreadPool.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Lab3ThreadPoolC__.dir/ThreadPool.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/nicoletaungur/FACULTATE/PPD/Lab3/Lab3ThreadPoolC++/ThreadPool.cpp > CMakeFiles/Lab3ThreadPoolC__.dir/ThreadPool.cpp.i

CMakeFiles/Lab3ThreadPoolC__.dir/ThreadPool.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Lab3ThreadPoolC__.dir/ThreadPool.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/nicoletaungur/FACULTATE/PPD/Lab3/Lab3ThreadPoolC++/ThreadPool.cpp -o CMakeFiles/Lab3ThreadPoolC__.dir/ThreadPool.cpp.s

# Object files for target Lab3ThreadPoolC__
Lab3ThreadPoolC___OBJECTS = \
"CMakeFiles/Lab3ThreadPoolC__.dir/main.cpp.o" \
"CMakeFiles/Lab3ThreadPoolC__.dir/ThreadPool.cpp.o"

# External object files for target Lab3ThreadPoolC__
Lab3ThreadPoolC___EXTERNAL_OBJECTS =

Lab3ThreadPoolC__: CMakeFiles/Lab3ThreadPoolC__.dir/main.cpp.o
Lab3ThreadPoolC__: CMakeFiles/Lab3ThreadPoolC__.dir/ThreadPool.cpp.o
Lab3ThreadPoolC__: CMakeFiles/Lab3ThreadPoolC__.dir/build.make
Lab3ThreadPoolC__: CMakeFiles/Lab3ThreadPoolC__.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/nicoletaungur/FACULTATE/PPD/Lab3/Lab3ThreadPoolC++/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable Lab3ThreadPoolC__"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Lab3ThreadPoolC__.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Lab3ThreadPoolC__.dir/build: Lab3ThreadPoolC__

.PHONY : CMakeFiles/Lab3ThreadPoolC__.dir/build

CMakeFiles/Lab3ThreadPoolC__.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Lab3ThreadPoolC__.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Lab3ThreadPoolC__.dir/clean

CMakeFiles/Lab3ThreadPoolC__.dir/depend:
	cd /Users/nicoletaungur/FACULTATE/PPD/Lab3/Lab3ThreadPoolC++/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/nicoletaungur/FACULTATE/PPD/Lab3/Lab3ThreadPoolC++ /Users/nicoletaungur/FACULTATE/PPD/Lab3/Lab3ThreadPoolC++ /Users/nicoletaungur/FACULTATE/PPD/Lab3/Lab3ThreadPoolC++/cmake-build-debug /Users/nicoletaungur/FACULTATE/PPD/Lab3/Lab3ThreadPoolC++/cmake-build-debug /Users/nicoletaungur/FACULTATE/PPD/Lab3/Lab3ThreadPoolC++/cmake-build-debug/CMakeFiles/Lab3ThreadPoolC__.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Lab3ThreadPoolC__.dir/depend

