#pragma once
#include <stdbool.h>
#include <stdint.h>
#include "game.h"
struct GLFWwindow;
struct GLFWcursor;


typedef struct {
    struct GLFWwindow *window;
    struct GLFWcursor *hand;
    struct GLFWcursor *arrow;
    Game game;
    uint32_t shader;
} Context; 


void init_context(Context *ctx);

void run_game(Context *ctx);

