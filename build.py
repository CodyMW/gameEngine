#!/usr/bin/env python3
"""
Build script for GameEngine project
Copyright (c) 2024 Cody Wall
"""

import os
import sys
import platform
import subprocess
import argparse
from pathlib import Path

def main():
    # Parse command line arguments
    parser = argparse.ArgumentParser(description='Build the GameEngine project')
    parser.add_argument('--clean', action='store_true', help='Clean the build directory before building')
    parser.add_argument('--release', action='store_true', help='Build in Release mode (default is Debug)')
    parser.add_argument('--examples', action='store_true', help='Build examples')
    parser.add_argument('--tests', action='store_true', help='Build tests')
    parser.add_argument('--run', action='store_true', help='Run the application after building')
    args = parser.parse_args()

    # Get the project root directory (where this script is located)
    project_root = Path(os.path.dirname(os.path.abspath(__file__)))

    # Create build directory if it doesn't exist
    build_dir = project_root / "build"
    if not build_dir.exists():
        os.makedirs(build_dir)
    
    # Clean build directory if requested
    if args.clean and build_dir.exists():
        print("Cleaning build directory...")
        for item in os.listdir(build_dir):
            item_path = build_dir / item
            if item_path.is_file():
                os.remove(item_path)
            elif item_path.is_dir():
                import shutil
                shutil.rmtree(item_path)
    
    # Determine build type
    build_type = "Release" if args.release else "Debug"
    
    # Determine generator based on platform
    generator = None
    if platform.system() == "Windows":
        generator = "Visual Studio 17 2022"  # Change this to match your Visual Studio version
    
    # Build CMake command
    cmake_cmd = ["cmake"]
    
    # Add generator if specified
    if generator:
        cmake_cmd.extend(["-G", generator])
    
    # Add build type
    cmake_cmd.extend(["-DCMAKE_BUILD_TYPE=" + build_type])
    
    # Add other options
    if args.examples:
        cmake_cmd.append("-DBUILD_EXAMPLES=ON")
    else:
        cmake_cmd.append("-DBUILD_EXAMPLES=OFF")
        
    if args.tests:
        cmake_cmd.append("-DBUILD_TESTS=ON")
    else:
        cmake_cmd.append("-DBUILD_TESTS=OFF")
    
    # Add source directory
    cmake_cmd.append("..")
    
    # Run CMake configure
    print(f"Configuring project with CMake in {build_type} mode...")
    os.chdir(build_dir)
    try:
        subprocess.run(cmake_cmd, check=True)
    except subprocess.CalledProcessError as e:
        print(f"Error configuring project: {e}")
        return 1
    
    # Build the project
    print("Building project...")
    build_cmd = ["cmake", "--build", ".", "--config", build_type]
    try:
        subprocess.run(build_cmd, check=True)
    except subprocess.CalledProcessError as e:
        print(f"Error building project: {e}")
        return 1
    
    print(f"Build completed successfully in {build_type} mode!")
    
    # Run the application if requested
    if args.run:
        print("Running application...")
        app_path = build_dir / "bin" / build_type / "GameEngine_App.exe"
        if not app_path.exists():
            app_path = build_dir / "bin" / "GameEngine_App.exe"
        
        if app_path.exists():
            try:
                subprocess.run([str(app_path)], check=True)
            except subprocess.CalledProcessError as e:
                print(f"Error running application: {e}")
                return 1
        else:
            print(f"Cannot find executable at {app_path}")
            return 1
    
    return 0

if __name__ == "__main__":
    sys.exit(main()) 