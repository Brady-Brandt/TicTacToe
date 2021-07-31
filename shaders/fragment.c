#version 330 core
out vec4 FragColor;

in vec2 tex_coords;
uniform  sampler2D text;
uniform vec3 button_color;

void main(){
  FragColor = texture(text, tex_coords) * vec4(button_color, 1.0f);
}
