#version 330 core
layout (location = 0) in vec3 point;
layout (location = 1) in vec2 texture;

out vec2 TexCoord;

void main(){
	TexCoord = texture;
	gl_Position = vec4(point, 1.0f);
}
