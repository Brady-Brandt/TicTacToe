#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <glhf.h>




void draw_main_screen(shader shad, unsigned int VAO,unsigned int button, unsigned int title);

void draw_game(shader shad, unsigned VAO);

void mouse_callback(GLFWwindow *window, double xpos, double ypos);

void button_callback(GLFWwindow *window, int button, int action, int mods);


//mimics the in keyword in python
bool in(int arr[], int size, int value){
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
bool first_frame = true;
bool title_screen = true;

//cursor types
typedef enum {
  HAND,
  ARROW,
} cursor;

GLFWcursor* hand;
GLFWcursor* arrow;
cursor current_cursor = ARROW;

//the colors of each tile on the board how we determine when one of the buttons is pressed
int gridcolors[] = {100, 101, 102, 103, 104, 105, 106, 107, 108};

int current_click = -1;


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




  glfwSetCursorPos(window, 500, 500);
  glfwSetCursorPosCallback(window, mouse_callback);
  glfwSetMouseButtonCallback(window, button_callback);



  while(!glfwWindowShouldClose(window)){
    glClearColor(GREEN.x, GREEN.y, GREEN.z, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    if(title_screen){
      draw_main_screen(shad, VAO, button_text, title_text);
    }else{
      draw_game(game_shader, VAO);
    }



    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  glfwTerminate();
  return 0;

}


void mouse_callback(GLFWwindow *window, double xpos, double ypos){
  if(first_frame == true){
    hand = glfwCreateStandardCursor(GLFW_HAND_CURSOR);
    arrow = glfwCreateStandardCursor(GLFW_ARROW_CURSOR);
    first_frame = false;

  }

    unsigned char pixels[1 * 1 * 4];
    glReadPixels(xpos, HEIGHT - ypos, 1,1, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
    printf("%i, %i, %i \n", (int)pixels[0], (int)pixels[1], (int)pixels[2]);

    //set to the hand cursor if we are on the play button
    if(title_screen == true && pixels[1] != 128 && ypos > 500){
      glfwSetCursor(window, hand);
      current_cursor = HAND;
    }

    else if(title_screen == false && in(gridcolors, 9, pixels[2])){
      glfwSetCursor(window, hand);
      current_cursor = HAND;

      current_click = gridcolors[pixels[2] % 100];
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

  else if(current_cursor == HAND && GLFW_PRESS == action && button == GLFW_MOUSE_BUTTON_LEFT){
    if(current_click == -1){
      return;
    }
    gridcolors[current_click % 100] = -1;

  }

}



//draws the title_screen
void draw_main_screen(shader shad, unsigned int VAO, unsigned int button, unsigned int title){
  glBindVertexArray(VAO);
  use_shader(shad);


  //enable our title text
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, title);

  //move the title to the top of the screen
  mat4 title_model = create_transform_mat4(SCALE, (vec3){1.5f, 0.25f, 0.0f});
  translate_mat4(&title_model, (vec3){0.0f, 0.75f, 0.0f});
  set_mat4("model", title_model, shad);
  set_vec3("color", PINK, shad);

  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);


  glBindTexture(GL_TEXTURE_2D, button);

  //translates play button to the bottom and scales it
  mat4 button_model = create_transform_mat4(SCALE, (vec3){0.65f, 0.25f, 0.0f});
  translate_mat4(&button_model, (vec3){0.0f, -0.5f, 0.0f});
  set_mat4("model", button_model, shad);


  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);


  free_mat4(title_model);
  free_mat4(button_model);

  glBindTexture(GL_TEXTURE_2D, 0);
}




void draw_game(shader shad, unsigned VAO){

  glBindVertexArray(VAO);
  use_shader(shad);

  mat4 model;
  set_vec3("color", YELLOW, shad);

  float scale_factor = 0.45f;

  //make our tic toc toe board
  vec3 translate[] = {
    //first row
    {-scale_factor, scale_factor, 0.0f},
    {0.0f, scale_factor, 0.0f},
    {scale_factor, scale_factor, 0.0f},

    //second row
    {-scale_factor, 0.0f, 0.0f},
    {0.0f, 0.0f, 0.0f},
    {scale_factor, 0.0f, 0.0f},

    //third row
    {-scale_factor, -scale_factor, 0.0f},
    {0.0f, -scale_factor, 0.0f},
    {scale_factor, -scale_factor, 0.0f}
  };



  for(int i =0; i < 9; i++){
    set_vec3("isTexture", WHITE, shad);
    glBindTexture(GL_TEXTURE_2D, 0);

    model = create_transform_mat4(SCALE, (vec3){scale_factor, scale_factor, 0.0f});
    translate_mat4(&model, translate[i]);


    set_mat4("model", model, shad);
    set_vec3("color", rgb((vec3){0, 0, 100 + i}), shad);

    if(gridcolors[i] == -1){
      //texture for x/o
      unsigned int x_texture = glhf_load_texture("res/images/x.png");
      unsigned int o_texture = glhf_load_texture("res/images/o.png");

      set_vec3("isTexture", BLACK, shad);
      glBindTexture(GL_TEXTURE_2D, x_texture);
    }




    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
    free_mat4(model);
  }

  //create the board grid lines
  set_vec3("color", PURPLE, shad);
  vec3 scale = Vec3(1.0f, 1.35f, 0.0f);
  mat4 id;


  //draws the vertical grid lines on the screen
  for(int i =0; i < 2; i++){
    id = create_transform_mat4(TRANSLATE, (vec3){0.28f + (i * 0.45f ), 0.0f, 0.0f});
    scale_mat4(&id, scale);

    set_mat4("model", id, shad);

    glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, NULL);
    free_mat4(id);
  }


  //draws the horizontal grid lines on the screen
  for(int i =0; i < 2; i++){
    id = create_transform_mat4(SCALE, scale);
    rotate_axis_mat4(&id, 180, (vec3){1.0f, 1.0f, 0.0f});
    translate_mat4(&id, (vec3){0.0, 0.27f + (i * 0.45f), 0.0f});
    set_mat4("model", id, shad);
    glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, NULL);
    free_mat4(id);
  }


}
