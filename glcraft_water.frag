#version 330 core
in vec3 FragPos;
in vec3 Normal;

out vec4 color;

void main()
{
	//color = vec4(result, 1);
	color = vec4(0.60f, 0.96f, 1.0f, 0.8f);
	// 0.8f, 0.6f, 0.4f, 1.0f);
}