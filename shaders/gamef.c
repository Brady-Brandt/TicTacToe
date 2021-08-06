#version 330 core
out vec4 FragColor;

uniform vec3 color;
in vec2 tex_coords;
uniform sampler2D tex;
uniform vec4 isTexture;

void main(){
  FragColor = max(texture(tex, tex_coords), isTexture) * vec4(color, 1.0);
}
