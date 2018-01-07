#pragma once
#include <math.h>
//#include <GL/glew.h>
#include <glad\glad.h>
#include <glfw/glfw3.h>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>
#include <sstream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define PI 3.14159265359
#define DAY_LENGTH 30

class Sky
{
private:
	GLuint skyVAO, skyVBO;
	GLuint skyTexture, cloudTexture1, cloudTexture2, nightTexture1;
	GLuint skyShaderProgram;
	float record_t, weather_factor;

public:
	void normalize(float *x, float *y, float *z);

	int _make_sphere(float *data, float r, int detail, float *a, float *b, float *c, float *ta, float *tb, float *tc);

	void make_sphere(float *data, float r, int detail);

	void checkError(unsigned int shader, const bool type);

	float get_time_of_day();

	GLuint create_program(const char *vertexfile, const char *fragmentfile);

	void generateSkyVAO();

	GLuint generateTexture(const char *path);

	void generateSkyTexture();

	void generateSkyShaderProgram();

	void getReadySky();

	void Sky::renderSky(glm::mat4 matrix);

	void deleteSky();
};
