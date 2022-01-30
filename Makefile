LIBS = res/dep/glfw/src/libglfw3.a res/dep/glHelper/glmath.a res/dep/glad/glad.o
INCLUDE = -I res/dep/glfw/3.3.4/include -I res/glad/include -I res/dep/GLHelper 
OBJS = objs/event.o objs/gamegraphics.o objs/logic.o objs/game.o
BIN = main

all: $(BIN)

$(BIN): $(OBJS)
	gcc $(LIBS) $(INCLUDE) main.c -o $(BIN)


GLAD:
	cd res/dep/glad; \
	CMake .; \
	make .;

GLFW:
	cd res/dep/glfw;\
	cmake .; \
	make;\

STB:
	cd res/dep/stb; \
	ls | grep -v stb_image.h | xargs rm; \

GLHELPER:
	cd res/dep/GLHelper; \
	make; \
