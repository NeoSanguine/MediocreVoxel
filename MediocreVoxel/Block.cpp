#include "Block.h"
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>

Block::Block()
{
	this->type = BlockType::AIR;
}

Block::~Block()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

void Block::init(const glm::vec3& position, BlockType type)
{
	this->type = type;

	float vertices[] = {
		-0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,

		-0.5f, -0.5f,  0.5f,
		 0.5f, -0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f,

		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,

		 0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,

		-0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f,  0.5f,
		 0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f, -0.5f,

		-0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f,
	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	//  then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	m_position = position;

	m_color = MediocreEngine::ColorRGBA8(255, 0, 0);
}

void Block::update(float deltaTime)
{
	//update blocks attributes
}

void Block::render(MediocreEngine::GLSLProgram program, glm::mat4 model)
{
	if (m_active) {

		glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

		int colorLocation = program.getUniformLocation("vertexColor");
		glUniform4f(colorLocation, (float)m_color.r / 255.0f, (float)m_color.g / 255.0f, (float)m_color.b / 255.0f, (float)m_color.a / 255.0f);

		// position our model matrix according to our world position
		model = glm::translate(model, glm::vec3(m_position.x, m_position.y, m_position.z));

		// update our model matrix
		int modelLocation = program.getUniformLocation("model");
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));

		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
	}

	
}

bool Block::isActive()
{
	return m_active;
}

void Block::setPosition(const glm::vec3& position)
{
	m_position = position;
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
}

void Block::setActive(bool active)
{
	this->m_active = active;
}
