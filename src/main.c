#include <glad/gl.h>
#include "render.h"
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdbool.h>
#include "context.h"


int main(){
        
    Context ctx;
    init_context(&ctx);
    int width, height;
    glfwGetWindowSize(ctx.window, &width, &height);
    glViewport(0,0, width, height);



    //texture for the play button
    unsigned int button_text = load_texture("assets/play.png");
    //texture for the title
    unsigned int title_text = load_texture("assets/title.png");

 
    while(!glfwWindowShouldClose(ctx.window)){
        glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        if(ctx.isTitleScreen){
            draw_main_screen(ctx.shader, button_text, title_text);
        }
        else{
            run_game(&ctx);            
        }
        glfwSwapBuffers(ctx.window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}



