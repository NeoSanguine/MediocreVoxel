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

	void init(BlockType type = BlockType::GRASS);

	void update(float deltaTime);

	void render(MediocreEngine::GLSLProgram program, glm::mat4 model, glm::ivec3 renderPosition);

	bool isActive();

	void setColor(MediocreEngine::ColorRGBA8 color);
	void setColor(int r, int g, int b, int a);
	void setActive(bool active);
	MediocreEngine::ColorRGBA8 getColor();

	void erase();

private:
	MediocreEngine::ColorRGBA8 m_color;
	bool m_active = true;
	BlockType type;
};