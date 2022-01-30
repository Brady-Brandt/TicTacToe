#include <shader.h>
#include <stdio.h>
#include <glad/glad.h>
#include <glmath.h>
#include <string.h>


shader create_shader(const char* vertex_path, const char* fragment_path){
  FILE *vertex_file = fopen(vertex_path, "r");
  FILE *frag_file = fopen(fragment_path, "r");

  if(vertex_file == NULL){
    perror("Failed to open vertex file path: ");
  }
  if(frag_file == NULL){
    perror("Failed to open fragment file path: ");
  }

  //get the size of both files
  fseek(vertex_file, 0, SEEK_END);
  int  vertex_size = ftell(vertex_file);
  rewind(vertex_file);

  fseek(frag_file, 0, SEEK_END);
  int frag_size = ftell(frag_file);
  rewind(frag_file);

  //strings that hold the code from the files
  char vertexs[vertex_size];
  char frags[frag_size];
  memset(vertexs, 0, vertex_size);
  memset(frags, 0, frag_size);

  const char *vertex = vertexs;
  const char *frag = frags;

  fread(vertexs, sizeof(char),vertex_size - 1, vertex_file);
  fread(frags, sizeof(char),frag_size - 1, frag_file);
  fclose(vertex_file);
  fclose(frag_file);


  //compile the shaders
  GLuint vertex_shader, frag_shader;

  int vsuccess;
  char vlog[512];


  //compile vertex shader and check for errors
  vertex_shader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex_shader, 1, &vertex, NULL);
  glCompileShader(vertex_shader);
  glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &vsuccess);


  if(!vsuccess){
    glGetShaderInfoLog(vertex_shader, 512, NULL, vlog);
    printf(" %s: %s \n", vertex_path, vlog);
  }

  int fsuccess;
  char flog[512];

  //compile fragment shader and check for errors
  frag_shader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(frag_shader, 1, &frag, NULL);
  glCompileShader(frag_shader);
  glGetShaderiv(frag_shader, GL_COMPILE_STATUS, &fsuccess);

  if(!fsuccess){
    glGetShaderInfoLog(frag_shader, 512, NULL, flog);
    printf("%s: %s \n", fragment_path, flog);
  }

  //link the shaders together
  GLuint id = glCreateProgram();
  glAttachShader(id, vertex_shader);
  glAttachShader(id, frag_shader);
  glLinkProgram(id);

  //check for linking erros
  glGetProgramiv(id, GL_LINK_STATUS, &fsuccess);
  if(!fsuccess){
    glGetProgramInfoLog(id, 512, NULL, flog);
    printf("Linking Error: %s \n", flog);
  }

  //delete the shaders
  glDeleteShader(vertex_shader);
  glDeleteShader(frag_shader);

  shader result = {id};
  return result;

}

void use_shader(shader shad){
  glUseProgram(shad.ID);
}


void set_int(const char* name, int value, shader shad){
  glUniform1i(glGetUniformLocation(shad.ID, name), value);
}

void set_float(const char* name, float value, shader shad){
  glUniform1f(glGetUniformLocation(shad.ID, name), value);
}

void set_mat4(const char* name, mat4 mat, shader shad){
  glUniformMatrix4fv(glGetUniformLocation(shad.ID, name), 1, GL_FALSE, mat.matrix);
}

void set_vec2(const char * name, vec2 vect, shader shad){
  glUniform2f(glGetUniformLocation(shad.ID, name),vect.x, vect.y);

}

void set_vec3(const char* name, vec3 vect, shader shad){
  glUniform3f(glGetUniformLocation(shad.ID, name),vect.x, vect.y, vect.z);
}

void set_vec4(const char* name, vec4 vect, shader shad){
  glUniform4f(glGetUniformLocation(shad.ID, name),vect.x, vect.y, vect.z, vect.w);
}

void set_int_array(const char* name, int count, int *values, shader shad){
  glUniform1iv(glGetUniformLocation(shad.ID, name), count, values);
}

void set_float_array(const char* name, int count, float *values, shader shad){
  glUniform1fv(glGetUniformLocation(shad.ID, name), count, values);
}

void set_vec2_array(const char* name, int count, vec2 *values, shader shad){
  glUniform2fv(glGetUniformLocation(shad.ID, name), count, values);
}

void set_vec3_array(const char* name, int count, vec3 *values, shader shad){
  glUniform3fv(glGetUniformLocation(shad.ID, name), count, values);
}

void set_vec4_array(const char* name, int count, vec4 *values, shader shad){
  glUniform4fv(glGetUniformLocation(shad.ID, name), count, values);
}
