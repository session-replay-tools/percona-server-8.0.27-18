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
CMAKE_SOURCE_DIR = /mnt/jenkins/workspace/ps8.0-autobuild-RELEASE/test/percona-server

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/jenkins/workspace/ps8.0-autobuild-RELEASE/test/percona-server

# Include any dependencies generated for this target.
include extra/libkmip/kmippp/CMakeFiles/kmippp.dir/depend.make

# Include the progress variables for this target.
include extra/libkmip/kmippp/CMakeFiles/kmippp.dir/progress.make

# Include the compile flags for this target's objects.
include extra/libkmip/kmippp/CMakeFiles/kmippp.dir/flags.make

extra/libkmip/kmippp/CMakeFiles/kmippp.dir/kmippp.cpp.o: extra/libkmip/kmippp/CMakeFiles/kmippp.dir/flags.make
extra/libkmip/kmippp/CMakeFiles/kmippp.dir/kmippp.cpp.o: extra/libkmip/kmippp/kmippp.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/jenkins/workspace/ps8.0-autobuild-RELEASE/test/percona-server/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object extra/libkmip/kmippp/CMakeFiles/kmippp.dir/kmippp.cpp.o"
	cd /mnt/jenkins/workspace/ps8.0-autobuild-RELEASE/test/percona-server/extra/libkmip/kmippp && /usr/bin/g++-8  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/kmippp.dir/kmippp.cpp.o -c /mnt/jenkins/workspace/ps8.0-autobuild-RELEASE/test/percona-server/extra/libkmip/kmippp/kmippp.cpp

extra/libkmip/kmippp/CMakeFiles/kmippp.dir/kmippp.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/kmippp.dir/kmippp.cpp.i"
	cd /mnt/jenkins/workspace/ps8.0-autobuild-RELEASE/test/percona-server/extra/libkmip/kmippp && /usr/bin/g++-8 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/jenkins/workspace/ps8.0-autobuild-RELEASE/test/percona-server/extra/libkmip/kmippp/kmippp.cpp > CMakeFiles/kmippp.dir/kmippp.cpp.i

extra/libkmip/kmippp/CMakeFiles/kmippp.dir/kmippp.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/kmippp.dir/kmippp.cpp.s"
	cd /mnt/jenkins/workspace/ps8.0-autobuild-RELEASE/test/percona-server/extra/libkmip/kmippp && /usr/bin/g++-8 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/jenkins/workspace/ps8.0-autobuild-RELEASE/test/percona-server/extra/libkmip/kmippp/kmippp.cpp -o CMakeFiles/kmippp.dir/kmippp.cpp.s

extra/libkmip/kmippp/CMakeFiles/kmippp.dir/kmippp.cpp.o.requires:

.PHONY : extra/libkmip/kmippp/CMakeFiles/kmippp.dir/kmippp.cpp.o.requires

extra/libkmip/kmippp/CMakeFiles/kmippp.dir/kmippp.cpp.o.provides: extra/libkmip/kmippp/CMakeFiles/kmippp.dir/kmippp.cpp.o.requires
	$(MAKE) -f extra/libkmip/kmippp/CMakeFiles/kmippp.dir/build.make extra/libkmip/kmippp/CMakeFiles/kmippp.dir/kmippp.cpp.o.provides.build
.PHONY : extra/libkmip/kmippp/CMakeFiles/kmippp.dir/kmippp.cpp.o.provides

extra/libkmip/kmippp/CMakeFiles/kmippp.dir/kmippp.cpp.o.provides.build: extra/libkmip/kmippp/CMakeFiles/kmippp.dir/kmippp.cpp.o


# Object files for target kmippp
kmippp_OBJECTS = \
"CMakeFiles/kmippp.dir/kmippp.cpp.o"

# External object files for target kmippp
kmippp_EXTERNAL_OBJECTS =

extra/libkmip/kmippp/libkmippp.a: extra/libkmip/kmippp/CMakeFiles/kmippp.dir/kmippp.cpp.o
extra/libkmip/kmippp/libkmippp.a: extra/libkmip/kmippp/CMakeFiles/kmippp.dir/build.make
extra/libkmip/kmippp/libkmippp.a: extra/libkmip/kmippp/CMakeFiles/kmippp.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/jenkins/workspace/ps8.0-autobuild-RELEASE/test/percona-server/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libkmippp.a"
	cd /mnt/jenkins/workspace/ps8.0-autobuild-RELEASE/test/percona-server/extra/libkmip/kmippp && $(CMAKE_COMMAND) -P CMakeFiles/kmippp.dir/cmake_clean_target.cmake
	cd /mnt/jenkins/workspace/ps8.0-autobuild-RELEASE/test/percona-server/extra/libkmip/kmippp && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/kmippp.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
extra/libkmip/kmippp/CMakeFiles/kmippp.dir/build: extra/libkmip/kmippp/libkmippp.a

.PHONY : extra/libkmip/kmippp/CMakeFiles/kmippp.dir/build

extra/libkmip/kmippp/CMakeFiles/kmippp.dir/requires: extra/libkmip/kmippp/CMakeFiles/kmippp.dir/kmippp.cpp.o.requires

.PHONY : extra/libkmip/kmippp/CMakeFiles/kmippp.dir/requires

extra/libkmip/kmippp/CMakeFiles/kmippp.dir/clean:
	cd /mnt/jenkins/workspace/ps8.0-autobuild-RELEASE/test/percona-server/extra/libkmip/kmippp && $(CMAKE_COMMAND) -P CMakeFiles/kmippp.dir/cmake_clean.cmake
.PHONY : extra/libkmip/kmippp/CMakeFiles/kmippp.dir/clean

extra/libkmip/kmippp/CMakeFiles/kmippp.dir/depend:
	cd /mnt/jenkins/workspace/ps8.0-autobuild-RELEASE/test/percona-server && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/jenkins/workspace/ps8.0-autobuild-RELEASE/test/percona-server /mnt/jenkins/workspace/ps8.0-autobuild-RELEASE/test/percona-server/extra/libkmip/kmippp /mnt/jenkins/workspace/ps8.0-autobuild-RELEASE/test/percona-server /mnt/jenkins/workspace/ps8.0-autobuild-RELEASE/test/percona-server/extra/libkmip/kmippp /mnt/jenkins/workspace/ps8.0-autobuild-RELEASE/test/percona-server/extra/libkmip/kmippp/CMakeFiles/kmippp.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : extra/libkmip/kmippp/CMakeFiles/kmippp.dir/depend

