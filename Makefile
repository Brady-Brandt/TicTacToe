CC = clang
FLAGS = 
LIBS = -lglfw -lm 
INCLUDE = -Ivendor/glhelper -Ivendor/glad/include/
FILES = src/event.c src/gamegraphics.c src/logic.c
VENDOR= vendor/glad/src/gl.c vendor/glhelper/glmath.c vendor/glhelper/shader.c
BIN = bin/tictactoe 

all: $(BIN)

$(BIN): 
	$(CC) $(FLAGS) $(VENDOR) $(LIBS) $(FILES) $(INCLUDE) src/main.c -o $(BIN)

r: 
	./bin/tictactoe

Release: $(OBJS)
	$(CC) -03 $(FLAGS) $(INCLUDE) $(LIBS) $(VENDOR) $(FILES) $(INCLUDE) src/main.c -o $(BIN)


