#version 330 core
out vec4 FragColor;

uniform vec3 button_color;

void main(){
  FragColor = vec4(button_color.x, button_color.y, button_color.z, 1.0f);
}
