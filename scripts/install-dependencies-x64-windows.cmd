@echo off
echo Installing dependencies...

mkdir ..\lib
cd ..\lib
git clone https://github.com/wingmann/wing-concepts

cd "%HOMEPATH%\vcpkg"

vcpkg.exe install gtest:x64-windows
