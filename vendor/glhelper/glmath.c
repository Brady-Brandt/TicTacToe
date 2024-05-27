#include <glmath.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

const float GLH_PI = 3.1415926;
const float GLH_DEG = 180 / GLH_PI;
const float GLH_RAD = GLH_PI / 180;

//creates a 2d vector
vec2 Vec2(float x, float y){
  return (vec2){x,y};
}

//prints out a 2d vector in component form
void print_vec2(vec2 v){
  printf("{%g, %g}\n", v.x, v.y);
}

//normalizes a 2d vector
vec2 normalize_vec2(vec2 v){
  double magnitude = sqrt(v.x * v.x + v.y * v.y);
  if(magnitude == 0){
    return (vec2){0,0};
  }
  return (vec2){v.x / magnitude, v.y/magnitude};
}


vec2 add_vec2(vec2 v1, vec2 v2){
  return (vec2){v1.x + v2.x, v1.y + v2.y};
}

vec2 sub_vec2(vec2 v1, vec2 v2){
  return (vec2){v1.x - v2.x, v1.y - v2.y};
}

vec2 mult_vec2(vec2 v1, vec2 v2){
  return (vec2){v1.x * v2.x, v1.y * v2.y};
}

vec2 div_vec2(vec2 v1, vec2 v2){
  if(v2.x == 0 || v2.y == 0){
    printf("Error cannot divide by zero");
    return (vec2){0,0};
  }

  return (vec2){v1.x / v2.x, v1.y / v2.y};
}

float dot_vec2(vec2 v1, vec2 v2){
  return v1.x * v2.x + v1.y * v2.y;
}

vec2 scalar_mult_vec2(vec2 v1, float value){
  return (vec2){v1.x * value, v1.y * value};
}


//creates a vector
vec3 Vec3(float x,float y,float z){
  vec3 result = {x,y,z};
  return result;
}

//prints out a 3d vector in component form
void print_vec3(vec3 v){
  printf("{%g, %g, %g}\n", v.x, v.y,v.z);
}

//normalizes a 3d vector
vec3 normalize_vec3(vec3 v){
  double magnitude = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
  if(magnitude == 0){
    return (vec3){0,0,0};
  }
  vec3 result = {v.x / magnitude, v.y / magnitude, v.z / magnitude};
  return result;
}

//adds two 3d vectors together
vec3 add_vec3(vec3 v1, vec3 v2){
  vec3 result = {v1.x + v2.x, v1.y + v2.y, v1.z + v2.z};
  return result;
}

//subtracts 3d vect2 from vect1
vec3 sub_vec3(vec3 v1, vec3 v2){
  vec3 result = {v1.x - v2.x , v1.y - v2.y, v1.z - v2.z};
  return result;
}

//multiplies two vectors together
vec3 mult_vec3(vec3 v1, vec3 v2){
  vec3 result = {v1.x * v2.x , v1.y * v2.y, v1.z * v2.z};
  return result;
}

//performs scalar multiplication on a 3d vector
vec3 scalar_mult_vec3(vec3 v, double scalar){
    vec3 result = {scalar * v.x, scalar * v.y, scalar * v.z};
    return result;
}

//calculates the dot product of 2 3d vectors
double dot_vec3(vec3 v, vec3 v2){
  return v.x * v2.x + v.y * v2.y + v.z * v2.z;
}

//calculates the cross product between 2 3d vectors
vec3 cross_product(vec3 v1, vec3 v2){
  double x = v1.y * v2.z - v1.z * v2.y;
  double y = v1.z * v2.x - v1.x * v2.z;
  double z = v1.x * v2.y - v1.y * v2.x;
  vec3 result = {x, y, z};
  return result;
}

//creates a 4d vector from the component
vec4 Vec4(float x, float y, float z, float w){
  vec4 result = {x,y,z, w};
  return result;
}

//prints a 4d vector
void print_vec4(vec4 v){
  printf("{%f, %f, %f, %f}\n", v.x, v.y, v.z, v.w);
}

