echo Installing dependencies...

lib_dir="./lib"

if [ ! -d "./lib" ]; then
    mkdir -p "lib"
fi

cd "./lib"

if [ ! -d "./alef-core" ]; then
    git clone https://github.com/wingmann/alef-core.git
else
    echo alef-core was already installed
fi

if [ ! -d "./concepts" ]; then
    git clone https://github.com/wingmann/concepts.git
else
    echo concepts was already installed
fi


if [ ! -d "./cast" ]; then
    git clone https://github.com/wingmann/cast.git
else
    echo cast was already installed
fi