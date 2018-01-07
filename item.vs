#version 330 core
layout (location = 0) in vec4 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

uniform mat4 itemmvp;

out vec3 ourColor;
out vec2 TexCoord;

void main()
{
    gl_Position = itemmvp * vec4(aPos.xyz, 1.0);
    ourColor = aColor;
    TexCoord = aTexCoord;
}