//normalizes a 4d vector
vec4 normalize_vec4(vec4 v){
  float magnitude = sqrt(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w);
  if(magnitude == 0)
    return (vec4){0,0,0,0};
  vec4 result = {v.x / magnitude, v.y / magnitude, v.z / magnitude, v.w/magnitude};
  return result;
}

vec4 add_vec4(vec4 v1, vec4 v2){
  return (vec4){v1.x + v2.x, v1.y + v2.y, v1.z + v2.z, v1.w + v2.w};
}

vec4 sub_vec4(vec4 v1, vec4 v2){
  return (vec4){v1.x - v2.x, v1.y - v2.y, v1.z - v2.z, v1.w - v2.w};
}

vec4 mult_vec4(vec4 v1, vec4 v2){
  return (vec4){v1.x * v2.x, v1.y * v2.y, v1.z * v2.z, v1.w * v2.w};
}

vec4 scalar_mult_vec4(vec4 v1, double scalar){
  return (vec4){v1.x * scalar, v1.y * scalar, v1.z * scalar, v1.w * scalar};
}

double dot_vec4(vec4 v1, vec4 v2){
  return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;
}

//creates a 4 * 4 matrix out of the given array in COLUMN-ORDER NOTATION
mat4 create_mat4(float arr[]){
  float *matrix = malloc(16 * sizeof(float));
  for(int i =0; i < 16; i++){
    matrix[i] = arr[i];
  }
  mat4 result = {matrix};
  return result;
}

//prints out a 4 * 4 matrix
void print_mat4(mat4 mat){
  for(int i =0; i < 4; i++){
    for(int j = 0; j < 4; j++){
      printf("%f \t", mat.matrix[i + j * 4]);
    }
    printf("\n");
  }
  printf("\n");
}

//returns an identity matrix with the corresponding value
mat4 identity_mat4(float value){
  float arr[] = {value,0,0,0,0,value,0,0,0,0,value,0,0,0,0,value};
  mat4 result = create_mat4(arr);
  return result;
}

//frees the memory from a mat4
void free_mat4(mat4 mat){
  free(mat.matrix);
}

//multiply 4 * 4 matrices
mat4 multiply_mat4(mat4 m1, mat4 m2){
  float *products = malloc(16 * sizeof(float));

  //array counter
  int iter = 0;
  double temp = 0;

  //Standard naive way of matrice multiplication
  for(int i =0; i < 4; i++){
    for(int j = 0; j < 4; j++){
      for(int k = 0; k < 4; k++){
        temp += m1.matrix[i * 4 + k] * m2.matrix[k * 4 + j];
      }
      products[iter] = temp;
      temp = 0;
      iter++;
    }
    }
    mat4 result = {products};
    return result;
}

//testing matrix print function
void test_mat4(mat4 mat){
  printf("(%f, %f, %f, %f) ", mat.matrix[0], mat.matrix[1], mat.matrix[2], mat.matrix[3]);
  printf("(%f, %f, %f, %f) ", mat.matrix[4], mat.matrix[5], mat.matrix[6], mat.matrix[7]);
  printf("(%f, %f, %f, %f) ", mat.matrix[8], mat.matrix[8], mat.matrix[10], mat.matrix[11]);
  printf("(%f, %f, %f, %f) \n", mat.matrix[12], mat.matrix[13], mat.matrix[14], mat.matrix[15]);
}

//scales a matrix by a constant scalar
void scalec_mat4(mat4 *mat, float scale){
  mat4 identity = identity_mat4(1.0f);
  identity.matrix[0] *= scale;
  identity.matrix[5] *= scale;
  identity.matrix[10] *= scale;
  mat4 product = multiply_mat4(identity, *mat);

  for(int i =0; i < 16; i++){
    mat->matrix[i] = product.matrix[i];
  }

  free_mat4(product);
  free_mat4(identity);
}

