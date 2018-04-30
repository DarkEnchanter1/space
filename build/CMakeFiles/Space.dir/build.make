# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_SOURCE_DIR = /home/greg/Documents/Projects/C++/space

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/greg/Documents/Projects/C++/space/build

# Include any dependencies generated for this target.
include CMakeFiles/Space.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Space.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Space.dir/flags.make

CMakeFiles/Space.dir/physics.cpp.o: CMakeFiles/Space.dir/flags.make
CMakeFiles/Space.dir/physics.cpp.o: ../physics.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/greg/Documents/Projects/C++/space/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Space.dir/physics.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Space.dir/physics.cpp.o -c /home/greg/Documents/Projects/C++/space/physics.cpp

CMakeFiles/Space.dir/physics.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Space.dir/physics.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/greg/Documents/Projects/C++/space/physics.cpp > CMakeFiles/Space.dir/physics.cpp.i

CMakeFiles/Space.dir/physics.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Space.dir/physics.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/greg/Documents/Projects/C++/space/physics.cpp -o CMakeFiles/Space.dir/physics.cpp.s

CMakeFiles/Space.dir/physics.cpp.o.requires:

.PHONY : CMakeFiles/Space.dir/physics.cpp.o.requires

CMakeFiles/Space.dir/physics.cpp.o.provides: CMakeFiles/Space.dir/physics.cpp.o.requires
	$(MAKE) -f CMakeFiles/Space.dir/build.make CMakeFiles/Space.dir/physics.cpp.o.provides.build
.PHONY : CMakeFiles/Space.dir/physics.cpp.o.provides

CMakeFiles/Space.dir/physics.cpp.o.provides.build: CMakeFiles/Space.dir/physics.cpp.o


CMakeFiles/Space.dir/rendering/renderer.cpp.o: CMakeFiles/Space.dir/flags.make
CMakeFiles/Space.dir/rendering/renderer.cpp.o: ../rendering/renderer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/greg/Documents/Projects/C++/space/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Space.dir/rendering/renderer.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Space.dir/rendering/renderer.cpp.o -c /home/greg/Documents/Projects/C++/space/rendering/renderer.cpp

CMakeFiles/Space.dir/rendering/renderer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Space.dir/rendering/renderer.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/greg/Documents/Projects/C++/space/rendering/renderer.cpp > CMakeFiles/Space.dir/rendering/renderer.cpp.i

CMakeFiles/Space.dir/rendering/renderer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Space.dir/rendering/renderer.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/greg/Documents/Projects/C++/space/rendering/renderer.cpp -o CMakeFiles/Space.dir/rendering/renderer.cpp.s

CMakeFiles/Space.dir/rendering/renderer.cpp.o.requires:

.PHONY : CMakeFiles/Space.dir/rendering/renderer.cpp.o.requires

CMakeFiles/Space.dir/rendering/renderer.cpp.o.provides: CMakeFiles/Space.dir/rendering/renderer.cpp.o.requires
	$(MAKE) -f CMakeFiles/Space.dir/build.make CMakeFiles/Space.dir/rendering/renderer.cpp.o.provides.build
.PHONY : CMakeFiles/Space.dir/rendering/renderer.cpp.o.provides

CMakeFiles/Space.dir/rendering/renderer.cpp.o.provides.build: CMakeFiles/Space.dir/rendering/renderer.cpp.o


CMakeFiles/Space.dir/rendering/utils/shader.cpp.o: CMakeFiles/Space.dir/flags.make
CMakeFiles/Space.dir/rendering/utils/shader.cpp.o: ../rendering/utils/shader.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/greg/Documents/Projects/C++/space/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/Space.dir/rendering/utils/shader.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Space.dir/rendering/utils/shader.cpp.o -c /home/greg/Documents/Projects/C++/space/rendering/utils/shader.cpp

CMakeFiles/Space.dir/rendering/utils/shader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Space.dir/rendering/utils/shader.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/greg/Documents/Projects/C++/space/rendering/utils/shader.cpp > CMakeFiles/Space.dir/rendering/utils/shader.cpp.i

