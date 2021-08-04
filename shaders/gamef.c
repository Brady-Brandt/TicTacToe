#version 330 core
out vec4 FragColor;

uniform vec3 color;
in vec2 tex_coords;
uniform sampler2D tex;
uniform vec3 isTexture;

void main(){
  FragColor = (texture(tex, tex_coords) + vec4(isTexture, 1.0)) * vec4(color, 1.0);
}