//creates a rotation matrix
mat4 rotation_mat4(Axis axis, float angle){
  mat4 result = identity_mat4(1.0f);

  float cosine = cosf(angle * GLH_RAD);
  //have to take in degrees or else we are off due to precision
  if(angle == 90){
    cosine = 1;
  }
  angle *= GLH_RAD;



  if(axis == GLH_X_AXIS){
    result.matrix[5] = cosine;
    result.matrix[9] = -1 * sinf(angle);
    result.matrix[6] = sinf(angle);
    result.matrix[10] = cosine;
  }
  else if(axis == GLH_Y_AXIS){
    result.matrix[0] = cosine;
    result.matrix[4] = sinf(angle);
    result.matrix[2] = sinf(angle) * -1;
    result.matrix[10] = cosine;
  }
  else{
    result.matrix[0] = cosine;
    result.matrix[4] = -1 * sinf(angle);
    result.matrix[1] = sinf(angle);
    result.matrix[5] = cosine;
  }
  return result;
}

//rotates the matrix
void rotate_mat4(mat4 *mat, Axis axis, float angle){
  //get the rotation matrix
  mat4 rotation = rotation_mat4(axis, angle);
  //multiply the rotation matrix by the input matrix to get the resulting transformation matrix
  mat4 result = multiply_mat4(*mat, rotation);

  //put the values from result into the inputted matrix
  for(int i =0; i < 16; i++){
    mat->matrix[i] = result.matrix[i];
  }

  free_mat4(result);
  free_mat4(rotation);
}

//creates an orthographic projection matrix
mat4 ortho(float l, float r, float b, float t, float n, float f){
  mat4 identity = identity_mat4(1.0f);

  identity.matrix[0]  = 2 / (r - l);
  identity.matrix[5]  = 2 / (t - b);
  identity.matrix[10] = -2 / (f - n);
  identity.matrix[12] = -(r + l) / (r - l);
  identity.matrix[13] = -(t + b) / (t - b);
  identity.matrix[14] = -(f + n) / (f - n);

  return identity;
}

//creates a perspective projection matrix
mat4 perspective_mat4(float l, float r, float b, float t, float n, float f){
  mat4 identity = identity_mat4(1.0f);

  identity.matrix[0]  = 2 * n / (r - l);
  identity.matrix[5]  = 2 * n / (t - b);
  identity.matrix[8]  = (r + l) / (r - l);
  identity.matrix[9]  = (t + b) / (t - b);
  identity.matrix[10] = -(f + n) / (f - n);
  identity.matrix[11] = -1;
  identity.matrix[14] = -(2 * f * n) / (f - n);
  identity.matrix[15] = 0;

  return identity;
}

mat4 perspective(float fov, float aspect, float front, float back){
  float tan = tanf(GLH_RAD * fov / 2 );
  float height = front * tan;
  float width = height * aspect;

  return perspective_mat4(-width, width, -height, height, front, back);
}


//creates a look at matrix
mat4 look_at(vec3 position, vec3 target, vec3 up){
  mat4 result = identity_mat4(1.0f);
  vec3 forward = normalize_vec3(sub_vec3(position, target));
  vec3 left = normalize_vec3(cross_product(up, forward));
  up = cross_product(forward, left);

  result.matrix[0] = left.x;
  result.matrix[1] = up.x;
  result.matrix[2] = forward.x;
  result.matrix[4] = left.y;
  result.matrix[5] = up.y;
  result.matrix[6] = forward.y;
  result.matrix[8] = left.z;
  result.matrix[9] = up.z;
  result.matrix[10] = forward.z;
  result.matrix[12] = -left.x * position.x - left.y * position.y - left.z * position.z;
  result.matrix[13] = -up.x * position.x - up.y * position.y - up.z * position.z;
  result.matrix[14] = -forward.x * position.x - forward.y * position.y - forward.z * position.z;

  return result;
}

