#include "VAO.h"
#include "VBO.h"

struct VAO vao_create()
{
	struct VAO self;

	glGenVertexArrays(1, &self.handle);

	return self;
}

void vao_destroy(struct VAO self)
{
	glDeleteVertexArrays(1, &self.handle);
}

void vao_bind(struct VAO self)
{
	glBindVertexArray(self.handle);
}

void vao_unbind()
{
	glBindVertexArray(0);
}

void vao_attribute(struct VAO self, struct VBO vbo, GLuint index, GLint size, GLenum type, GLsizei stride, size_t offset)
{
	vao_bind(self);
	vbo_bind(vbo);
	glVertexAttribPointer(index, size, type, GL_FALSE, stride, (void*)offset);
	glEnableVertexAttribArray(index);
}