CMakeFiles/Space.dir/rendering/utils/shader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Space.dir/rendering/utils/shader.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/greg/Documents/Projects/C++/space/rendering/utils/shader.cpp -o CMakeFiles/Space.dir/rendering/utils/shader.cpp.s

CMakeFiles/Space.dir/rendering/utils/shader.cpp.o.requires:

.PHONY : CMakeFiles/Space.dir/rendering/utils/shader.cpp.o.requires

CMakeFiles/Space.dir/rendering/utils/shader.cpp.o.provides: CMakeFiles/Space.dir/rendering/utils/shader.cpp.o.requires
	$(MAKE) -f CMakeFiles/Space.dir/build.make CMakeFiles/Space.dir/rendering/utils/shader.cpp.o.provides.build
.PHONY : CMakeFiles/Space.dir/rendering/utils/shader.cpp.o.provides

CMakeFiles/Space.dir/rendering/utils/shader.cpp.o.provides.build: CMakeFiles/Space.dir/rendering/utils/shader.cpp.o


CMakeFiles/Space.dir/rendering/utils/text2D.cpp.o: CMakeFiles/Space.dir/flags.make
CMakeFiles/Space.dir/rendering/utils/text2D.cpp.o: ../rendering/utils/text2D.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/greg/Documents/Projects/C++/space/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/Space.dir/rendering/utils/text2D.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Space.dir/rendering/utils/text2D.cpp.o -c /home/greg/Documents/Projects/C++/space/rendering/utils/text2D.cpp

CMakeFiles/Space.dir/rendering/utils/text2D.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Space.dir/rendering/utils/text2D.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/greg/Documents/Projects/C++/space/rendering/utils/text2D.cpp > CMakeFiles/Space.dir/rendering/utils/text2D.cpp.i

CMakeFiles/Space.dir/rendering/utils/text2D.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Space.dir/rendering/utils/text2D.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/greg/Documents/Projects/C++/space/rendering/utils/text2D.cpp -o CMakeFiles/Space.dir/rendering/utils/text2D.cpp.s

CMakeFiles/Space.dir/rendering/utils/text2D.cpp.o.requires:

.PHONY : CMakeFiles/Space.dir/rendering/utils/text2D.cpp.o.requires

CMakeFiles/Space.dir/rendering/utils/text2D.cpp.o.provides: CMakeFiles/Space.dir/rendering/utils/text2D.cpp.o.requires
	$(MAKE) -f CMakeFiles/Space.dir/build.make CMakeFiles/Space.dir/rendering/utils/text2D.cpp.o.provides.build
.PHONY : CMakeFiles/Space.dir/rendering/utils/text2D.cpp.o.provides

CMakeFiles/Space.dir/rendering/utils/text2D.cpp.o.provides.build: CMakeFiles/Space.dir/rendering/utils/text2D.cpp.o


CMakeFiles/Space.dir/rendering/utils/texture.cpp.o: CMakeFiles/Space.dir/flags.make
CMakeFiles/Space.dir/rendering/utils/texture.cpp.o: ../rendering/utils/texture.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/greg/Documents/Projects/C++/space/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/Space.dir/rendering/utils/texture.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Space.dir/rendering/utils/texture.cpp.o -c /home/greg/Documents/Projects/C++/space/rendering/utils/texture.cpp

CMakeFiles/Space.dir/rendering/utils/texture.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Space.dir/rendering/utils/texture.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/greg/Documents/Projects/C++/space/rendering/utils/texture.cpp > CMakeFiles/Space.dir/rendering/utils/texture.cpp.i

CMakeFiles/Space.dir/rendering/utils/texture.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Space.dir/rendering/utils/texture.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/greg/Documents/Projects/C++/space/rendering/utils/texture.cpp -o CMakeFiles/Space.dir/rendering/utils/texture.cpp.s

CMakeFiles/Space.dir/rendering/utils/texture.cpp.o.requires:

.PHONY : CMakeFiles/Space.dir/rendering/utils/texture.cpp.o.requires

