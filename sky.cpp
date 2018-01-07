#pragma once
#include "sky.h"
//#ifndef STB_IMAGE_IMPLEMENTATION
//#define STB_IMAGE_IMPLEMENTATION
//#include <stb\stb_image.h>
//#endif
//#include "STB\stb_image.h"
#include <stb\stb_image.h>

void Sky::normalize(float *x, float *y, float *z)
{
	float d = sqrtf((*x) * (*x) + (*y) * (*y) + (*z) * (*z));
	*x /= d; *y /= d; *z /= d;
}

int Sky::_make_sphere(float *data, float r, int detail, float *a, float *b, float *c, float *ta, float *tb, float *tc)
{
	if (detail == 0) {
		float *d = data;
		*(d++) = a[0] * r; *(d++) = a[1] * r; *(d++) = a[2] * r;
		*(d++) = a[0]; *(d++) = a[1]; *(d++) = a[2];
		*(d++) = ta[0]; *(d++) = ta[1];
		*(d++) = b[0] * r; *(d++) = b[1] * r; *(d++) = b[2] * r;
		*(d++) = b[0]; *(d++) = b[1]; *(d++) = b[2];
		*(d++) = tb[0]; *(d++) = tb[1];
		*(d++) = c[0] * r; *(d++) = c[1] * r; *(d++) = c[2] * r;
		*(d++) = c[0]; *(d++) = c[1]; *(d++) = c[2];
		*(d++) = tc[0]; *(d++) = tc[1];
		return 1;
	}
	else {
		float ab[3], ac[3], bc[3];
		for (int i = 0; i < 3; i++) {
			ab[i] = (a[i] + b[i]) / 2;
			ac[i] = (a[i] + c[i]) / 2;
			bc[i] = (b[i] + c[i]) / 2;
		}
		normalize(ab + 0, ab + 1, ab + 2);
		normalize(ac + 0, ac + 1, ac + 2);
		normalize(bc + 0, bc + 1, bc + 2);
		float tab[2], tac[2], tbc[2];
		tab[0] = 0; tab[1] = 1 - acosf(ab[1]) / PI;
		tac[0] = 0; tac[1] = 1 - acosf(ac[1]) / PI;
		tbc[0] = 0; tbc[1] = 1 - acosf(bc[1]) / PI;
		int total = 0;
		int n;
		n = _make_sphere(data, r, detail - 1, a, ab, ac, ta, tab, tac);
		total += n; data += n * 24;
		n = _make_sphere(data, r, detail - 1, b, bc, ab, tb, tbc, tab);
		total += n; data += n * 24;
		n = _make_sphere(data, r, detail - 1, c, ac, bc, tc, tac, tbc);
		total += n; data += n * 24;
		n = _make_sphere(data, r, detail - 1, ab, bc, ac, tab, tbc, tac);
		total += n; data += n * 24;
		return total;
	}
}

void Sky::make_sphere(float *data, float r, int detail)
{
	// detail, triangles, floats
	// 0, 8, 192
	// 1, 32, 768
	// 2, 128, 3072
	// 3, 512, 12288
	// 4, 2048, 49152
	// 5, 8192, 196608
	// 6, 32768, 786432
	// 7, 131072, 3145728
	static int indices[8][3] = {
		{ 4, 3, 0 },{ 1, 4, 0 },
		{ 3, 4, 5 },{ 4, 1, 5 },
		{ 0, 3, 2 },{ 0, 2, 1 },
		{ 5, 2, 3 },{ 5, 1, 2 }
	};
	static float positions[6][3] = {
		{ 0, 0,-1 },{ 1, 0, 0 },
		{ 0,-1, 0 },{ -1, 0, 0 },
		{ 0, 1, 0 },{ 0, 0, 1 }
	};
	static float uvs[6][3] = {
		{ 0, 0.5 },{ 0, 0.5 },
		{ 0, 0 },{ 0, 0.5 },
		{ 0, 1 },{ 0, 0.5 }
	};
	int total = 0;
	for (int i = 0; i < 8; i++) {
		int n = _make_sphere(
			data, r, detail,
			positions[indices[i][0]],
			positions[indices[i][1]],
			positions[indices[i][2]],
			uvs[indices[i][0]],
			uvs[indices[i][1]],
			uvs[indices[i][2]]);
		total += n; data += n * 24;
	}
}

void Sky::checkError(unsigned int shader, const bool type)
{
	int success;
	char infoLog[512];
	if (type == false) {
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(shader, 512, NULL, infoLog);
			std::cout << infoLog << std::endl;
		}
	}
	else
		if (type == true) {
			glGetProgramiv(shader, GL_LINK_STATUS, &success);
			if (!success) {
				glGetProgramInfoLog(shader, 512, NULL, infoLog);
				std::cout << infoLog << std::endl;
			}
		}
}

