#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H
#include <stdbool.h>
#include "gamegraphics.h"
#include <GLFW/glfw3.h>


typedef enum {
  PLAYER,
  BOT,
} players;

typedef enum {
  X,
  O,
  DRAW,
  EMPTY,
} state;


typedef struct {
  players play;
  state symbol;
} player;


typedef struct {
  player human;
  player bot;
  player currentPlayer;
  state *board;
  int lastMove;
  bool isGameOver;
} game;


//get the players and board setup
game new_game();

void delete_game(game current_game);

void update_board(game *current_game, int index);

//checks the current state of the board ->
//EMPTY = UNFINISHED GAME, X = The player who is x wins
//O = Player who is O wins, DRAW = draw
state check_board(state *board, int index);

int mini_max(game board, int depth, int index,  bool isMaximizer);

//returns the bot's move
int bot_move(game *current_game);

//returns true if the board is empty
bool is_empty(state *board);

//returns true if it is the bot's turn
bool is_bot_turn(game current_game);

//get's the current player's enum value
int get_player_value(game current_game);

void bot_turn(game *current_game, GLFWwindow *window, drawer *draw_tool);

void play_game(game *current_game, GLFWwindow *window, drawer *draw_tool);












#endif
