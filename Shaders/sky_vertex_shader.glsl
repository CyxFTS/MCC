#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 uv;

out vec2 fragment_uv;
out vec3 pos;
out vec3 star_pos;

uniform mat4 mvp;
uniform mat3 stars_rotation;

void main()
{
    gl_Position = mvp * vec4(position, 1.0);
    pos = position;
    star_pos = stars_rotation * normalize(pos);
    fragment_uv = uv;
}