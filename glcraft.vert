#version 330 core
layout (location = 0) in vec4 coord;
layout (location = 1) in float normal_kind;
layout (location = 2) in vec3 aTangent;
layout (location = 3) in vec3 aBitangent;
layout (location = 4) in vec2 aTexCoords;
uniform mat4 mvp;
uniform mat4 lightSpaceMatrix;
out vec4 texcoord;
out vec3 normal;
out vec4 fragPosLightSpace;
uniform mat4 model;
uniform vec3 viewPos;
uniform vec3 lightDir;
out VS_OUT {
    vec3 FragPos;
    vec2 TexCoords;
	vec3 TangentLightDir;
    vec3 TangentViewPos;
    vec3 TangentFragPos;
} vs_out;

void main(void) {
	texcoord = coord;
	normal = vec3(0);
	normal[int(abs(normal_kind)) - 1] = sign(normal_kind);
	vec2 coord2d;
	
	// If the texture index is negative, it is a top or bottom face, otherwise a side face
	// Side faces are less bright than top faces, simulating a sun at noon
	if(coord.w < 0.0) 
		coord2d = vec2((fract(coord.x) + coord.w) / 16.0, coord.z);
	else 
		coord2d = vec2((fract(coord.x + coord.z) + coord.w) / 16.0, -coord.y);

	vs_out.FragPos = vec3(model * vec4(coord.xyz, 1.0));   
    vs_out.TexCoords = coord2d;

	mat3 normalMatrix = transpose(inverse(mat3(model)));
    vec3 T = normalize(normalMatrix * aTangent);
    vec3 N = normalize(normalMatrix * normal);
    T = normalize(T - dot(T, N) * N);
    vec3 B = cross(N, T);

	mat3 TBN = transpose(mat3(T, B, N));    
	vs_out.TangentLightDir = TBN * lightDir;
    vs_out.TangentViewPos  = TBN * viewPos;
    vs_out.TangentFragPos  = TBN * vs_out.FragPos;

	// Just pass the original vertex coordinates to the fragment shader as texture coordinates
	

	fragPosLightSpace = lightSpaceMatrix * vec4(coord.xyz, 1);
	// Apply the model-view-projection matrix to the xyz components of the vertex coordinates
	gl_Position = mvp * vec4(coord.xyz, 1);
}
