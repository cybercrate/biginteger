@echo off
echo Installing dependencies...

if not exist ".\lib" (
    mkdir "lib"
)

cd ".\lib"

if not exist ".\alef-core" (
    git clone https://github.com/wingmann/alef-core.git
) else (
    echo alef-core was already installed
)

if not exist ".\concepts" (
    git clone https://github.com/wingmann/concepts.git
) else (
    echo concepts was already installed
)

if not exist ".\cast" (
    git clone https://github.com/wingmann/cast.git
) else (
    echo cast was already installed
)

if exist "%HOMEPATH%\vcpkg" (
    cd "%HOMEPATH%\vcpkg"
    vcpkg.exe install gtest:x64-windows
) else (
    echo Error: vcpkg not installed
)
