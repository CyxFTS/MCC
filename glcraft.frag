#version 330 core
struct DirLight{
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
uniform DirLight dirlight;
uniform vec3 viewPos;
in vec4 texcoord;
in vec3 normal;
uniform sampler2D texture;

const vec4 fogcolor = vec4(0.6, 0.8, 1.0, 1.0);
const float fogdensity = .00003;

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir, vec3 texColor, vec3 texSpec, float shininess){
    vec3 ambient = light.ambient * texColor;

    vec3 lightDir = normalize(-light.direction);
    float diff = max(dot(lightDir, normal), 0.0);
    vec3 diffuse = diff * texColor * light.diffuse;

    vec3 reflectDir = normalize(reflect(-lightDir, normal));
    float spec = pow(max(dot(reflectDir, viewDir), 0.0), shininess);
    vec3 specular = light.specular * spec * texSpec;
    return ambient + diffuse + specular;
}

void main(void) {
	vec2 coord2d;
	float intensity;

	// If the texture index is negative, it is a top or bottom face, otherwise a side face
	// Side faces are less bright than top faces, simulating a sun at noon
	if(texcoord.w < 0.0) {
		coord2d = vec2((fract(texcoord.x) + texcoord.w) / 16.0, texcoord.z);
		intensity = 1.0;
	} else {
		coord2d = vec2((fract(texcoord.x + texcoord.z) + texcoord.w) / 16.0, -texcoord.y);
		intensity = 0.85;
	}

	vec4 color = texture2D(texture, coord2d);

	// Attenuate sides of blocks
	color.xyz *= intensity;
	vec3 viewDir = normalize(viewPos - texcoord.xyz);
	vec3 tmpColor = CalcDirLight(dirlight, normal, viewDir, color.xyz, vec3(0.3), 32);
	color.xyz = tmpColor;

	// Calculate strength of fog
	float z = gl_FragCoord.z / gl_FragCoord.w;
	float fog = clamp(exp(-fogdensity * z * z), 0.2, 1.0);

	// Final color is a mix of the actual color and the fog color
	gl_FragColor = mix(fogcolor, color, fog);
}
