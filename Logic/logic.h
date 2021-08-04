#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H
#include <stdbool.h>

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
  player playerTurn;
  state *board;
} game;


//get the players and board setup
game new_game();

void update_board(game *gam, int index);

state check_board(state *board, int index);

int mini_max(game board, int depth, int index,  bool isMaximizer);

int bot_move(game *gam);

bool is_bot_turn(game gam);

int get_player_value(game gam);












#endif
