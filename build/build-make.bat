@echo off


:: Run CMake and build
cmake .. -G "MinGW Makefiles"
cmake --build .

:: Wait for exit key
echo.
echo Press any key to exit...
pause >nul
