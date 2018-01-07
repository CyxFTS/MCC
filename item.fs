#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D itemTexture;

void main()
{
	FragColor = texture(itemTexture, TexCoord);
	//vec2 thisTexCoord;// = (0.685, 0.001);
	//if(TexCoord.w < 0.0) {
	//	thisTexCoord = vec2((fract(TexCoord.x) + TexCoord.w) / 16.0, TexCoord.z);
		//intensity = 1.0;
	//} else {
	//	thisTexCoord = vec2((fract(TexCoord.x + TexCoord.z) + TexCoord.w) / 16.0, -TexCoord.y);
		//intensity = 0.85;
	//}

    //FragColor = texture(itemTexture, thisTexCoord);
}