#pragma once 


#include "glmath.h"
#include <stdint.h>


uint32_t create_shader(const char* vertexPath, const char* fragmentPath);

void use_shader(uint32_t shader);

void set_int(const char* name, int value, uint32_t shader);

void set_float(const char* name, float value, uint32_t shader);

void set_vec2(const char * name, vec2 vect, uint32_t shader);

void set_vec3(const char* name, vec3 vect, uint32_t shader);

void set_vec4(const char* name, vec4 vect, uint32_t shader);

void set_mat4(const char* name, mat4 mat, uint32_t shader);

void set_int_array(const char* name, int count, int *values, uint32_t shader);

void set_float_array(const char* name, int count, float *values, uint32_t shader);


