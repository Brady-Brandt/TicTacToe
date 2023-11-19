#pragma once
#include <stdbool.h>


typedef enum {
  SYMBOL_X = 0,
  SYMBOL_O = 1,
  SYMBOL_DRAW = 2,
  SYMBOL_EMPTY = 3,
} Symbol;




typedef struct {
  Symbol playerSymbol;
  Symbol botSymbol;
  bool isPlayerTurn;
  int lastMove;
  bool isGameOver;
  Symbol board[9];
} Game;


//get the players and board setup
void new_game(Game *game);

void update_board(Game *game, int index);

//checks the current Symbol of the board ->
//EMPTY = UNFINISHED GAME, X = The player who is x wins
//O = Player who is O wins, DRAW = draw
Symbol check_board(Symbol *board, int index);

int mini_max(Game board, int depth, int index,  bool isMaximizer);

//returns the bot's move
int bot_move(Game *game);

//returns true if the board is empty
bool is_empty(Symbol *board);


