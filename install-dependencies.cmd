@echo off
echo Installing dependencies...

if not exist ".\lib" (
    mkdir "lib"
)

cd ".\lib"

if not exist ".\alef-core" (
    git clone https://github.com/wingmann/alef-core.git
) else (
    echo alef was already installed
)

if exist "%HOMEPATH%\vcpkg" (
    cd "%HOMEPATH%\vcpkg"
    vcpkg.exe install gtest:x64-windows
) else (
    echo Error: vcpkg not installed
)
