# Build Scripts for GameEngine

This repository includes several build scripts to help you build the GameEngine project on different platforms.

## Available Scripts

- `build.bat` - Windows batch script
- `build.py` - Python build script (works on Windows, macOS, and Linux)
- `build.sh` - Shell script for macOS and Linux

## Usage

### Windows Batch Script

```bash
# Basic usage (Debug build)
build.bat

# Clean and build in Release mode
build.bat --clean --release

# Build with examples and run the application
build.bat --examples --run

# Build with tests
build.bat --tests

# Full options
build.bat --clean --release --examples --tests --run
```

### Python Script

```bash
# Basic usage (Debug build)
python build.py

# Clean and build in Release mode
python build.py --clean --release

# Build with examples and run the application
python build.py --examples --run

# Build with tests
python build.py --tests

# Full options
python build.py --clean --release --examples --tests --run
```

### Shell Script (macOS/Linux)

```bash
# Make the script executable
chmod +x build.sh

# Basic usage (Debug build)
./build.sh

# Clean and build in Release mode
./build.sh --clean --release

# Build with examples and run the application
./build.sh --examples --run

# Build with tests
./build.sh --tests

# Full options
./build.sh --clean --release --examples --tests --run
```

## Options

All scripts support the following command-line options:

- `--clean` - Clean the build directory before building
- `--release` - Build in Release mode (default is Debug)
- `--examples` - Build example applications
- `--tests` - Build test applications
- `--run` - Run the application after building

## Requirements

- CMake 3.14 or higher
- C++ compiler with C++17 support
- Python 3.x (for the Python script)

## Build Output

The build output will be placed in the `build` directory:

- Executables: `build/bin/Debug/` or `build/bin/Release/`
- Libraries: `build/lib/Debug/` or `build/lib/Release/` 