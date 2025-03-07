# Copyright (c) 2024 Cody Wall
# All Rights Reserved

# Define the engine library
set(ENGINE_NAME "GameEngine")

# Check if main.cpp exists
if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp")
    # Create a simple main.cpp if it doesn't exist
    file(WRITE "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp" "
/**
 * @file main.cpp
 * @brief Entry point for the Game Engine
 * @copyright Copyright (c) 2024 Cody Wall
 */

#include <iostream>

int main() {
    std::cout << \"Starting Game Engine...\" << std::endl;
    std::cout << \"This is a placeholder. Please implement the engine functionality.\" << std::endl;
    return 0;
}
")
    message(STATUS "Created a placeholder main.cpp file")
endif()

# Collect all source files recursively
file(GLOB_RECURSE ENGINE_SOURCES 
    "*.cpp"
    "*.c"
)

file(GLOB_RECURSE ENGINE_HEADERS 
    "*.hpp"
    "*.h"
)

# Remove main.cpp from the engine library sources
list(FILTER ENGINE_SOURCES EXCLUDE REGEX ".*main\\.cpp$")

# Create the engine library
if(BUILD_SHARED_LIBS)
    add_library(${ENGINE_NAME} SHARED ${ENGINE_SOURCES} ${ENGINE_HEADERS})
else()
    add_library(${ENGINE_NAME} STATIC ${ENGINE_SOURCES} ${ENGINE_HEADERS})
endif()

# Set include directories
target_include_directories(${ENGINE_NAME} 
    PUBLIC 
        ${CMAKE_SOURCE_DIR}/include
    PRIVATE 
        ${CMAKE_CURRENT_SOURCE_DIR}
)

# Link dependencies
target_link_libraries(${ENGINE_NAME} 
    PUBLIC
        OpenGL::GL
)

# Link GLFW if found
if(GLFW_FOUND)
    target_link_libraries(${ENGINE_NAME} PUBLIC glfw)
endif()

# Link GLAD if found
if(GLAD_FOUND)
    target_link_libraries(${ENGINE_NAME} PRIVATE glad)
endif()

# Add other dependencies as needed
# target_link_libraries(${ENGINE_NAME} PRIVATE assimp freetype imgui)

# Create the main executable
add_executable(${ENGINE_NAME}_App main.cpp)
target_link_libraries(${ENGINE_NAME}_App PRIVATE ${ENGINE_NAME})

# Install targets
install(TARGETS ${ENGINE_NAME} ${ENGINE_NAME}_App
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
) 