float Sky::get_time_of_day()
{
	if (DAY_LENGTH <= 0)
		return 0.5;
	float t;
	t = glfwGetTime();
	t = t / DAY_LENGTH;
	t = t - (int)t;
	return t;
}

GLuint Sky::create_program(const char *vertexfile, const char *fragmentfile)
{
	std::string vertexCode, fragmentCode;
	std::ifstream vertexFile, fragmentFile;
	vertexFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fragmentFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try {
		vertexFile.open(vertexfile);
		fragmentFile.open(fragmentfile);

		std::stringstream vertexStream, fragmentStream;
		vertexStream << vertexFile.rdbuf();
		fragmentStream << fragmentFile.rdbuf();
		vertexFile.close();
		fragmentFile.close();
		vertexCode = vertexStream.str();
		fragmentCode = fragmentStream.str();
	}
	catch (std::ifstream::failure) {
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULY_READ" << std::endl;
		return 0;
	}
	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vShaderCode, NULL);
	glCompileShader(vertexShader);
	checkError(vertexShader, false);
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fShaderCode, NULL);
	glCompileShader(fragmentShader);
	checkError(fragmentShader, false);
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	checkError(shaderProgram, true);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	vertexShader = -1;
	fragmentShader = -1;

	return shaderProgram;
}

void Sky::generateSkyVAO()
{
	float data[12288];
	make_sphere(data, 1, 3);

	glGenVertexArrays(1, &skyVAO);
	glGenBuffers(1, &skyVBO);
	glBindVertexArray(skyVAO);

	glBindBuffer(GL_ARRAY_BUFFER, skyVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 8, 0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 8, (GLvoid *)(sizeof(GLfloat) * 3));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 8, (GLvoid *)(sizeof(GLfloat) * 6));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

GLuint Sky::generateTexture(const char *path)
{
	GLuint sky;
	glGenTextures(1, &sky);
	glBindTexture(GL_TEXTURE_2D, sky);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char *data = stbi_load(path, &width, &height, &nrChannels, 0);
	//std::cout << nrChannels << std::endl;
	if (data)
	{
		//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
	return sky;
}

void Sky::generateSkyTexture()
{
	skyTexture = generateTexture("Textures/sky.png");
	cloudTexture1 = generateTexture("Textures/clouds1.gif");
	cloudTexture2 = generateTexture("Textures/clouds2.gif");
	nightTexture1 = generateTexture("Textures/night_sky_1.png");
	glUseProgram(skyShaderProgram);
	glUniform1i(glGetUniformLocation(skyShaderProgram, "skyTtexture"), 0);
	glUniform1i(glGetUniformLocation(skyShaderProgram, "cloudTexture1"), 1);
	glUniform1i(glGetUniformLocation(skyShaderProgram, "cloudTexture2"), 2);
	glUniform1i(glGetUniformLocation(skyShaderProgram, "nightTexture1"), 3);
}

void Sky::generateSkyShaderProgram()
{
	skyShaderProgram = create_program("Shaders/sky_vertex_shader.glsl", "Shaders/sky_fragment_shader.glsl");
}

void Sky::getReadySky()
{
	srand(time(NULL));
	record_t = 0.0f;
	weather_factor = 0.9f;
	generateSkyShaderProgram();
	generateSkyVAO();
	generateSkyTexture();
}

void Sky::renderSky(glm::mat4 matrix)
{
	glUseProgram(skyShaderProgram);
	//glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_FALSE);
	glUniformMatrix4fv(glGetUniformLocation(skyShaderProgram, "mvp"), 1, GL_FALSE, glm::value_ptr(matrix));
	glm::mat4 tmp_stars_rotation;
	glm::mat3 stars_rotation = glm::mat3(glm::rotate(tmp_stars_rotation, (float)glfwGetTime() / DAY_LENGTH, glm::vec3(0.6f, -1.0f, 0.0f)));
	glUniformMatrix3fv(glGetUniformLocation(skyShaderProgram, "stars_rotation"), 1, GL_FALSE, glm::value_ptr(stars_rotation));
	float tmp = get_time_of_day();
	glUniform1f(glGetUniformLocation(skyShaderProgram, "timer"), tmp);
	if (record_t > tmp)
	{
		weather_factor = ((float)rand() / RAND_MAX) * 0.5f + 0.5f;
	}
	record_t = tmp;
	glUniform1f(glGetUniformLocation(skyShaderProgram, "weatherFactor"), weather_factor);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, skyTexture);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, cloudTexture1);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, cloudTexture2);
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, nightTexture1);
	glBindVertexArray(skyVAO);
	glDrawArrays(GL_TRIANGLES, 0, 512 * 3);
	glBindVertexArray(0);
	glDepthMask(GL_TRUE);
}

void Sky::deleteSky()
{
	glDeleteVertexArrays(1, &skyVAO);
	glDeleteBuffers(1, &skyVBO);
}