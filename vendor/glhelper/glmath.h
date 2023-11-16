#ifndef GLHELPER_GLMATH_H
#define GLHELPER_GLMATH_H

extern const float GLH_PI;
extern const float GLH_DEG;
extern const float GLH_RAD;

typedef struct {
  float x;
  float y;
} vec2;


//3d vector
typedef struct{
  float x;
  float y;
  float z;
} vec3;


//4d vector
typedef struct{
  float x;
  float y;
  float z;
  float w;
} vec4;

//4 * 4 matrix used for identity matrices and transformations
typedef struct {
  float *matrix;
} mat4;


typedef enum {
  GLH_TRANSLATE,
  GLH_ROTATE,
  GLH_SCALE
} Transform;

typedef enum{
  GLH_X_AXIS,
  GLH_Y_AXIS,
  GLH_Z_AXIS
} Axis;


//creates a 2d vector
vec2 Vec2(float x, float y);

//prints out a 2d vector in component form
void print_vec2(vec2 vect);

//normalizes a 2d vector
vec2 normalize_vec2(vec2 vect);

vec2 add_vec2(vec2 v1, vec2 v2);

vec2 sub_vec2(vec2 v1, vec2 v2);

vec2 mult_vec2(vec2 v1, vec2 v2);

vec2 div_vec2(vec2 v1, vec2 v2);

float dot_vec2(vec2 v1, vec2 v2);

vec2 scalar_mult_vec2(vec2 v1, float value);




//creates a vector
vec3 Vec3(float x,float y,float z);

//prints out a 3d vector in component form
void print_vec3(vec3 v);

//normalizes a 3d vector
vec3 normalize_vec3(vec3 v);

//adds two 3d vectors together
vec3 add_vec3(vec3 v1, vec3 v2);

//subtracts 3d vect2 from 3d vect1
vec3 sub_vec3(vec3 v1, vec3 v2);

//multiplies two vectors together
vec3 mult_vec3(vec3 v1, vec3 v2);

//performs scalar multiplication on a 3d vector
vec3 scalar_mult_vec3(vec3 v, double scalar);

//calculates the dot product of 2 3d vectors
double dot_vec3(vec3 v, vec3 v2);

//calculates the cross product between 2 3d vectors
vec3 cross_product(vec3 v1, vec3 v2);


//creates a 4d vector from the component
vec4 Vec4(float x, float y, float z, float w);

//prints a 4d vector
void print_vec4(vec4 v);

vec4 add_vec4(vec4 v1, vec4 v2);

vec4 sub_vec4(vec4 v1, vec4 v2);

vec4 mult_vec4(vec4 v1, vec4 v2);

vec4 scalar_mult_vec4(vec4 v, double scalar);

double dot_vec4(vec4 v, vec4 v2);

vec4 normalize_vec4(vec4 v);

//creates a 4 * 4 matrix out of the given array in COLUMN-ORDER NOTATION
mat4 create_mat4(float arr[]);

//prints out a 4 * 4 matrix
void print_mat4(mat4 mat);

//returns an identity matrix with the corresponding value
mat4 identity_mat4(float value);

//frees the memory
void free_mat4(mat4 mat);

//multiply 4 * 4 matrices
mat4 multiply_mat4(mat4 m1, mat4 m2);

void test_mat4(mat4 mat);

//scalar dilation matrix
void scalec_mat4(mat4 *mat, float scale);

//creates a rotation matrix
mat4 rotation_mat4(Axis axis, float angle);

//rototes the matrix
void rotate_mat4(mat4 *mat, Axis axis, float angle);

//creates an orthographic projection matrix
mat4 ortho(float l, float r, float b, float t, float n, float f);

//creates a perspective projection matrix
mat4 perspective_mat4(float l, float r, float b, float t, float n, float f);

mat4 perspective(float fov, float aspect, float front, float back);

//creates a look at matrix
mat4 look_at(vec3 position, vec3 target, vec3 up);

//creates a rotation matrix around an arbitary axis
mat4 rotation_axis_mat4(float angle, vec3 v);

//rotates the inputted matix around an arbitary axis
void rotate_axis_mat4(mat4 *mat, float angle, vec3 v);

//creates a transformation matrix from the vector
mat4 create_transform_mat4(Transform transform, vec4 v);

//translate the matrix by the vector
void translate_mat4(mat4 *mat, vec3 v);

//dilates the matrix by the vector
void scale_mat4(mat4 *mat, vec3 v);

//multiplies a mat4 by a vec4
vec4 mat4_times_vec4(mat4 mat, vec4 v);

#endif
