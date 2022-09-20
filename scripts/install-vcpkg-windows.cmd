@echo off
echo Installing vcpkg...

if not exist "%HOMEPATH%\vcpkg" (
    cd "%HOMEPATH%"

    git clone https://github.com/microsoft/vcpkg
    .\vcpkg\bootstrap-vcpkg.bat
) else (
    echo vcpkg was already installed
)
