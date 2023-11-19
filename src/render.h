#pragma once

#include "game.h"
#include <stdbool.h>
#include <stdint.h>



uint32_t load_texture(const char *path);

//returns the shader id
uint32_t render_init();

void draw_main_screen(uint32_t shader ,unsigned int button, unsigned int title);

void draw_game(uint32_t shader, Symbol board[9]);

void display_winner(uint32_t shader, int winner);

void display_end_buttons(uint32_t shader);
