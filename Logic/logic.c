#include "logic.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

//get the players and board setup
game new_game(){
  //setup random number generator to determine who is x's/o's
  time_t t;
  srand((unsigned) time(&t));
  int random = rand() % 1;

  //create the two player
  player human = {PLAYER, random};
  player bot = {BOT, abs(random - 1)};

  //determine who gets to go first
  int turn = rand() % 1;
  players first_player = turn;

  options *board = malloc(9 * sizeof(char));
  for(int i =0; i < 9; i++){
    board[i] = EMPTY;
  }


  game current_game = {human, bot, first_player, board};
  return current_game;
}

void update_board(game *gam);
