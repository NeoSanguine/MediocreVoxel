#include "Block.h"
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>
#include "VAO.h"
#include "VBO.h"



Block::Block()
{
	this->type = BlockType::AIR;
	m_color = MediocreEngine::ColorRGBA8(255, 255, 255);
}

Block::~Block()
{
	
}

void Block::init(BlockType type)
{
	this->type = type;
	m_active = true;
}

void Block::update(float deltaTime)
{
	//update blocks attributes
}

void Block::render(MediocreEngine::GLSLProgram program, glm::mat4 model, glm::ivec3 renderPosition)
{
	if (m_active) {
		//glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
		

		int colorLocation = program.getUniformLocation("vertexColor");
		glUniform4f(colorLocation, (float)m_color.r / 255.0f, (float)m_color.g / 255.0f, (float)m_color.b / 255.0f, (float)m_color.a / 255.0f);

		// position our model matrix according to our world position
		model = glm::translate(model, glm::vec3(renderPosition.x, renderPosition.y, renderPosition.z));

		// update our model matrix
		int modelLocation = program.getUniformLocation("model");
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));

		//glBindVertexArray(0);
		//vao_unbind();
	}
	
}

bool Block::isActive()
{
	return m_active;
}


void Block::setColor(MediocreEngine::ColorRGBA8 color)
{
	
	m_color = color;
}

void Block::setColor(int r, int g, int b, int a)
{
	m_color.r = r;
	m_color.g = g;
	m_color.b = b;
	m_color.a = a;
}

void Block::setActive(bool active)
{
	this->m_active = active;
}

MediocreEngine::ColorRGBA8 Block::getColor()
{
	return m_color;
}


void Block::erase()
{
	m_active = false;
}

