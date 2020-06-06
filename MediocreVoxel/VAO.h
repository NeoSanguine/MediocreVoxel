#pragma once

#ifndef VAO_H_
#define VAO_H_

#include <GL\glew.h>

struct VAO {
	GLuint handle;
};

struct VAO vao_create();

void vao_destroy(struct VAO self);

void vao_bind(struct VAO self);

void vao_unbind();

void vao_attribute( struct VAO self, struct VBO vbo, GLuint index, GLint size, GLenum type, GLsizei stride, size_t offset);

#endif // VAO_H_
