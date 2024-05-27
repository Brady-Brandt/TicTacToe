#pragma once

#include "game.h"
#include <stdint.h>


//returns the shader id
uint32_t render_init();

void draw_main_screen(uint32_t shader ,unsigned int button, unsigned int title);

void draw_game(uint32_t shader, Symbol board[9]);

void display_winner(uint32_t shader, int winner);

