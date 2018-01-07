#version 330 core
struct DirLight{
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
uniform DirLight dirlight;
uniform int enableFxAA;
uniform vec3 viewPos;
in vec4 texcoord;
in vec4 fragPosLightSpace;
uniform sampler2D shadow;
uniform sampler2D texture;
uniform sampler2D normalMap;
// uniform bool under_water;

in VS_OUT {
    vec3 FragPos;
    vec2 TexCoords;
	vec3 TangentLightDir;
    vec3 TangentViewPos;
    vec3 TangentFragPos;
} fs_in;

const vec4 fogcolor = vec4(0.6, 0.8, 1.0, 1.0);
const float fogdensity = .00003;

float ShadowCalculation(vec4 fragPosLightSpace, vec3 normal, vec3 direction, vec2 pixelSize){
	vec3 projCoord = fragPosLightSpace.xyz / fragPosLightSpace.w;
	projCoord = projCoord * 0.5 + 0.5;
	float currentDepth = projCoord.z > 1 ? 0 : projCoord.z;
	float bias = 0.0008;//max(0.0001 * (1 - dot(normal, direction)), 0.000001);
	float shadowCal  = currentDepth - bias >texture2D(shadow, projCoord.xy).r ? 1 : 0;//= 0;
	// for(int x = -1; x <= 1; ++x){
	// 	for(int y = -1; y <= 1; ++y){
	// 		float closetDepth = texture2D(shadow, projCoord.xy + vec2(x, y) * pixelSize).r;
	// 		shadowCal += currentDepth - bias > closetDepth ? 1 : 0;
	// 	}
	// }
	// return shadowCal / 9.0;
	return shadowCal;
}

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir, vec3 texColor, vec3 texSpec, float shininess){
    vec3 ambient = light.ambient * texColor;

    vec3 lightDir = normalize(-fs_in.TangentLightDir);
    float diff = max(dot(lightDir, normal), 0.0);
    vec3 diffuse = diff * texColor * light.diffuse;

    vec3 reflectDir = normalize(reflect(-lightDir, normal));
    float spec = pow(max(dot(reflectDir, viewDir), 0.0), shininess);
    vec3 specular = light.specular * spec * texSpec;
    return ambient + (diffuse + specular) * (1 - ShadowCalculation(fragPosLightSpace, normal, light.direction,  1.0 / textureSize(shadow, 0)));
}

void main(void) {
	
	vec2 coord2d;
	float intensity;
	if(texcoord.w < 0.0) {
		coord2d = vec2((fract(texcoord.x) + texcoord.w) / 16.0, texcoord.z);
		intensity = 1.0;
	} else {
		coord2d = vec2((fract(texcoord.x + texcoord.z) + texcoord.w) / 16.0, -texcoord.y);
		intensity = 0.85;
	}
	vec3 normal = texture(normalMap, coord2d).rgb;
	normal = normalize(normal * 2.0 - 1.0);  // this normal is in tangent space
	// If the texture index is negative, it is a top or bottom face, otherwise a side face
	// Side faces are less bright than top faces, simulating a sun at noon
	
	vec4 color = texture2D(texture, coord2d);

	// Attenuate sides of blocks
	//color.xyz *= intensity;
	vec3 viewDir = normalize(fs_in.TangentViewPos - fs_in.TangentFragPos);
	color.xyz = CalcDirLight(dirlight, normal, viewDir, color.xyz, vec3(0.3), 32);

	// Calculate strength of fog
	float z = gl_FragCoord.z / gl_FragCoord.w;
	float fog = clamp(exp(-fogdensity * z * z), 0.2, 1.0);

	// Final color is a mix of the actual color and the fog color
	gl_FragColor = color;

	
	if (viewPos.y < -65.5f){
		// gl_FragColor = vec4(0.0f, 0.0f, 0.50f, 1.0f);
		gl_FragColor = mix(gl_FragColor, vec4(0.0f, 0.0f, 0.50f, 1.0f), 0.5f);
	}
	
}
