#ifndef GAME_EVENT_H
#define GAME_EVENT_H
#include <GLFW/glfw3.h>

typedef struct{
  int button;
  double mouseposx;
  double mouseposy;
  int key;
} Event_handler;


void init_event_handler();

void mouse_button_callback(GLFWwindow *window, int button, int action, int mods);

void mouse_pos_callback(GLFWwindow *window, double mouseposx, mouseposy);














#endif
