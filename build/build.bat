@echo off

:: Check if argument is provided
if "%1"=="" (
    echo Usage: build.bat [make|ninja|vs]
    exit /b 1
)

:: Select generator
if "%1"=="make" (
    set GENERATOR="MinGW Makefiles"
) else if "%1"=="ninja" (
    set GENERATOR="Ninja"
) else if "%1"=="vs" (
    set GENERATOR="Visual Studio 17 2022"
) else (
    echo Invalid system. Use 'make', 'ninja', or 'vs'.
    exit /b 1
)


:: Run CMake and build
cmake .. -G %GENERATOR%
cmake --build .

:: Return to project root
cd ..
