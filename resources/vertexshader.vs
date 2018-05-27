#version 330 core
layout(location = 0) in vec4 vertex;
layout(location = 1) in vec2 vertexUV;

uniform mat4 MVP;

out vec2 UV;

void main(){
	gl_Position = MVP * vertex;
	UV = vertexUV;
}


