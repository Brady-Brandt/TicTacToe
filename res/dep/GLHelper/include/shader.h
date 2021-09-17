#ifndef GLHELPER_SHADER_H
#define GLHELPER_SHADER_H

#include <glad/glad.h>
#include <glmath.h>

typedef struct{
  GLuint ID;
} shader;



shader create_shader(const char* vertexPath, const char* fragmentPath);
void use_shader(shader shad);

void set_int(const char* name, int value, shader shad);

void set_float(const char* name, float value, shader shad);


void set_vec2(const char * name, vec2 vect, shader shad);

void set_vec3(const char* name, vec3 vect, shader shad);

void set_vec4(const char* name, vec4 vect, shader shad);


void set_mat4(const char* name, mat4 mat, shader shad);


void set_int_array(const char* name, int count, int *values, shader shad);

void set_float_array(const char* name, int count, float *values, shader shad);


void set_vec2_array(const char* name, int count, vec2 *values, shader shad);

void set_vec3_array(const char* name, int count, vec3 *values, shader shad);

void set_vec4_array(const char* name, int count, vec4 *values, shader shad);







#endif
