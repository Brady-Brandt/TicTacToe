OBJS = objs/glmath.o objs/shader.o
INCLUDE = -I dep/glad/include -I include
GLAD = dep/glad/glad.o
BIN = GLHelper.a

$(BIN): $(OBJS)
	ar rcs $(BIN) $(OBJS) $(GLAD) 

objs/%.o: src/%.c
	gcc -c $(INCLUDE) $^ -o $@
