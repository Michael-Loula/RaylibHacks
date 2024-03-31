#!/bin/bash -eux

if [ ! -d raylib/ ]; then
	git clone https://github.com/raysan5/raylib.git
fi
HASH=$(ls -lR raylib/ | shasum)
if [ ! -f build_lock ] || [ "$HASH" != "$(<build_lock)" ]; then
        echo "either lock doesn't or something changed, rebuilding raylib"
	echo "$HASH" > build_lock
	cd raylib/src
	MACOSX_DEPLOYMENT_TARGET=10.9 bash -c 'make'
        cp libraylib.a ../..
	cd ../..
fi
clang main.c -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL libraylib.a -o "game"
