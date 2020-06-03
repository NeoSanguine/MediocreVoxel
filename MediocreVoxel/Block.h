#pragma once

#include <MediocreEngine/vertex.h>
#include <MediocreEngine/GLSLProgram.h>
#include <glm.hpp>
#include <GL/glew.h>

class Block {

public:

	Block();
	~Block();

	void init(const glm::vec3& position);

	void update();

	void render(MediocreEngine::GLSLProgram program, glm::mat4 model);

private:
	MediocreEngine::ColorRGBA8 m_color;
	glm::vec3 m_position;
	unsigned int VBO = 0;
	unsigned int VAO = 0;

};