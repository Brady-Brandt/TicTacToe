#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <glhf.h>

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

  float button_vertices[] = {
    -0.5f, 0.5f, 0.0f,
    -0.5, -0.5f, 0.0f,
    0.5f, 0.5f, 0.0f,
    0.5f, -0.5f, 0.0f
  };

  unsigned int button_indices[] = {
    0,1,2, //first triangle
    2,1,3 //second triangle
  };

  unsigned int VAO, EBO, VBO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &EBO);
  glGenBuffers(1, &VBO);

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(button_vertices), button_vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(button_indices), button_indices, GL_STATIC_DRAW);


  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  vec3 LIGHT_BLUE = rgb((vec3){173, 216, 230});
  while(!glfwWindowShouldClose(window)){
    glClearColor(GREEN.x, GREEN.y, GREEN.z, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    use_shader(shad);
    set_vec3("button_color", LIGHT_BLUE, shad);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  glfwTerminate();
  return 0;

}
