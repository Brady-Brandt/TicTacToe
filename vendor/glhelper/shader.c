#include "shader.h"
#include <stdio.h>
#include <glad/gl.h>
#include "glmath.h"
#include <stdlib.h>
#include <stdint.h>
#include <string.h>


uint32_t create_shader_from_file(const char* vertex_path, const char* fragment_path){
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
    int  vertex_size = ftell(vertex_file) + 1;
    rewind(vertex_file);

    fseek(frag_file, 0, SEEK_END);
    int frag_size = ftell(frag_file) + 1;
    rewind(frag_file);

    //strings that hold the code from the files
    char *const vertex = calloc(vertex_size / sizeof(char), sizeof(char));
    char *const frags = calloc(frag_size / sizeof(char), sizeof(char));


    fread(vertex, sizeof(char),vertex_size - 1, vertex_file);
    fread(frags, sizeof(char),frag_size - 1, frag_file);
    fclose(vertex_file);
    fclose(frag_file);

    uint32_t id = create_shader_from_string(vertex, frags);
    free(vertex);
    free(frags);
    return id;
}



uint32_t create_shader_from_string(const char* vertex, const char* fragment){
    //compile the shaderers
    uint32_t vertex_shader, frag_shader;

    int vsuccess;
    char vlog[512];

    //compile vertex shader and check for errors
    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex, NULL);
    glCompileShader(vertex_shader);
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &vsuccess);


    if(!vsuccess){
        glGetShaderInfoLog(vertex_shader, 512, NULL, vlog);
        fprintf(stderr, "%s: %s \n", "Failed to compile vertex shader", vlog);
    }

    int fsuccess;
    char flog[512];

    //compile fragment uint32_t and check for errors
    frag_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(frag_shader, 1, &fragment, NULL);
    glCompileShader(frag_shader);
    glGetShaderiv(frag_shader, GL_COMPILE_STATUS, &fsuccess);

    if(!fsuccess){
        glGetShaderInfoLog(frag_shader, 512, NULL, flog);
        fprintf(stderr, "%s: %s \n", "Failed to compile fragment shader", flog);
    }

    //link the shaderers together
    GLuint id = glCreateProgram();
    glAttachShader(id, vertex_shader);
    glAttachShader(id, frag_shader);
    glLinkProgram(id);

    //check for linking erros
    glGetProgramiv(id, GL_LINK_STATUS, &fsuccess);
    if(!fsuccess){
        glGetProgramInfoLog(id, 512, NULL, flog);
        fprintf(stderr,"Linking Error: %s \n", flog);
    }

    //delete the shaderers
    glDeleteShader(vertex_shader);
    glDeleteShader(frag_shader);

    return id;
}

void use_shader(uint32_t shader){
  glUseProgram(shader);
}


void set_int(const char* name, int value, uint32_t shader){
  glUniform1i(glGetUniformLocation(shader, name), value);
}

void set_float(const char* name, float value, uint32_t shader){
  glUniform1f(glGetUniformLocation(shader, name), value);
}

void set_mat4(const char* name, mat4 mat, uint32_t shader){
  glUniformMatrix4fv(glGetUniformLocation(shader, name), 1, GL_FALSE, mat.matrix);
}

void set_vec2(const char * name, vec2 vect, uint32_t shader){
  glUniform2f(glGetUniformLocation(shader, name),vect.x, vect.y);

}

void set_vec3(const char* name, vec3 vect, uint32_t shader){
  glUniform3f(glGetUniformLocation(shader, name),vect.x, vect.y, vect.z);
}

void set_vec4(const char* name, vec4 vect, uint32_t shader){
  glUniform4f(glGetUniformLocation(shader, name),vect.x, vect.y, vect.z, vect.w);
}

void set_int_array(const char* name, int count, int *values, uint32_t shader){
  glUniform1iv(glGetUniformLocation(shader, name), count, values);
}

void set_float_array(const char* name, int count, float *values, uint32_t shader){
  glUniform1fv(glGetUniformLocation(shader, name), count, values);
}


