#include "context.h"
#include "game.h"
#include "render.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <glad/gl.h>
#include <GLFW/glfw3.h>


void init_context(Context *ctx){
    int width = 800;
    int height = 800;

    glfwInit();
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    printf("Hello World");
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


    ctx->window = window;
    ctx->isTitleScreen = true;
    GLFWcursor *hand = glfwCreateStandardCursor(GLFW_HAND_CURSOR);
    GLFWcursor *arrow = glfwCreateStandardCursor(GLFW_ARROW_CURSOR);
    ctx->cursors[0] = arrow;
    ctx->cursors[1] = hand;
    ctx->current_cursor = ARROW;
    EventHandler event;
    event.button = -1;
    event.mouseposx = width / 2.0;
    event.mouseposy = height / 2.0;
    ctx->event = event;
    ctx->shader = render_init();
    Game game;
    new_game(&game);
    ctx->game = game;
    glfwSetWindowUserPointer(window, ctx);
}


void mouse_button_callback(struct GLFWwindow *window, int button, int action, int mods){
    Context *ctx = glfwGetWindowUserPointer(window);
    if(action == GLFW_PRESS){
        ctx->event.button = button;
    }
    else if(action == GLFW_RELEASE){
        ctx->event.button = -1;
    }
}

void mouse_pos_callback(struct GLFWwindow *window, double mouseposx, double mouseposy){
    Context *ctx = glfwGetWindowUserPointer(window);
    ctx->event.mouseposx = mouseposx;
    ctx->event.mouseposy = mouseposy;
}

void run_game(Context *ctx){
    draw_game(ctx->shader, ctx->game.board);
    Symbol result = check_board(ctx->game.board, ctx->game.lastMove);
    if(result == SYMBOL_EMPTY){
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
        display_end_buttons(ctx->shader);
    }
}