CMakeFiles/Space.dir/rendering/utils/texture.cpp.o.provides: CMakeFiles/Space.dir/rendering/utils/texture.cpp.o.requires
	$(MAKE) -f CMakeFiles/Space.dir/build.make CMakeFiles/Space.dir/rendering/utils/texture.cpp.o.provides.build
.PHONY : CMakeFiles/Space.dir/rendering/utils/texture.cpp.o.provides

CMakeFiles/Space.dir/rendering/utils/texture.cpp.o.provides.build: CMakeFiles/Space.dir/rendering/utils/texture.cpp.o


CMakeFiles/Space.dir/common/controls.cpp.o: CMakeFiles/Space.dir/flags.make
CMakeFiles/Space.dir/common/controls.cpp.o: ../common/controls.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/greg/Documents/Projects/C++/space/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/Space.dir/common/controls.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Space.dir/common/controls.cpp.o -c /home/greg/Documents/Projects/C++/space/common/controls.cpp

CMakeFiles/Space.dir/common/controls.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Space.dir/common/controls.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/greg/Documents/Projects/C++/space/common/controls.cpp > CMakeFiles/Space.dir/common/controls.cpp.i

CMakeFiles/Space.dir/common/controls.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Space.dir/common/controls.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/greg/Documents/Projects/C++/space/common/controls.cpp -o CMakeFiles/Space.dir/common/controls.cpp.s

CMakeFiles/Space.dir/common/controls.cpp.o.requires:

.PHONY : CMakeFiles/Space.dir/common/controls.cpp.o.requires

CMakeFiles/Space.dir/common/controls.cpp.o.provides: CMakeFiles/Space.dir/common/controls.cpp.o.requires
	$(MAKE) -f CMakeFiles/Space.dir/build.make CMakeFiles/Space.dir/common/controls.cpp.o.provides.build
.PHONY : CMakeFiles/Space.dir/common/controls.cpp.o.provides

CMakeFiles/Space.dir/common/controls.cpp.o.provides.build: CMakeFiles/Space.dir/common/controls.cpp.o


CMakeFiles/Space.dir/common/delta.cpp.o: CMakeFiles/Space.dir/flags.make
CMakeFiles/Space.dir/common/delta.cpp.o: ../common/delta.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/greg/Documents/Projects/C++/space/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/Space.dir/common/delta.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Space.dir/common/delta.cpp.o -c /home/greg/Documents/Projects/C++/space/common/delta.cpp

CMakeFiles/Space.dir/common/delta.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Space.dir/common/delta.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/greg/Documents/Projects/C++/space/common/delta.cpp > CMakeFiles/Space.dir/common/delta.cpp.i

CMakeFiles/Space.dir/common/delta.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Space.dir/common/delta.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/greg/Documents/Projects/C++/space/common/delta.cpp -o CMakeFiles/Space.dir/common/delta.cpp.s

CMakeFiles/Space.dir/common/delta.cpp.o.requires:

.PHONY : CMakeFiles/Space.dir/common/delta.cpp.o.requires

CMakeFiles/Space.dir/common/delta.cpp.o.provides: CMakeFiles/Space.dir/common/delta.cpp.o.requires
	$(MAKE) -f CMakeFiles/Space.dir/build.make CMakeFiles/Space.dir/common/delta.cpp.o.provides.build
.PHONY : CMakeFiles/Space.dir/common/delta.cpp.o.provides

CMakeFiles/Space.dir/common/delta.cpp.o.provides.build: CMakeFiles/Space.dir/common/delta.cpp.o


CMakeFiles/Space.dir/space.cpp.o: CMakeFiles/Space.dir/flags.make
CMakeFiles/Space.dir/space.cpp.o: ../space.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/greg/Documents/Projects/C++/space/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/Space.dir/space.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Space.dir/space.cpp.o -c /home/greg/Documents/Projects/C++/space/space.cpp

CMakeFiles/Space.dir/space.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Space.dir/space.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/greg/Documents/Projects/C++/space/space.cpp > CMakeFiles/Space.dir/space.cpp.i

