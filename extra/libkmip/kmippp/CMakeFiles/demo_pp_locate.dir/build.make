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
include extra/libkmip/kmippp/CMakeFiles/demo_pp_locate.dir/depend.make

# Include the progress variables for this target.
include extra/libkmip/kmippp/CMakeFiles/demo_pp_locate.dir/progress.make

# Include the compile flags for this target's objects.
include extra/libkmip/kmippp/CMakeFiles/demo_pp_locate.dir/flags.make

extra/libkmip/kmippp/CMakeFiles/demo_pp_locate.dir/demo_locate.cpp.o: extra/libkmip/kmippp/CMakeFiles/demo_pp_locate.dir/flags.make
extra/libkmip/kmippp/CMakeFiles/demo_pp_locate.dir/demo_locate.cpp.o: extra/libkmip/kmippp/demo_locate.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/jenkins/workspace/ps8.0-autobuild-RELEASE/test/percona-server/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object extra/libkmip/kmippp/CMakeFiles/demo_pp_locate.dir/demo_locate.cpp.o"
	cd /mnt/jenkins/workspace/ps8.0-autobuild-RELEASE/test/percona-server/extra/libkmip/kmippp && /usr/bin/g++-8  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/demo_pp_locate.dir/demo_locate.cpp.o -c /mnt/jenkins/workspace/ps8.0-autobuild-RELEASE/test/percona-server/extra/libkmip/kmippp/demo_locate.cpp

extra/libkmip/kmippp/CMakeFiles/demo_pp_locate.dir/demo_locate.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/demo_pp_locate.dir/demo_locate.cpp.i"
	cd /mnt/jenkins/workspace/ps8.0-autobuild-RELEASE/test/percona-server/extra/libkmip/kmippp && /usr/bin/g++-8 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/jenkins/workspace/ps8.0-autobuild-RELEASE/test/percona-server/extra/libkmip/kmippp/demo_locate.cpp > CMakeFiles/demo_pp_locate.dir/demo_locate.cpp.i

extra/libkmip/kmippp/CMakeFiles/demo_pp_locate.dir/demo_locate.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/demo_pp_locate.dir/demo_locate.cpp.s"
	cd /mnt/jenkins/workspace/ps8.0-autobuild-RELEASE/test/percona-server/extra/libkmip/kmippp && /usr/bin/g++-8 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/jenkins/workspace/ps8.0-autobuild-RELEASE/test/percona-server/extra/libkmip/kmippp/demo_locate.cpp -o CMakeFiles/demo_pp_locate.dir/demo_locate.cpp.s

extra/libkmip/kmippp/CMakeFiles/demo_pp_locate.dir/demo_locate.cpp.o.requires:

.PHONY : extra/libkmip/kmippp/CMakeFiles/demo_pp_locate.dir/demo_locate.cpp.o.requires

extra/libkmip/kmippp/CMakeFiles/demo_pp_locate.dir/demo_locate.cpp.o.provides: extra/libkmip/kmippp/CMakeFiles/demo_pp_locate.dir/demo_locate.cpp.o.requires
	$(MAKE) -f extra/libkmip/kmippp/CMakeFiles/demo_pp_locate.dir/build.make extra/libkmip/kmippp/CMakeFiles/demo_pp_locate.dir/demo_locate.cpp.o.provides.build
.PHONY : extra/libkmip/kmippp/CMakeFiles/demo_pp_locate.dir/demo_locate.cpp.o.provides

extra/libkmip/kmippp/CMakeFiles/demo_pp_locate.dir/demo_locate.cpp.o.provides.build: extra/libkmip/kmippp/CMakeFiles/demo_pp_locate.dir/demo_locate.cpp.o


# Object files for target demo_pp_locate
demo_pp_locate_OBJECTS = \
"CMakeFiles/demo_pp_locate.dir/demo_locate.cpp.o"

# External object files for target demo_pp_locate
demo_pp_locate_EXTERNAL_OBJECTS =

extra/libkmip/kmippp/demo_pp_locate: extra/libkmip/kmippp/CMakeFiles/demo_pp_locate.dir/demo_locate.cpp.o
extra/libkmip/kmippp/demo_pp_locate: extra/libkmip/kmippp/CMakeFiles/demo_pp_locate.dir/build.make
extra/libkmip/kmippp/demo_pp_locate: extra/libkmip/kmippp/libkmippp.a
extra/libkmip/kmippp/demo_pp_locate: extra/libkmip/libkmip/src/libkmip.a
extra/libkmip/kmippp/demo_pp_locate: /usr/lib/x86_64-linux-gnu/libssl.so
extra/libkmip/kmippp/demo_pp_locate: /usr/lib/x86_64-linux-gnu/libcrypto.so
extra/libkmip/kmippp/demo_pp_locate: extra/libkmip/kmippp/CMakeFiles/demo_pp_locate.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/jenkins/workspace/ps8.0-autobuild-RELEASE/test/percona-server/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable demo_pp_locate"
	cd /mnt/jenkins/workspace/ps8.0-autobuild-RELEASE/test/percona-server/extra/libkmip/kmippp && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/demo_pp_locate.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
extra/libkmip/kmippp/CMakeFiles/demo_pp_locate.dir/build: extra/libkmip/kmippp/demo_pp_locate

.PHONY : extra/libkmip/kmippp/CMakeFiles/demo_pp_locate.dir/build

extra/libkmip/kmippp/CMakeFiles/demo_pp_locate.dir/requires: extra/libkmip/kmippp/CMakeFiles/demo_pp_locate.dir/demo_locate.cpp.o.requires

.PHONY : extra/libkmip/kmippp/CMakeFiles/demo_pp_locate.dir/requires

extra/libkmip/kmippp/CMakeFiles/demo_pp_locate.dir/clean:
	cd /mnt/jenkins/workspace/ps8.0-autobuild-RELEASE/test/percona-server/extra/libkmip/kmippp && $(CMAKE_COMMAND) -P CMakeFiles/demo_pp_locate.dir/cmake_clean.cmake
.PHONY : extra/libkmip/kmippp/CMakeFiles/demo_pp_locate.dir/clean

extra/libkmip/kmippp/CMakeFiles/demo_pp_locate.dir/depend:
	cd /mnt/jenkins/workspace/ps8.0-autobuild-RELEASE/test/percona-server && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/jenkins/workspace/ps8.0-autobuild-RELEASE/test/percona-server /mnt/jenkins/workspace/ps8.0-autobuild-RELEASE/test/percona-server/extra/libkmip/kmippp /mnt/jenkins/workspace/ps8.0-autobuild-RELEASE/test/percona-server /mnt/jenkins/workspace/ps8.0-autobuild-RELEASE/test/percona-server/extra/libkmip/kmippp /mnt/jenkins/workspace/ps8.0-autobuild-RELEASE/test/percona-server/extra/libkmip/kmippp/CMakeFiles/demo_pp_locate.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : extra/libkmip/kmippp/CMakeFiles/demo_pp_locate.dir/depend

