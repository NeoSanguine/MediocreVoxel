#pragma once

#include <glm.hpp>

class Vertex3D {
public:

	glm::vec3 position;
	glm::vec3 normals;
	glm::vec2 uvs;

	Vertex3D(glm::vec3 position, glm::vec2 uvs, glm::vec3 normals) {
		this->position = position;
		this->uvs = uvs;
		this->normals = normals;
	}
	
};