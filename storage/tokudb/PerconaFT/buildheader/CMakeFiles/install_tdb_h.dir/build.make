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

# Utility rule file for install_tdb_h.

# Include the progress variables for this target.
include storage/tokudb/PerconaFT/buildheader/CMakeFiles/install_tdb_h.dir/progress.make

storage/tokudb/PerconaFT/buildheader/CMakeFiles/install_tdb_h: storage/tokudb/PerconaFT/buildheader/db.h


storage/tokudb/PerconaFT/buildheader/db.h: storage/tokudb/PerconaFT/buildheader/make_tdb
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/mnt/jenkins/workspace/ps8.0-autobuild-RELEASE/test/percona-server/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating db.h"
	cd /mnt/jenkins/workspace/ps8.0-autobuild-RELEASE/test/percona-server/storage/tokudb/PerconaFT/buildheader && bash runcat.sh /mnt/jenkins/workspace/ps8.0-autobuild-RELEASE/test/percona-server/storage/tokudb/PerconaFT/buildheader/db.h /mnt/jenkins/workspace/ps8.0-autobuild-RELEASE/test/percona-server/storage/tokudb/PerconaFT/buildheader/make_tdb

install_tdb_h: storage/tokudb/PerconaFT/buildheader/CMakeFiles/install_tdb_h
install_tdb_h: storage/tokudb/PerconaFT/buildheader/db.h
install_tdb_h: storage/tokudb/PerconaFT/buildheader/CMakeFiles/install_tdb_h.dir/build.make

.PHONY : install_tdb_h

# Rule to build all files generated by this target.
storage/tokudb/PerconaFT/buildheader/CMakeFiles/install_tdb_h.dir/build: install_tdb_h

.PHONY : storage/tokudb/PerconaFT/buildheader/CMakeFiles/install_tdb_h.dir/build

storage/tokudb/PerconaFT/buildheader/CMakeFiles/install_tdb_h.dir/clean:
	cd /mnt/jenkins/workspace/ps8.0-autobuild-RELEASE/test/percona-server/storage/tokudb/PerconaFT/buildheader && $(CMAKE_COMMAND) -P CMakeFiles/install_tdb_h.dir/cmake_clean.cmake
.PHONY : storage/tokudb/PerconaFT/buildheader/CMakeFiles/install_tdb_h.dir/clean

storage/tokudb/PerconaFT/buildheader/CMakeFiles/install_tdb_h.dir/depend:
	cd /mnt/jenkins/workspace/ps8.0-autobuild-RELEASE/test/percona-server && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/jenkins/workspace/ps8.0-autobuild-RELEASE/test/percona-server /mnt/jenkins/workspace/ps8.0-autobuild-RELEASE/test/percona-server/storage/tokudb/PerconaFT/buildheader /mnt/jenkins/workspace/ps8.0-autobuild-RELEASE/test/percona-server /mnt/jenkins/workspace/ps8.0-autobuild-RELEASE/test/percona-server/storage/tokudb/PerconaFT/buildheader /mnt/jenkins/workspace/ps8.0-autobuild-RELEASE/test/percona-server/storage/tokudb/PerconaFT/buildheader/CMakeFiles/install_tdb_h.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : storage/tokudb/PerconaFT/buildheader/CMakeFiles/install_tdb_h.dir/depend

