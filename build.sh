#!/bin/bash
# Build script for GameEngine project
# Copyright (c) 2024 Cody Wall

# Parse command line arguments
CLEAN=0
BUILD_TYPE="Debug"
BUILD_EXAMPLES="OFF"
BUILD_TESTS="OFF"
RUN_AFTER_BUILD=0

for arg in "$@"; do
    case $arg in
        --clean)
            CLEAN=1
            ;;
        --release)
            BUILD_TYPE="Release"
            ;;
        --examples)
            BUILD_EXAMPLES="ON"
            ;;
        --tests)
            BUILD_TESTS="ON"
            ;;
        --run)
            RUN_AFTER_BUILD=1
            ;;
    esac
done

# Get the project root directory (where this script is located)
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
PROJECT_ROOT="$SCRIPT_DIR"

# Create build directory if it doesn't exist
if [ ! -d "$PROJECT_ROOT/build" ]; then
    mkdir -p "$PROJECT_ROOT/build"
fi

# Clean build directory if requested
if [ $CLEAN -eq 1 ] && [ -d "$PROJECT_ROOT/build" ]; then
    echo "Cleaning build directory..."
    rm -rf "$PROJECT_ROOT/build"/*
fi

# Configure and build the project
echo "Configuring project with CMake in $BUILD_TYPE mode..."
cd "$PROJECT_ROOT/build"

# Determine generator based on platform
GENERATOR=""
if [ "$(uname)" == "Darwin" ]; then
    # macOS - use Xcode if available
    if command -v xcodebuild &> /dev/null; then
        GENERATOR="-G Xcode"
    fi
fi

# Run CMake configure
cmake $GENERATOR -DCMAKE_BUILD_TYPE=$BUILD_TYPE -DBUILD_EXAMPLES=$BUILD_EXAMPLES -DBUILD_TESTS=$BUILD_TESTS ..
if [ $? -ne 0 ]; then
    echo "Error configuring project"
    exit 1
fi

# Build the project
echo "Building project..."
cmake --build . --config $BUILD_TYPE
if [ $? -ne 0 ]; then
    echo "Error building project"
    exit 1
fi

echo "Build completed successfully in $BUILD_TYPE mode!"

# Run the application if requested
if [ $RUN_AFTER_BUILD -eq 1 ]; then
    echo "Running application..."
    if [ "$(uname)" == "Darwin" ] || [ "$(uname)" == "Linux" ]; then
        APP_PATH="$PROJECT_ROOT/build/bin/GameEngine_App"
        if [ ! -f "$APP_PATH" ]; then
            APP_PATH="$PROJECT_ROOT/build/bin/$BUILD_TYPE/GameEngine_App"
        fi
    fi
    
    if [ -f "$APP_PATH" ]; then
        "$APP_PATH"
    else
        echo "Cannot find executable at $APP_PATH"
        exit 1
    fi
fi

exit 0 