#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

typedef enum {
  PLAYER,
  BOT,
} players;

typedef enum {
  X,
  O,
  EMPTY,
} options;


typedef struct {
  players play;
  options symbol;
} player;


typedef struct {
  player human;
  player bot;
  players playerTurn;
  options *board;
} game;


//get the players and board setup
game new_game();

void update_board(game *gam);












#endif
