# Setup vcpkg on linux 

## Install vcpkg
```bash
cd ~/
git clone https://github.com/microsoft/vcpkg
./vcpkg/bootstrap-vcpkg.sh
```
#### Before installing the dependencies, you must install pkg-config

## Install dependencies
```bash
cd ~/vcpkg/
./vcpkg install fmt:x64-linux
./vcpkg install gtest:x64-linux
```
