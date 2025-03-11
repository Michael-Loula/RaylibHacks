all: game

run: game
	./game

raylib/:
	git clone https://github.com/raysan5/raylib.git
libraylib.a: raylib/
	MACOSX_DEPLOYMENT_TARGET=10.9 make -C raylib/src 
	cp raylib/src/libraylib.a .


game: libraylib.a main.c
	clang main.c -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL libraylib.a -o "game"
