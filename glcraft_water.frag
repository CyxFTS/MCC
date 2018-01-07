#version 330 core
in vec3 FragPos;
in vec3 Normal;
// in vec2 texCoord;

out vec4 color;

uniform vec3 lightPos;
uniform vec3 eyePos;
// uniform sampler2D waterTexture;

void main()
{
	bool blinn = true;
	vec3 lightColor = vec3(0.8f, 0.8f, 0.8f);
	vec3 gridColor = vec3(0.0f, 0.0f, 0.50f);
	// vec3 gridColor = texture(waterTexture, texCoord);

	float ambientStrength = 0.3;
	vec3 ambient = ambientStrength * lightColor;
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);
	float diff = max(dot(norm, lightDir), 0.7);
	vec3 diffuse = diff * lightColor;
	float specularStrength = 1.0;
	vec3 viewDir = normalize(eyePos - FragPos);
	float spec = 0.8f;
	if (blinn)
	{
		vec3 halfwayDir = normalize(lightDir + viewDir);
		spec = pow(max(dot(norm, halfwayDir), 0.1), 128);
	}
	else
	{
		vec3 reflectDir = reflect(-lightDir, norm);
		spec = pow(max(dot(viewDir, reflectDir), 0.1), 32);
	}
	vec3 specular = specularStrength * spec * lightColor;
	vec3 result = (ambient + diffuse + specular) * gridColor;
	// vec4 reflecColor = vec4(1.0f, 0.66f, 0.9f, 0.6f);
	//color = vec4(result, 1);
	color = vec4(ambient + diffuse + specular, 1.0);
	color = vec4(result, 0.7);
	// color = vec4(gridColor, 0.7);
	// 0.8f, 0.6f, 0.4f, 1.0f);
}