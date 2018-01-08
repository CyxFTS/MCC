#version 330 core
out vec4 FragColor;
struct DirLight{
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
uniform DirLight dirlight;
in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D itemTexture;
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir, vec3 texColor, vec3 texSpec, float shininess){
    vec3 ambient = light.ambient * texColor;

    vec3 lightDir = normalize(-light.direction);
    float diff = max(dot(lightDir, normal), 0.0);
    vec3 diffuse = diff * texColor * light.diffuse;

    vec3 reflectDir = normalize(reflect(-lightDir, normal));
    float spec = pow(max(dot(reflectDir, viewDir), 0.0), shininess);
    vec3 specular = light.specular * spec * texSpec;
    return ambient + (diffuse + specular);
}
void main()
{
	vec3 normal = vec3(0,1,0);
	vec4 color = texture(itemTexture, TexCoord);
	vec3 viewDir = normalize(-dirlight.direction);
	color.xyz = CalcDirLight(dirlight, normal, viewDir, color.xyz, vec3(0.3), 32);
	FragColor = color;
}