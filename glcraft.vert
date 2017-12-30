#version 330 core
layout (location = 0) in vec4 coord;
layout (location = 1) in float normal_kind;
uniform mat4 mvp;
out vec4 texcoord;
out vec3 normal;

void main(void) {
	// Just pass the original vertex coordinates to the fragment shader as texture coordinates
	texcoord = coord;
	normal = vec3(0);
	normal[int(abs(normal_kind)) - 1] = sign(normal_kind);

	// Apply the model-view-projection matrix to the xyz components of the vertex coordinates
	gl_Position = mvp * vec4(coord.xyz, 1);
}
