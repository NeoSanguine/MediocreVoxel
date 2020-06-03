#pragma once

#include <MediocreEngine/vertex.h>
#include <MediocreEngine/GLSLProgram.h>
#include <glm.hpp>
#include <GL/glew.h>

#include "BlockType.h"

class Block {

public:

	Block();
	~Block();

	void init(const glm::vec3& position, BlockType type = BlockType::AIR);

	void update(float deltaTime);

	void render(MediocreEngine::GLSLProgram program, glm::mat4 model);

	void setPosition(const glm::vec3& position);
	void setColor(MediocreEngine::ColorRGBA8 color);
	void setColor(int r, int g, int b, int a);
	void setActive(bool active);

private:
	MediocreEngine::ColorRGBA8 m_color;
	glm::vec3 m_position;
	unsigned int VBO = 0;
	unsigned int VAO = 0;
	bool active = true;
	BlockType type;
};