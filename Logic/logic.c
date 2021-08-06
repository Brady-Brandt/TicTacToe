#include "logic.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "../Graphics/gamegraphics.h"
#include <GLFW/glfw3.h>


//get the players and board setup
game new_game(){
  //setup random number generator to determine who is x's/o's
  time_t t;
  srand((unsigned) time(&t));
  int random = rand() % 2;

  //create the two player
  player human = {PLAYER, random};
  player bot = {BOT, abs(random - 1)};

  //determine who gets to go first
  int turn = rand() % 2;
  player first_player = (turn == 0) ? bot : human;

  //create the game board array
  state *board = malloc(9 * sizeof(state));
  for(int i =0; i < 9; i++){
    board[i] = EMPTY;
  }


  game current_game = {human, bot, first_player, board, -1, false};
  return current_game;
}

void update_board(game *current_game, int index){
  //set the board position to the current player
  current_game->board[index] = current_game->currentPlayer.symbol;
  current_game->lastMove = index;

  //switch the players turns
  current_game->currentPlayer = (current_game->currentPlayer.symbol == current_game->bot.symbol) ? current_game->human : current_game->bot;
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


int mini_max(game current_game, int depth, int index, bool isMaximizer){
  state result = check_board(current_game.board, index);
  if(result != EMPTY){

    //draw returns 0
    if(result == DRAW) return 0;
    //win returns 1
    else if(result == current_game.bot.symbol) return 1;
    //lose returns -1
    return -1;
  }



  if(isMaximizer){
    int best_score = -10;
    for(int i =0; i < 9; i++){
      if(current_game.board[i] == EMPTY){
        current_game.board[i] = current_game.bot.symbol;
        int score = mini_max(current_game, depth + 1, i, false);
        current_game.board[i] = EMPTY;

        //max func
        best_score = (score > best_score) ? score: best_score;
      }
    }
    return best_score;
  }

  else{
    int best_score = 10;
    for(int i =0; i < 9; i++){
      if(current_game.board[i] == EMPTY){
        current_game.board[i] = current_game.human.symbol;
        int score = mini_max(current_game, depth + 1, i, true);
        current_game.board[i] = EMPTY;

        //min func
        best_score = (score < best_score) ? score: best_score;
      }
    }
    return best_score;
  }

}

//returns true if board is empty
bool is_empty(state *board){
  for(int i =0; i < 9; i++){
    if(board[i] != EMPTY){
      return false;
    }
  }

  return true;
}


int bot_move(game *current_game){

  //if the board is empty return a random number
  if(is_empty(current_game->board)){
    time_t t;
    srand((unsigned) time(&t));
    int move = rand() % 8;
    return move;
  }

  int move;
  int best_score = -10;
  for(int i =0; i < 9; i++){
    if(current_game->board[i] == EMPTY){
      current_game->board[i] = current_game->bot.symbol;
      int score = mini_max(*current_game, 0, i, false);

      current_game->board[i] = EMPTY;

      if(score > best_score){
        best_score = score;
        move = i;
      }

    }
  }
  return move;
}

bool is_bot_turn(game current_game){
  return current_game.currentPlayer.symbol == current_game.bot.symbol;
}

int get_player_value(game current_game){
  return current_game.currentPlayer.symbol;
}


void bot_turn(game *current_game, GLFWwindow *window, drawer *draw_tool){
  //disable the player cursor
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

  //bot determines it's move
  int move = bot_move(current_game);

  //set the corresponding texture
  draw_tool->gridColors[move] = get_player_value(*current_game);
  //update logic board
  update_board(current_game, move);
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void play_game(game *current_game, GLFWwindow *window, drawer *draw_tool){
  state result = check_board(current_game->board, current_game->lastMove);
  if(result == EMPTY){
    if(is_bot_turn(*current_game)){
      bot_turn(current_game, window, draw_tool);
    }
  }


  else{
    current_game->isGameOver = true;
    //two means draw
    int win = 2;

    if(result == current_game->human.symbol){
      win = 0;
    }
    else if(result == current_game->bot.symbol){
      win = 1;
    }

    display_winner(*draw_tool, win);
    display_end_buttons(*draw_tool);
  }
}
