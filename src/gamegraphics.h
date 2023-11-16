#pragma once

#include <stdint.h>
typedef struct{
  int shader;
  unsigned int vao;
  int gridColors[9];
} drawer;


uint32_t load_texture(const char *path);

drawer set_up_drawer(int shader, unsigned int vao, int arr[]);

void draw_main_screen(drawer draw_tools ,unsigned int button, unsigned int title);

void draw_game(drawer draw_tools);

void display_winner(drawer draw_tools, int winner);

void display_end_buttons(drawer draw_tools);
