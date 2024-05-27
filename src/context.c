#include "context.h"
#include "game.h"
#include "render.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <glad/gl.h>
#include <GLFW/glfw3.h>


static const int width = 800;
static const int height = 800;



//we get the color under the cursor
//if the color is not blue we return -1
//if the color is blue, we convert it to its coresponding index on the tictactoe board 
static int read_pixels(double xpos, double ypos){
    uint8_t data[4] = {0};
    glReadPixels(xpos, height - ypos, 1,1,GL_RGBA, GL_UNSIGNED_BYTE, data);
    if(data[0] != 0 || data[1] != 0) return -1;
    uint8_t blue = data[2];
    if(blue < 100 || blue > 108) return -1;

    return blue - 100;
}




static void mouse_button_callback(GLFWwindow *window, int button, int action, int mods){
    Context *ctx = glfwGetWindowUserPointer(window);
    if(action == GLFW_PRESS && button == GLFW_MOUSE_BUTTON_LEFT && ctx->game.isPlayerTurn && !ctx->game.isGameOver){
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        int index = read_pixels(xpos, ypos);
        if(index != -1 && ctx->game.board[index] == SYMBOL_EMPTY){
            update_board(&ctx->game, index);
            glfwSetCursor(ctx->window, ctx->arrow);
        }
    } 
}



static void mouse_pos_callback(GLFWwindow *window, double mouseposx, double mouseposy){
    Context *ctx = glfwGetWindowUserPointer(window);
    int index = read_pixels(mouseposx, mouseposy);
    if(ctx->game.isPlayerTurn && index != -1 && !ctx->game.isGameOver){
        if(SYMBOL_EMPTY == ctx->game.board[index]){
            glfwSetCursor(ctx->window, ctx->hand);
        } else {
            glfwSetCursor(ctx->window, ctx->arrow);
        }     
    } else {
        glfwSetCursor(ctx->window, ctx->arrow);
    }  
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
    Context* ctx = glfwGetWindowUserPointer(window);
    if(action == GLFW_PRESS && key == GLFW_KEY_ESCAPE){
        glfwSetWindowShouldClose(window, true);
    }

    //reset game on spacebar press
    if(ctx->game.isGameOver && action == GLFW_PRESS && key == GLFW_KEY_SPACE){
        new_game(&ctx->game);
    }
}


void init_context(Context *ctx){
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(width, height, "Tic Tac Toe", NULL, NULL);
    if(window == NULL){
        printf("Failed to create window \n");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    //initialize glad
    if(!gladLoadGL(glfwGetProcAddress)){
        printf("Failed to init GLAD \n");
        exit(EXIT_FAILURE);
    }


    glfwSetCursorPos(window, height / 2.0, width / 2.0);
    glfwSetCursorPosCallback(window, mouse_pos_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetKeyCallback(window, key_callback);


    ctx->window = window;
    GLFWcursor *hand = glfwCreateStandardCursor(GLFW_HAND_CURSOR);
    GLFWcursor *arrow = glfwCreateStandardCursor(GLFW_ARROW_CURSOR);
    ctx->arrow = arrow;
    ctx->hand = hand;
    ctx->shader = render_init();
    new_game(&ctx->game);
    glfwSetWindowUserPointer(window, ctx);
}



void run_game(Context *ctx){
    draw_game(ctx->shader, ctx->game.board);
    Symbol result = check_board(ctx->game.board, ctx->game.lastMove);
 
    if(result == SYMBOL_EMPTY && !ctx->game.isGameOver){
        if(!ctx->game.isPlayerTurn){
            //disable the player cursor 
            glfwSetInputMode(ctx->window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
            int move = bot_move(&ctx->game);
            update_board(&ctx->game, move);
            glfwSetInputMode(ctx->window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

        }
    }

    else{
        ctx->game.isGameOver = true;
        //default is draw
        int winner = 2;
        //player has won
        if(result == ctx->game.playerSymbol) winner = 0;
        //bot has won
        if(result == ctx->game.botSymbol) winner = 1;
        display_winner(ctx->shader, winner);
    }

}


