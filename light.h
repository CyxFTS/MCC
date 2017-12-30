#pragma once
#ifndef LIGHT_H
#define LIGHT_H
#include <glad\glad.h>
#include <glfw/glfw3.h>
#include <GLM\glm.hpp>

struct DirlightUniform {
	GLint direction, ambient, diffuse, specular;
};

struct DirectLight {
	glm::vec3 direction, ambient, diffuse, specular;
	DirectLight() :
		direction(glm::vec3(0)),
		ambient(glm::vec3(0)),
		diffuse(glm::vec3(0)),
		specular(glm::vec3(0)) {}
	void UniformSet(const DirlightUniform & du) {
		glUniform3f(du.direction, direction.x, direction.y, direction.z);
		glUniform3f(du.ambient, ambient.x, ambient.y, ambient.z);
		glUniform3f(du.diffuse, diffuse.x, diffuse.y, diffuse.z);
		glUniform3f(du.specular, specular.x, specular.y, specular.z);
	}
};

#endif // LIGHT_H
