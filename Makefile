all: game

run: game
	./game

raylib/:
	git clone https://github.com/raysan5/raylib.git
libraylib.a: raylib/
	MACOSX_DEPLOYMENT_TARGET=10.9 make -C raylib/src 
	cp raylib/src/libraylib.a .
libcjson.a:
	git clone https://github.com/DaveGamble/cJSON.git
	mkdir -p cJSON/build
	cd build
	cmake -B=cJSON/build -S=cJSON -DBUILD_SHARED_LIBS=Off
	make -C cJSON/build
	cp cJSON/build/libcjson.a .

game: libcjson.a libraylib.a main.c
	clang main.c -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL libcjson.a libraylib.a -o "game"

clean:
	rm -rf *.a game cJSON raylib
