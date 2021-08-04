#include "logic.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
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
  player first_player = (turn == 0) ? bot : human;

  state *board = malloc(9 * sizeof(char));
  for(int i =0; i < 9; i++){
    board[i] = EMPTY;
  }


  game current_game = {human, bot, first_player, board};
  return current_game;
}

void update_board(game *gam, int index){
  //set the board position to the current player
  gam->board[index] = gam->playerTurn.symbol;

  //switch the players turns
  gam->playerTurn = (gam->playerTurn.symbol == gam->bot.symbol) ? gam->human : gam->bot;
}

state check_board(state *board, int index){
  int col = index % 3;
  int row = (index > 2) + (index > 5);

  //checks the column
  if(board[col] == board[col + 3] && board[col] == board[col + 6]) return board[col];

  //checks rows
  if(board[row * 3] == board[row * 3 + 1] && board[row * 3] == board[row * 3 + 2]) return board[row * 3];

  //check diagonals
  if (board[2] == board[4] && board[2] == board[6]) return board[2];
  if (board[0] == board[4] && board[0] == board[8]) return board[0];

  for(int i =0; i < 9; i++){
    if(board[i] == EMPTY) return EMPTY;
  }

  return DRAW;
}


int mini_max(game gam, int depth, int index, bool isMaximizer){
  state result = check_board(gam.board, index);
  if(result != EMPTY){

    //draw returns 0
    if(result == DRAW) return 0;
    //win returns 1
    else if(result == gam.bot.symbol) return 1;
    //lose returns -1
    return -1;
  }



  if(isMaximizer){
    int best_score = -10;
    for(int i =0; i < 9; i++){
      if(gam.board[i] == EMPTY){
        gam.board[i] = gam.bot.symbol;
        int score = mini_max(gam, depth + 1, i, false);
        gam.board[i] = EMPTY;

        //max func
        best_score = (score > best_score) ? score: best_score;
      }
    }
    return best_score;
  }

  else{
    int best_score = 10;
    for(int i =0; i < 9; i++){
      if(gam.board[i] == EMPTY){
        gam.board[i] = gam.human.symbol;
        int score = mini_max(gam, depth + 1, i, true);
        gam.board[i] = EMPTY;

        //min func
        best_score = (score < best_score) ? score: best_score;
      }
    }
    return best_score;
  }

}


int bot_move(game *gam){
  int move;
  int best_score = -10;
  for(int i =0; i < 9; i++){
    if(gam->board[i] == EMPTY){
      gam->board[i] = gam->bot.symbol;
      int score = mini_max(*gam, 0, i, false);

      gam->board[i] = EMPTY;

      if(score > best_score){
        best_score = score;
        move = i;
      }

    }
  }
  return move;
}

bool is_bot_turn(game gam){
  return gam.playerTurn.symbol == gam.bot.symbol;
}

int get_player_value(game gam){
  return gam.playerTurn.symbol;
}
