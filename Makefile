CC = clang
FLAGS = -g 
LIBS =  -lglfw -lm 
MACOS = $(shell pkg-config --cflags glfw3) $(shell pkg-config --libs glfw3) -framework Cocoa -framework OpenGL -framework IOKit
INCLUDE = -Ivendor/glhelper -Ivendor/glad/include/
FILES = src/game.c src/render.c src/context.c
VENDOR= vendor/glad/src/gl.c vendor/glhelper/glmath.c vendor/glhelper/shader.c
BIN = bin/tictactoe 

all: $(BIN)

MACOS:
	$(CC) -O3 $(FLAGS) $(VENDOR) $(LIBS) $(FILES) $(INCLUDE) $(MACOS) src/main.c -o $(BIN)

$(BIN): 
	$(CC) $(FLAGS) $(VENDOR) $(LIBS) $(FILES) $(INCLUDE) src/main.c -o $(BIN)

r: 
	./bin/tictactoe

Release: 
	$(CC) -O3 $(FLAGS) $(INCLUDE) $(LIBS) $(VENDOR) $(FILES) $(INCLUDE) src/main.c -o $(BIN)


