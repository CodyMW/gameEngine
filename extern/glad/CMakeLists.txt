cmake_minimum_required(VERSION 3.14)
project(glad C)

# Add include directory
include_directories(include)

# Create the GLAD library
add_library(glad src/glad.c)

# Set include directories
target_include_directories(glad 
    PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Link with required libraries
if(WIN32)
    target_link_libraries(glad PRIVATE opengl32)
else()
    target_link_libraries(glad PRIVATE ${OPENGL_LIBRARIES})
endif()

# Set properties
set_target_properties(glad PROPERTIES
    C_STANDARD 99
    C_STANDARD_REQUIRED ON
) 