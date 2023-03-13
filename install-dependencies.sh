echo Installing dependencies...

lib_dir="./lib"

if [ ! -d "./lib" ]; then
    mkdir -p "lib"
fi

cd "./lib"

if [ ! -d "./alef" ]; then
    git clone https://github.com/wingmann/alef.git
else
    echo alef was already installed
fi
