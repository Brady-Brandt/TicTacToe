#ifndef GLH_CAMERA_H
#define GLH_CAMERA_H
#include <stdbool.h>
#include <glmath.h>

typedef enum {
  FORWARD,
  BACKWARD,
  LEFT,
  RIGHT
} Camera_Movement;

extern const float YAW;
extern const float PITCH;
extern const float SPEED;
extern const float SENSITIVITY;
extern const float ZOOM;
extern const vec3 FRONT;
extern const vec3 UP;



typedef struct{
  vec3 Position; //camera pos
  vec3 Front;
  vec3 Up;
  vec3 Right;
  vec3 WorldUp;

  float Yaw;
  float Pitch;

  //camera options
  float MovementSpeed;
  float MouseSensitivity;
  float Zoom;

  bool PitchConstraint;
} camera;

//returns a camera object created from vectors
camera create_camera_vectors(vec3 position, vec3 up, float yaw, float pitch);

//returns a camera object created from scalar values
camera create_camera_values(float pos_x, float pos_y, float pos_z, float up_x, float up_y, float up_z, float yaw, float pitch);

//sets the camera speed, sensitivity and zoom
void set_camera_options(camera *cam, float speed, float sensitivity, float zoom);

//returns the view matrix
mat4 get_view_mat4(camera cam);

//processes keyboard input
void process_keyboard(camera *cam, Camera_Movement direction, float delta_time);

//processes mouse input
void process_mouse(camera *cam, float x_offset, float y_offset);

//processes the scrollwhell events
void process_scroll(camera *cam, float y_offset);

void update_camera_vectors(camera *cam);


#endif
