#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdbool.h>
#include "Graphics/gamegraphics.h"
#include "Logic/logic.h"
#include <glhf.h>



void mouse_callback(GLFWwindow *window, double xpos, double ypos);

void button_callback(GLFWwindow *window, int button, int action, int mods);



//checks if value is in arr[]
bool contains(int arr[], int size, int value){
  for(int i =0; i < size; i++){
    if(arr[i] == value){
      return true;
    }
  }
  return false;
}



//window size
const int WIDTH = 1000;
const int HEIGHT = 1000;


bool title_screen = true;


//cursor types
typedef enum {
  HAND,
  ARROW,
} cursor;

GLFWcursor *hand, *arrow;
cursor current_cursor = ARROW;


drawer title_draw;
drawer game_draw;

game my_game;


int main(){

  glfwInit();
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Tic Tac Toe", NULL, NULL);

  if(window == NULL){
    printf("Failed to create window \n");
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);

  //initialize glad
  if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
    printf("Failed to init GLAD \n");
    return -1;
  }
  glViewport(0,0, WIDTH, HEIGHT);

  shader shad = create_shader("shaders/vertex.c", "shaders/fragment.c");
  shader game_shader = create_shader("shaders/gamev.c", "shaders/gamef.c");

  float vertices[] = {
    //play button pos     play button texture
    -0.5f, 0.5f, 0.0f,    0.0f, 1.0f,
    -0.5, -0.5f, 0.0f,    0.0f, 0.0f,
    0.5f, 0.5f, 0.0f,     1.0f, 1.0f,
    0.5f, -0.5f, 0.0f,     1.0f, 0.0f
  };

  unsigned int button_indices[] = {
    //play button
    0,1,2, //first triangle
    2,1,3, //second triangle
  };

  unsigned int VAO, EBO, VBO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &EBO);
  glGenBuffers(1, &VBO);


  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(button_indices), button_indices, GL_STATIC_DRAW);

  //triangle coords
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  //texture coords
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);



  //texture for the play button
  unsigned int button_text = glhf_load_texture("res/images/play.png");
  //texture for the title
  unsigned int title_text = glhf_load_texture("res/images/title.png");


  hand = glfwCreateStandardCursor(GLFW_HAND_CURSOR);
  arrow = glfwCreateStandardCursor(GLFW_ARROW_CURSOR);


  glfwSetCursorPos(window, 500, 500);
  glfwSetCursorPosCallback(window, mouse_callback);
  glfwSetMouseButtonCallback(window, button_callback);

  my_game = new_game();

  int blank[9] = {0};
  title_draw = set_up_drawer(shad, VAO, blank);

  //the colors of each tile on the board how we determine when one of the buttons is pressed
  int gridcolors[] = {100, 101, 102, 103, 104, 105, 106, 107, 108};
  game_draw = set_up_drawer(game_shader, VAO, gridcolors);

  while(!glfwWindowShouldClose(window)){
    glClearColor(GREEN.x, GREEN.y, GREEN.z, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    if(title_screen){
      draw_main_screen(title_draw, button_text, title_text);
    }
    else{
        draw_game(game_draw);
        play_game(&my_game, window, &game_draw);
    }



    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  glfwTerminate();
  return 0;

}


void mouse_callback(GLFWwindow *window, double xpos, double ypos){
    unsigned char pixels[1 * 1 * 4];
    ypos = HEIGHT - ypos;
    glReadPixels(xpos, ypos, 1,1, GL_RGBA, GL_UNSIGNED_BYTE, pixels);


    //set to the hand cursor if we are on the play button
    if(title_screen == true && pixels[1] != 128 && ypos < 500){
      glfwSetCursor(window, hand);
      current_cursor = HAND;
    }

    //check if the cursor is on the board by the color of the pixels
    else if(title_screen == false && contains(game_draw.gridColors, 9, pixels[2]) && my_game.isGameOver == false){
      glfwSetCursor(window, hand);
      current_cursor = HAND;
    }

    else if(my_game.isGameOver == true && pixels[0] == 255 && ypos < 200){
      glfwSetCursor(window, hand);
      current_cursor = HAND;
    }

    else{
      glfwSetCursor(window, arrow);
      current_cursor = ARROW;
    }

}


void button_callback(GLFWwindow *window, int button, int action, int mods){
  if(title_screen == true && current_cursor == HAND && action == GLFW_PRESS && button == GLFW_MOUSE_BUTTON_LEFT){
    title_screen = false;
  }

  else if(current_cursor == HAND && GLFW_PRESS == action && button == GLFW_MOUSE_BUTTON_LEFT && my_game.isGameOver == false){
    //get the current mouse position and read in the colors at that value
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    unsigned char pixels[1 * 1 * 4];
    glReadPixels(xpos, HEIGHT - ypos, 1,1, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

    //the color of the boards pixels ranges from 100-108
    if(pixels[2] < 100 & pixels[2] > 109){
      return;
    }

    //get the index of the array
    int index = pixels[2] % 100;

    //set the index on the board to the right texture
    game_draw.gridColors[index] = get_player_value(my_game) + 1;
    //update the logic board
    update_board(&my_game, index);
    glfwSetCursor(window, arrow);
  }


  else if(my_game.isGameOver == true && GLFW_PRESS == action && button == GLFW_MOUSE_BUTTON_LEFT && current_cursor == HAND){
    //get the current mouse position and read in the colors at that value
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    unsigned char pixels[1 * 1 * 4];
    glReadPixels(xpos, HEIGHT - ypos, 1,1, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

    if(pixels[0] != 255){
      return;
    }

    //if click on quit button
    //free the game memory and close the application
    if(xpos < 420){
      delete_game(my_game);
      glfwSetWindowShouldClose(window, GL_TRUE);
    }

    //if click play again
    //free old memory
    //start a new game
    //set the grid color back to their original values
    else if(xpos > 450){
      delete_game(my_game);
      my_game = new_game();

      for(int i =0; i < 9; i++){
        game_draw.gridColors[i] = 100 + i;
      }

    }


  }


}
