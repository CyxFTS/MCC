#version 120
#define lowp 
#define mediump
#define highp
attribute vec4 coord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 mvp;

varying vec4 texcoord;

void main(void) {
    texcoord = coord;
    gl_Position = mvp * vec4(coord.xyz, 1);
}

