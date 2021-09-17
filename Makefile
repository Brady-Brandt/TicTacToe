LIBS = res/dep/glfw/3.3.4/lib/libglfw.3.3.dylib res/dep/glHelper/glmath.a res/dep/glad/glad.o
INCLUDE = -I res/dep/glfw/3.3.4/include -I res/glad/include -I res/dep/GLHelper res/dep/
OBJS = objs/event.o objs/gamegraphics.o objs/logic.o objs/game.o
BIN = main

all: $(BIN)

$(BIN): $(OBJS)
	gcc $(LIBS) $(INCLUDE) main.c -o $(BIN)


objs/%.o: src/%.c
	gcc -c $(INCLUDE) $< -o $@ 
