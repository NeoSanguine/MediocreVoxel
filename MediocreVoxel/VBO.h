#pragma once
#ifndef VBO_H_
#define VBO_H_

#include <GL/glew.h>

struct VBO {
	GLuint handle;
	GLint type;
	bool dynamic;
};

struct VBO vbo_create(GLint type, bool dynamic);

void vbo_destroy(struct VBO self);

void vbo_bind(struct VBO self);

void vbo_unbind(struct VBO self);

void vbo_buffer(struct VBO self, void* data, size_t offset, size_t count);

#endif // VBO_H_
