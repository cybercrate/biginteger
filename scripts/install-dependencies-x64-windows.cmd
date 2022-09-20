@echo off
echo Installing dependencies...

cd "%HOMEPATH%\vcpkg"

vcpkg.exe install gtest:x64-windows
