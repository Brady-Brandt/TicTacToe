#pragma once
#include <stdbool.h>
#include <stdint.h>
#include "game.h"
struct GLFWwindow;
struct GLFWcursor;

//cursor types
typedef enum {
  ARROW = 0,
  HAND = 1,
} Cursor;


typedef struct{
  int button;
  double mouseposx;
  double mouseposy;
} EventHandler;


typedef struct {
    struct GLFWwindow *window;
    EventHandler event;
    bool isTitleScreen;
    struct GLFWcursor *cursors[2];
    Cursor current_cursor;
    Game game;
    uint32_t shader;
} Context; 


void init_context(Context *ctx);

void mouse_button_callback(struct GLFWwindow *window, int button, int action, int mods);

void mouse_pos_callback(struct GLFWwindow *window, double mouseposx, double mouseposy);

void run_game(Context *ctx);

