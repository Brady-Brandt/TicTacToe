#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 atex_coords;

out vec2 tex_coords;
uniform mat4 button_model;


void main(){
  gl_Position = button_model * vec4(aPos, 1.0);
  tex_coords = vec2(atex_coords.x, atex_coords.y);
}
