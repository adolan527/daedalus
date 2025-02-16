@echo off


:: Run CMake and build
cmake .. -G "Visual Studio 17 2022"
cmake --build .

:: Wait for exit key
echo.
echo Press any key to exit...
pause >nul