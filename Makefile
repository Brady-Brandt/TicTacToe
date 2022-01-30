CC = clang
FLAGS = -std=c17
LIBS = res/dep/glfw/src/libglfw3.a res/dep/glHelper/glmath.a res/dep/glad/glad.o
INCLUDE = -I res/dep/glfw/include -I res/dep/glad/include -I res/dep/GLHelper/include -I res/dep -I .
OBJS = objs/event.o objs/gamegraphics.o objs/logic.o objs/game.o
BIN = main

all: $(BIN)

$(BIN): $(OBJS)
	$(CC) $(FLAGS) $(LIBS) $(OBJS) $(INCLUDE) main.c -o $(BIN)


Release: GLAD GLFW GLHELPER $(OBJS)
	$(CC) -03 $(FLAGS) $(LIBS) $(OBJS) $(INCLUDE) main.c -o $(BIN)

GLAD:
	cd res/dep/glad; \
	cmake .; \
	make; \

GLFW:
	cd res/dep/glfw;\
	cmake .; \
	make;\

GLHELPER:
	cd res/dep/GLHelper; \
	make; \

objs/%.o: src/%.c | objs
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
