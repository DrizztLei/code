# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.3

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
CMAKE_SOURCE_DIR = /home/elvis/work/opencv/recognition

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/elvis/work/opencv/recognition

# Include any dependencies generated for this target.
include CMakeFiles/DisplayImage.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/DisplayImage.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/DisplayImage.dir/flags.make

CMakeFiles/DisplayImage.dir/display.cpp.o: CMakeFiles/DisplayImage.dir/flags.make
CMakeFiles/DisplayImage.dir/display.cpp.o: display.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/elvis/work/opencv/recognition/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/DisplayImage.dir/display.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/DisplayImage.dir/display.cpp.o -c /home/elvis/work/opencv/recognition/display.cpp

CMakeFiles/DisplayImage.dir/display.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/DisplayImage.dir/display.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/elvis/work/opencv/recognition/display.cpp > CMakeFiles/DisplayImage.dir/display.cpp.i

CMakeFiles/DisplayImage.dir/display.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/DisplayImage.dir/display.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/elvis/work/opencv/recognition/display.cpp -o CMakeFiles/DisplayImage.dir/display.cpp.s

CMakeFiles/DisplayImage.dir/display.cpp.o.requires:

.PHONY : CMakeFiles/DisplayImage.dir/display.cpp.o.requires

CMakeFiles/DisplayImage.dir/display.cpp.o.provides: CMakeFiles/DisplayImage.dir/display.cpp.o.requires
	$(MAKE) -f CMakeFiles/DisplayImage.dir/build.make CMakeFiles/DisplayImage.dir/display.cpp.o.provides.build
.PHONY : CMakeFiles/DisplayImage.dir/display.cpp.o.provides

CMakeFiles/DisplayImage.dir/display.cpp.o.provides.build: CMakeFiles/DisplayImage.dir/display.cpp.o


# Object files for target DisplayImage
DisplayImage_OBJECTS = \
"CMakeFiles/DisplayImage.dir/display.cpp.o"

# External object files for target DisplayImage
DisplayImage_EXTERNAL_OBJECTS =

DisplayImage: CMakeFiles/DisplayImage.dir/display.cpp.o
DisplayImage: CMakeFiles/DisplayImage.dir/build.make
DisplayImage: /usr/lib64/libopencv_videostab.so.2.4.12
DisplayImage: /usr/lib64/libopencv_ts.a
DisplayImage: /usr/lib64/libopencv_superres.so.2.4.12
DisplayImage: /usr/lib64/libopencv_stitching.so.2.4.12
DisplayImage: /usr/lib64/libopencv_contrib.so.2.4.12
DisplayImage: /usr/lib64/libGLU.so
DisplayImage: /usr/lib64/libGL.so
DisplayImage: /usr/lib64/libopencv_nonfree.so.2.4.12
DisplayImage: /usr/lib64/libopencv_gpu.so.2.4.12
DisplayImage: /usr/lib64/libopencv_photo.so.2.4.12
DisplayImage: /usr/lib64/libopencv_objdetect.so.2.4.12
DisplayImage: /usr/lib64/libopencv_legacy.so.2.4.12
DisplayImage: /usr/lib64/libopencv_video.so.2.4.12
DisplayImage: /usr/lib64/libopencv_ml.so.2.4.12
DisplayImage: /usr/lib64/libopencv_calib3d.so.2.4.12
DisplayImage: /usr/lib64/libopencv_features2d.so.2.4.12
DisplayImage: /usr/lib64/libopencv_highgui.so.2.4.12
DisplayImage: /usr/lib64/libopencv_imgproc.so.2.4.12
DisplayImage: /usr/lib64/libopencv_flann.so.2.4.12
DisplayImage: /usr/lib64/libopencv_core.so.2.4.12
DisplayImage: CMakeFiles/DisplayImage.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/elvis/work/opencv/recognition/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable DisplayImage"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/DisplayImage.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/DisplayImage.dir/build: DisplayImage

.PHONY : CMakeFiles/DisplayImage.dir/build

CMakeFiles/DisplayImage.dir/requires: CMakeFiles/DisplayImage.dir/display.cpp.o.requires

.PHONY : CMakeFiles/DisplayImage.dir/requires

CMakeFiles/DisplayImage.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/DisplayImage.dir/cmake_clean.cmake
.PHONY : CMakeFiles/DisplayImage.dir/clean

CMakeFiles/DisplayImage.dir/depend:
	cd /home/elvis/work/opencv/recognition && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/elvis/work/opencv/recognition /home/elvis/work/opencv/recognition /home/elvis/work/opencv/recognition /home/elvis/work/opencv/recognition /home/elvis/work/opencv/recognition/CMakeFiles/DisplayImage.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/DisplayImage.dir/depend

