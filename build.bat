@echo off
REM Simple build script for GameEngine project
REM Copyright (c) 2024 Cody Wall

setlocal enabledelayedexpansion

REM Parse command line arguments
set CLEAN=0
set BUILD_TYPE=Debug
set BUILD_EXAMPLES=OFF
set BUILD_TESTS=OFF
set RUN_AFTER_BUILD=0

:parse_args
if "%1"=="" goto :done_parsing
if /i "%1"=="--clean" set CLEAN=1
if /i "%1"=="--release" set BUILD_TYPE=Release
if /i "%1"=="--examples" set BUILD_EXAMPLES=ON
if /i "%1"=="--tests" set BUILD_TESTS=ON
if /i "%1"=="--run" set RUN_AFTER_BUILD=1
shift
goto :parse_args
:done_parsing

REM Create build directory if it doesn't exist
if not exist "build" mkdir "build"

REM Clean build directory if requested
if %CLEAN%==1 (
    echo Cleaning build directory...
    if exist "build" (
        pushd "build"
        for /f "delims=" %%i in ('dir /b') do (
            if exist "%%i\*" (
                rmdir /s /q "%%i"
            ) else (
                del /q "%%i"
            )
        )
        popd
    )
)

REM Configure and build the project
echo Configuring project with CMake in %BUILD_TYPE% mode...
pushd "build"

REM Run CMake configure
cmake -G "Visual Studio 17 2022" -DCMAKE_BUILD_TYPE=%BUILD_TYPE% -DBUILD_EXAMPLES=%BUILD_EXAMPLES% -DBUILD_TESTS=%BUILD_TESTS% ..
if %ERRORLEVEL% neq 0 (
    echo Error configuring project
    popd
    exit /b 1
)

REM Build the project
echo Building project...
cmake --build . --config %BUILD_TYPE%
if %ERRORLEVEL% neq 0 (
    echo Error building project
    popd
    exit /b 1
)

echo Build completed successfully in %BUILD_TYPE% mode!

REM Run the application if requested
if %RUN_AFTER_BUILD%==1 (
    echo Running application...
    set APP_PATH=bin\%BUILD_TYPE%\GameEngine_App.exe
    if not exist "!APP_PATH!" set APP_PATH=bin\GameEngine_App.exe
    
    if exist "!APP_PATH!" (
        "!APP_PATH!"
    ) else (
        echo Cannot find executable at !APP_PATH!
        popd
        exit /b 1
    )
)

popd
exit /b 0 