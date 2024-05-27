#include "game.h"
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>


//get the players and board setup
void new_game(Game *game){
    //setup random number generator to determine who is x's/o's
    srand(time(NULL));
    int random = rand() % 2;
    if(random == 0){
        game->playerSymbol = SYMBOL_X;
        game->botSymbol = SYMBOL_O;
    } else {
        game->playerSymbol = SYMBOL_O;
        game->botSymbol = SYMBOL_X;
    }
    //determine who gets to go first
    game->isPlayerTurn = rand() % 2;
    for(int i =0; i < 9; i++){
        game->board[i] = SYMBOL_EMPTY;
    }
    game->isGameOver = false;
    //used for min max algo
    game->lastMove = -1;
}

void update_board(Game *game, int index){
    //track each move for min max
    game->lastMove = index;
    if(game->isPlayerTurn){
        game->board[index] = game->playerSymbol;
        game->isPlayerTurn = false;
    }
    else{
        game->board[index] = game->botSymbol;
        game->isPlayerTurn = true;
    }
}

//returns 
//X if X wins
//O if O wins
//Empty if the game isn't over
//draw if there is a draw
Symbol check_board(Symbol *board, int index){
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
    if(board[i] == SYMBOL_EMPTY) return SYMBOL_EMPTY;
  }

  return SYMBOL_DRAW;
}


int mini_max(Game game, int depth, int index, bool isMaximizer){
  Symbol result = check_board(game.board, index);
  if(result != SYMBOL_EMPTY){

    //draw returns 0
    if(result == SYMBOL_DRAW) return 0;
    //win returns 1
    else if(result == game.botSymbol) return 1;
    //lose returns -1
    return -1;
  }

  if(isMaximizer){
    int best_score = -10;
    for(int i =0; i < 9; i++){
      if(game.board[i] == SYMBOL_EMPTY){
        game.board[i] = game.botSymbol;
        int score = mini_max(game, depth + 1, i, false);
        game.board[i] = SYMBOL_EMPTY;

        //max func
        best_score = (score > best_score) ? score: best_score;
      }
    }
    return best_score;
  }

  else{
    int best_score = 10;
    for(int i =0; i < 9; i++){
      if(game.board[i] == SYMBOL_EMPTY){
        game.board[i] = game.playerSymbol;
        int score = mini_max(game, depth + 1, i, true);
        game.board[i] = SYMBOL_EMPTY;
        //min func
        best_score = (score < best_score) ? score: best_score;
      }
    }
    return best_score;
  }
}

//returns true if board is empty
bool is_empty(Symbol *board){
  for(int i =0; i < 9; i++){
    if(board[i] != SYMBOL_EMPTY){
      return false;
    }
  }

  return true;
}


int bot_move(Game *game){
  //if the board is empty return a random number
  if(is_empty(game->board)){
    return rand() % 8;
  }

  int move;
  int best_score = -10;
  for(int i =0; i < 9; i++){
    if(game->board[i] == SYMBOL_EMPTY){
      game->board[i] = game->botSymbol;
      int score = mini_max(*game, 0, i, false);
      game->board[i] = SYMBOL_EMPTY;
      if(score > best_score){
        best_score = score;
        move = i;
      }

    }
  }
  return move;
}



