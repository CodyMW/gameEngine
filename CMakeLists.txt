# Copyright (c) 2024 [Your Name]
# All Rights Reserved
# 
# This file is part of [Your Game Engine Name].
# 
# The use, copying, modification, merging, publication, distribution, sublicensing, 
# and/or selling of this software requires explicit written permission from the copyright holder.

cmake_minimum_required(VERSION 3.14)
project(GameEngine VERSION 0.1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Options
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)
option(BUILD_EXAMPLES "Build example applications" ON)

# Find required packages
find_package(OpenGL REQUIRED)

# Add subdirectories
add_subdirectory(src)

# Examples
if(BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

# Installation
install(DIRECTORY include/ DESTINATION include) 