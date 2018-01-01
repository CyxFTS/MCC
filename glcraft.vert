#version 330 core
layout (location = 0) in vec4 coord;
layout (location = 1) in float normal_kind;
uniform mat4 mvp;
uniform mat4 lightSpaceMatrix;
out vec4 texcoord;
out vec3 normal;
out vec4 fragPosLightSpace;

void main(void) {
	// Just pass the original vertex coordinates to the fragment shader as texture coordinates
	texcoord = coord;
	normal = vec3(0);
	normal[int(abs(normal_kind)) - 1] = sign(normal_kind);

	fragPosLightSpace = lightSpaceMatrix * vec4(coord.xyz, 1);
	// Apply the model-view-projection matrix to the xyz components of the vertex coordinates
	gl_Position = mvp * vec4(coord.xyz, 1);
}