//creates a rotation matrix around an arbitary axis
mat4 rotation_axis_mat4(float angle, vec3 v){
  vec3 unit = normalize_vec3(v);
  float x, y,z;
  x = unit.x;
  y = unit.y;
  z = unit.z;
  mat4 identity = identity_mat4(1.0f);

  float cosine = cos(angle * GLH_RAD);
  if(angle == 90){
    cosine = 1;
  }
  angle *= GLH_RAD;

  identity.matrix[0] = (1 - cosine) * (x * x) + cosine;
  identity.matrix[1] = (1 - cosine) * x * y + sin(angle) * z;
  identity.matrix[2] = (1 - cosine) * x * z - sin(angle) * y;
  identity.matrix[4] = (1 - cosine) * x * y - sin(angle) * z;
  identity.matrix[5] = (1 - cosf(angle)) * (y * y) + cosine;
  identity.matrix[6] = (1 - cosine) * y * z + sin(angle) * x;
  identity.matrix[8] = (1 - cosine) * x * z + sin(angle) * y;
  identity.matrix[9] = (1 - cosine) * y * z - sin(angle) * x;
  identity.matrix[10] = (1 - cosine) * (z * z) + cosine;

  return identity;
}

//rotates the inputted matix around an arbitary axis
void rotate_axis_mat4(mat4 *mat, float angle, vec3 v){
  mat4 rotation = rotation_axis_mat4(angle, v);
  mat4 product = multiply_mat4(*mat, rotation);

  for(int i =0; i < 16; i++){
    mat->matrix[i] = product.matrix[i];
  }

  free_mat4(rotation);
  free_mat4(product);
}


//creates a transformation matrix from the vector
mat4 create_transform_mat4(Transform transform, vec4 v){

  mat4 identity = identity_mat4(1.0f);

  if(transform == GLH_SCALE){
    identity.matrix[0] *= v.x;
    identity.matrix[5] *= v.y;
    identity.matrix[10] *= v.z;
    return identity;
  }
  if(transform == GLH_TRANSLATE){
    identity.matrix[12] += v.x;
    identity.matrix[13] += v.y;
    identity.matrix[14] += v.z;
    return identity;
  }

  identity.matrix[0] = 1 - 2 * (v.y * v.y) - 2 * (v.z * v.z);
  identity.matrix[1] = 2 * v.x * v.y + 2 * v.w * v.z;
  identity.matrix[2] = 2 * v.x * v.z - 2 * v.w * v.y;

  identity.matrix[4] = 2 * v.x * v.y - 2 * v.w * v.z;
  identity.matrix[5] = 1 - 2 * (v.x * v.x) - 2 * (v.z * v.z);
  identity.matrix[6] = 2 * v.y * v.z + 2 * v.w * v.x;

  identity.matrix[8] = 2 * v.x * v.z + 2 * v.w * v.y;
  identity.matrix[9] = 2 * v.y * v.z + 2 * v.w * v.x;
  identity.matrix[10] = 1 - 2 * (v.x * v.x) - 2 * (v.y * v.y);
  

}

//translate the matrix by the vector
void translate_mat4(mat4 *mat, vec3 v){
  mat4 identity = identity_mat4(1.0f);
  identity.matrix[12] += v.x;
  identity.matrix[13] += v.y;
  identity.matrix[14] += v.z;
  mat4 product = multiply_mat4(*mat, identity);

  for(int i =0; i < 16; i++){
    mat->matrix[i] = product.matrix[i];
  }

  free_mat4(product);
  free_mat4(identity);
}

//dilates the matrix by the vector
void scale_mat4(mat4 *mat, vec3 v){
  mat4 identity = identity_mat4(1.0f);
  identity.matrix[0] *= v.x;
  identity.matrix[5] *= v.y;
  identity.matrix[10] *= v.z;

  mat4 product = multiply_mat4(identity, *mat);

  for(int i =0; i < 16; i++){
    mat->matrix[i] = product.matrix[i];
  }

  free_mat4(product);
  free_mat4(identity);
}

//multiplies a mat4 by a vec4
vec4 mat4_times_vec4(mat4 mat, vec4 v){
  float dot_products[4];
  float vector[] = {v.x, v.y, v.z, v.w};

  double temp;
  for(int i =0; i < 4; i++){
    temp = 0;
    for(int j = 0; j < 4; j++){
      temp += mat.matrix[i + 4 * j] * vector[j];
    }
    dot_products[i] = temp;
  }


  vec4 result = {dot_products[0], dot_products[1], dot_products[2], dot_products[3]};
  return result;
}
