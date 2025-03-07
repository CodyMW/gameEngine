# Copyright (c) 2024 Cody Wall
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

# Output directories
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Build options
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)
option(BUILD_EXAMPLES "Build example applications" ON)
option(BUILD_TESTS "Build test applications" OFF)
option(USE_SYSTEM_DEPENDENCIES "Use system-installed dependencies instead of bundled ones" OFF)

# Set default build type if not specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Choose the type of build (Debug/Release/RelWithDebInfo/MinSizeRel)" FORCE)
endif()

# Add compiler warnings
if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Include directories
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# External dependencies
find_package(OpenGL REQUIRED)

# Check if external dependencies exist
set(GLFW_FOUND FALSE)
set(GLM_FOUND FALSE)
set(GLAD_FOUND FALSE)

# Check for system dependencies first
if(USE_SYSTEM_DEPENDENCIES)
    find_package(glfw3 QUIET)
    if(glfw3_FOUND)
        set(GLFW_FOUND TRUE)
        message(STATUS "Using system GLFW")
    endif()
    
    find_package(glm QUIET)
    if(glm_FOUND)
        set(GLM_FOUND TRUE)
        message(STATUS "Using system GLM")
    endif()
else()
    # Check for bundled dependencies
    if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/extern/glfw/CMakeLists.txt")
        set(GLFW_FOUND TRUE)
        set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
        set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
        set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
        set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
        add_subdirectory(extern/glfw)
        message(STATUS "Using bundled GLFW")
    endif()
    
    if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/extern/glm/CMakeLists.txt")
        set(GLM_FOUND TRUE)
        set(GLM_TEST_ENABLE OFF CACHE BOOL "" FORCE)
        add_subdirectory(extern/glm)
        message(STATUS "Using bundled GLM")
    endif()
    
    if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/extern/glad/CMakeLists.txt")
        set(GLAD_FOUND TRUE)
        add_subdirectory(extern/glad)
        message(STATUS "Using bundled GLAD")
    endif()
endif()

# Handle missing dependencies
if(NOT GLFW_FOUND)
    message(WARNING "GLFW not found. Please install GLFW or clone it to extern/glfw")
    message(STATUS "You can run: git clone https://github.com/glfw/glfw.git extern/glfw")
endif()

if(NOT GLM_FOUND)
    message(WARNING "GLM not found. Please install GLM or clone it to extern/glm")
    message(STATUS "You can run: git clone https://github.com/g-truc/glm.git extern/glm")
endif()

if(NOT GLAD_FOUND)
    message(WARNING "GLAD not found. Please install GLAD or clone it to extern/glad")
    message(STATUS "You can download GLAD from: https://glad.dav1d.de/")
endif()

# Add other dependencies as needed (commented out until you need them)
# add_subdirectory(extern/assimp)
# add_subdirectory(extern/freetype)
# add_subdirectory(extern/imgui)

# Add engine source if dependencies are available
if(GLFW_FOUND AND GLM_FOUND)
    add_subdirectory(src)
else()
    message(FATAL_ERROR "Missing required dependencies. Please install them before continuing.")
endif()

# Examples
if(BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

# Tests
if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

# Installation
install(DIRECTORY include/ DESTINATION include) 