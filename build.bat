@echo off
if not exist build mkdir build

REM Compile src/main.c and link your local raylib library and Windows system flags
gcc src/main.c -o build/game.exe -Iinclude -Llib -lraylib -lopengl32 -lgdi32 -lwinmm -lucrt

if %errorlevel% equ 0 (
    echo Build successful! Running game...
    start build\game.exe
) else (
    echo Compilation failed!
)
