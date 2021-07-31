LIBS = /usr/local/Cellar/glfw/3.3.4/lib/libglfw.3.3.dylib res/glmath.a
IN = -I/usr/local/Cellar/glad/include -I/Users/bradybrandt/Documents/GLHelperFunctions
GLAD = /usr/local/Cellar/glad/src/glad.c
INPUT = tic.c

all:
	gcc -Wall $(LIBS) $(IN) $(GLAD) $(INPUT) -o main
