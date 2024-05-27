#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <stdbool.h>
#include "context.h"

int main(){
        
    Context ctx;
    init_context(&ctx);
    int width, height;
    glfwGetWindowSize(ctx.window, &width, &height);
    glViewport(0,0, width, height);

    
    while(!glfwWindowShouldClose(ctx.window)){
        glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        run_game(&ctx); 
        glfwSwapBuffers(ctx.window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}



