# Generated by CMake

if("${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}" LESS 2.5)
   message(FATAL_ERROR "CMake >= 2.6.0 required")
endif()
cmake_policy(PUSH)
cmake_policy(VERSION 2.6)
#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Protect against multiple inclusion, which would fail when already imported targets are added once more.
set(_targetsDefined)
set(_targetsNotDefined)
set(_expectedTargets)
foreach(_expectedTarget kmip kmippp)
  list(APPEND _expectedTargets ${_expectedTarget})
  if(NOT TARGET ${_expectedTarget})
    list(APPEND _targetsNotDefined ${_expectedTarget})
  endif()
  if(TARGET ${_expectedTarget})
    list(APPEND _targetsDefined ${_expectedTarget})
  endif()
endforeach()
if("${_targetsDefined}" STREQUAL "${_expectedTargets}")
  unset(_targetsDefined)
  unset(_targetsNotDefined)
  unset(_expectedTargets)
  set(CMAKE_IMPORT_FILE_VERSION)
  cmake_policy(POP)
  return()
endif()
if(NOT "${_targetsDefined}" STREQUAL "")
  message(FATAL_ERROR "Some (but not all) targets in this export set were already defined.\nTargets Defined: ${_targetsDefined}\nTargets not yet defined: ${_targetsNotDefined}\n")
endif()
unset(_targetsDefined)
unset(_targetsNotDefined)
unset(_expectedTargets)


# Create imported target kmip
add_library(kmip STATIC IMPORTED)

set_target_properties(kmip PROPERTIES
  INTERFACE_INCLUDE_DIRECTORIES "/mnt/jenkins/workspace/ps8.0-autobuild-RELEASE/test/percona-server/extra/libkmip/libkmip/include/"
)

# Create imported target kmippp
add_library(kmippp STATIC IMPORTED)

set_target_properties(kmippp PROPERTIES
  INTERFACE_INCLUDE_DIRECTORIES "/mnt/jenkins/workspace/ps8.0-autobuild-RELEASE/test/percona-server/extra/libkmip/kmippp/"
)

# Import target "kmip" for configuration "RelWithDebInfo"
set_property(TARGET kmip APPEND PROPERTY IMPORTED_CONFIGURATIONS RELWITHDEBINFO)
set_target_properties(kmip PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELWITHDEBINFO "C"
  IMPORTED_LINK_INTERFACE_LIBRARIES_RELWITHDEBINFO "-lpthread;/usr/lib/x86_64-linux-gnu/libssl.so;/usr/lib/x86_64-linux-gnu/libcrypto.so"
  IMPORTED_LOCATION_RELWITHDEBINFO "/mnt/jenkins/workspace/ps8.0-autobuild-RELEASE/test/percona-server/extra/libkmip/libkmip/src/libkmip.a"
  )

# Import target "kmippp" for configuration "RelWithDebInfo"
set_property(TARGET kmippp APPEND PROPERTY IMPORTED_CONFIGURATIONS RELWITHDEBINFO)
set_target_properties(kmippp PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELWITHDEBINFO "CXX"
  IMPORTED_LINK_INTERFACE_LIBRARIES_RELWITHDEBINFO "-lpthread;kmip"
  IMPORTED_LOCATION_RELWITHDEBINFO "/mnt/jenkins/workspace/ps8.0-autobuild-RELEASE/test/percona-server/extra/libkmip/kmippp/libkmippp.a"
  )

# This file does not depend on other imported targets which have
# been exported from the same project but in a separate export set.

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
cmake_policy(POP)