CMakeFiles/Space.dir/space.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Space.dir/space.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/greg/Documents/Projects/C++/space/space.cpp -o CMakeFiles/Space.dir/space.cpp.s

CMakeFiles/Space.dir/space.cpp.o.requires:

.PHONY : CMakeFiles/Space.dir/space.cpp.o.requires

CMakeFiles/Space.dir/space.cpp.o.provides: CMakeFiles/Space.dir/space.cpp.o.requires
	$(MAKE) -f CMakeFiles/Space.dir/build.make CMakeFiles/Space.dir/space.cpp.o.provides.build
.PHONY : CMakeFiles/Space.dir/space.cpp.o.provides

CMakeFiles/Space.dir/space.cpp.o.provides.build: CMakeFiles/Space.dir/space.cpp.o


# Object files for target Space
Space_OBJECTS = \
"CMakeFiles/Space.dir/physics.cpp.o" \
"CMakeFiles/Space.dir/rendering/renderer.cpp.o" \
"CMakeFiles/Space.dir/rendering/utils/shader.cpp.o" \
"CMakeFiles/Space.dir/rendering/utils/text2D.cpp.o" \
"CMakeFiles/Space.dir/rendering/utils/texture.cpp.o" \
"CMakeFiles/Space.dir/common/controls.cpp.o" \
"CMakeFiles/Space.dir/common/delta.cpp.o" \
"CMakeFiles/Space.dir/space.cpp.o"

# External object files for target Space
Space_EXTERNAL_OBJECTS =

Space: CMakeFiles/Space.dir/physics.cpp.o
Space: CMakeFiles/Space.dir/rendering/renderer.cpp.o
Space: CMakeFiles/Space.dir/rendering/utils/shader.cpp.o
Space: CMakeFiles/Space.dir/rendering/utils/text2D.cpp.o
Space: CMakeFiles/Space.dir/rendering/utils/texture.cpp.o
Space: CMakeFiles/Space.dir/common/controls.cpp.o
Space: CMakeFiles/Space.dir/common/delta.cpp.o
Space: CMakeFiles/Space.dir/space.cpp.o
Space: CMakeFiles/Space.dir/build.make
Space: /usr/lib/libGL.so
Space: /usr/lib/libGLU.so
Space: /usr/lib/libGLEW.so
Space: /usr/lib/libglfw.so
Space: CMakeFiles/Space.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/greg/Documents/Projects/C++/space/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Linking CXX executable Space"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Space.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Space.dir/build: Space

.PHONY : CMakeFiles/Space.dir/build

CMakeFiles/Space.dir/requires: CMakeFiles/Space.dir/physics.cpp.o.requires
CMakeFiles/Space.dir/requires: CMakeFiles/Space.dir/rendering/renderer.cpp.o.requires
CMakeFiles/Space.dir/requires: CMakeFiles/Space.dir/rendering/utils/shader.cpp.o.requires
CMakeFiles/Space.dir/requires: CMakeFiles/Space.dir/rendering/utils/text2D.cpp.o.requires
CMakeFiles/Space.dir/requires: CMakeFiles/Space.dir/rendering/utils/texture.cpp.o.requires
CMakeFiles/Space.dir/requires: CMakeFiles/Space.dir/common/controls.cpp.o.requires
CMakeFiles/Space.dir/requires: CMakeFiles/Space.dir/common/delta.cpp.o.requires
CMakeFiles/Space.dir/requires: CMakeFiles/Space.dir/space.cpp.o.requires

.PHONY : CMakeFiles/Space.dir/requires

CMakeFiles/Space.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Space.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Space.dir/clean

CMakeFiles/Space.dir/depend:
	cd /home/greg/Documents/Projects/C++/space/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/greg/Documents/Projects/C++/space /home/greg/Documents/Projects/C++/space /home/greg/Documents/Projects/C++/space/build /home/greg/Documents/Projects/C++/space/build /home/greg/Documents/Projects/C++/space/build/CMakeFiles/Space.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Space.dir/depend

