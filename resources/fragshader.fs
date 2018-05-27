#version 330 core
in vec2 UV;

out vec3 color;

uniform sampler2D tSampler;

void main(){
  color = texture(tSampler, UV).rgb;
}
