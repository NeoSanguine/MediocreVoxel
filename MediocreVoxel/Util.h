#pragma once
#ifndef UTIL_H_
#define UTIL_H_

#include <glm.hpp>

static glm::vec3 PX_POS[6] = {

			glm::vec3(0.5f,0.5f,-0.5f),
			glm::vec3(0.5f,-0.5f,-0.5f),
			glm::vec3(0.5f,-0.5f,0.5f),
			glm::vec3(0.5f,-0.5f,0.5f),
			glm::vec3(0.5f,0.5f,0.5f),
			glm::vec3(0.5f,0.5f,-0.5f)

};

static glm::vec3 NX_POS[] = {

		glm::vec3(-0.5f,0.5f,-0.5f),
		glm::vec3(-0.5f,-0.5f,-0.5f),
		glm::vec3(-0.5f,-0.5f,0.5f),
		glm::vec3(-0.5f,-0.5f,0.5f),
		glm::vec3(-0.5f,0.5f,0.5f),
		glm::vec3(-0.5f,0.5f,-0.5f)

};

static glm::vec3 PY_POS[] = {

		glm::vec3(-0.5f,0.5f,0.5f),
		glm::vec3(-0.5f,0.5f,-0.5f),
		glm::vec3(0.5f,0.5f,-0.5f),
		glm::vec3(0.5f,0.5f,-0.5f),
		glm::vec3(0.5f,0.5f,0.5f),
		glm::vec3(-0.5f,0.5f,0.5f)

};

static glm::vec3 NY_POS[] = {

		glm::vec3(-0.5f,-0.5f,0.5f),
		glm::vec3(-0.5f,-0.5f,-0.5f),
		glm::vec3(0.5f,-0.5f,-0.5f),
		glm::vec3(0.5f,-0.5f,-0.5f),
		glm::vec3(0.5f,-0.5f,0.5f),
		glm::vec3(-0.5f,-0.5f,0.5f)

};

static glm::vec3 PZ_POS[] = {

		glm::vec3(-0.5f,0.5f,0.5f),
		glm::vec3(-0.5f,-0.5f,0.5f),
		glm::vec3(0.5f,-0.5f,0.5f),
		glm::vec3(0.5f,-0.5f,0.5f),
		glm::vec3(0.5f,0.5f,0.5f),
		glm::vec3(-0.5f,0.5f,0.5f)

};

static glm::vec3 NZ_POS[] = {

		glm::vec3(-0.5f,0.5f,-0.5f),
		glm::vec3(-0.5f,-0.5f,-0.5f),
		glm::vec3(0.5f,-0.5f,-0.5f),
		glm::vec3(0.5f,-0.5f,-0.5f),
		glm::vec3(0.5f,0.5f,-0.5f),
		glm::vec3(-0.5f,0.5f,-0.5f)

};

static glm::vec2 UV[] = {

		glm::vec2(0.f, 0.f),
		glm::vec2(0.f, 1.f),
		glm::vec2(1.f, 1.f),
		glm::vec2(1.f, 1.f),
		glm::vec2(1.f, 0.f),
		glm::vec2(0.f, 0.f)

};

static glm::vec3 NORMALS[] = {

		glm::vec3(0.f, 0.f, 0.f),
		glm::vec3(0.f, 0.f, 0.f),
		glm::vec3(0.f, 0.f, 0.f),
		glm::vec3(0.f, 0.f, 0.f),
		glm::vec3(0.f, 0.f, 0.f),
		glm::vec3(0.f, 0.f, 0.f)

};

static float vertices_for_indices[] = {

		-0.5f,0.5f,-0.5f,
		-0.5f,-0.5f,-0.5f,
		0.5f,-0.5f,-0.5f,
		0.5f,0.5f,-0.5f,

		-0.5f,0.5f,0.5f,
		-0.5f,-0.5f,0.5f,
		0.5f,-0.5f,0.5f,
		0.5f,0.5f,0.5f,

		0.5f,0.5f,-0.5f,
		0.5f,-0.5f,-0.5f,
		0.5f,-0.5f,0.5f,
		0.5f,0.5f,0.5f,

		-0.5f,0.5f,-0.5f,
		-0.5f,-0.5f,-0.5f,
		-0.5f,-0.5f,0.5f,
		-0.5f,0.5f,0.5f,

		-0.5f,0.5f,0.5f,
		-0.5f,0.5f,-0.5f,
		0.5f,0.5f,-0.5f,
		0.5f,0.5f,0.5f,

		-0.5f,-0.5f,0.5f,
		-0.5f,-0.5f,-0.5f,
		0.5f,-0.5f,-0.5f,
		0.5f,-0.5f,0.5f

};

static int indices[] = {

		0,1,3,
		3,1,2,
		4,5,7,
		7,5,6,
		8,9,11,
		11,9,10,
		12,13,15,
		15,13,14,
		16,17,19,
		19,17,18,
		20,21,23,
		23,21,22

};

static float uv[] = {

		0, 0,
		0, 1,
		1, 1,
		1, 0,
		0, 0,
		0, 1,
		1, 1,
		1, 0,
		0, 0,
		0, 1,
		1, 1,
		1, 0,
		0, 0,
		0, 1,
		1, 1,
		1, 0,
		0, 0,
		0, 1,
		1, 1,
		1, 0,
		0, 0,
		0, 1,
		1, 1,
		1, 0

};

#endif // UTIL_H_
