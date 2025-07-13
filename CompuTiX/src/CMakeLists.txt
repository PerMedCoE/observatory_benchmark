cmake_minimum_required( VERSION 3.25 )

# Create an initial project
project( simulation )

set( CMAKE_CXX_STANDARD 20 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )

# Set default build
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Setting build type to 'Release' as none was specified.")
  set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose the type of build." FORCE)
  # Set the possible values of build type for cmake-gui
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

# Define resulting executables and associate them with source files
add_executable( simulation )
target_sources( simulation 
                PRIVATE main.cpp )

# Find CompuTiX and link it to resulting binary
find_package( CompuTiX REQUIRED Core Actions )
target_link_libraries( simulation
                       PRIVATE CompuTiX::Core
                       PRIVATE CompuTiX::Actions
                       )
