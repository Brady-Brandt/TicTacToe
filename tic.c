#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdbool.h>
#include <glhf.h>




void draw_main_screen(shader shad, unsigned int VAO,unsigned int button, unsigned int title);

void mouse_callback(GLFWwindow *window, double xpos, double ypos);




//window size
const int WIDTH = 1000;
const int HEIGHT = 1000;

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


  //GLFWcursor* hand_cursor = glfwCreateStandardCursor(GLFW_HAND_CURSOR);
  //glfwSetCursor(window, hand_cursor);
  glfwSetCursorPos(window, 500, 500);
  glfwSetCursorPosCallback(window, mouse_callback);



  while(!glfwWindowShouldClose(window)){
    glClearColor(GREEN.x, GREEN.y, GREEN.z, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);


    draw_main_screen(shad, VAO, button_text, title_text);


    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  glfwTerminate();
  return 0;

}


void mouse_callback(GLFWwindow *window, double xpos, double ypos){
  printf("%g, %g \n", xpos, ypos);
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
  set_vec3("color", YELLOW, shad);

  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);


  glBindTexture(GL_TEXTURE_2D, button);

  //translates play button to the bottom and scales it
  mat4 button_model = create_transform_mat4(SCALE, (vec3){0.65f, 0.25f, 0.0f});
  translate_mat4(&button_model, (vec3){0.0f, -0.5f, 0.0f});
  set_mat4("model", button_model, shad);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);


  free_mat4(title_model);
  free_mat4(button_model);
}
