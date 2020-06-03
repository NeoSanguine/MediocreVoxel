#pragma once

#include "Block.h"

class Chunk {

public:
	Chunk();
	~Chunk();

	void update(float deltaTime);

	void render(MediocreEngine::GLSLProgram program, glm::mat4 model);

	const static int CHUNK_SIZE = 4;

	void createMesh();

	void createCube(int x, int y, int z);

private:
	// block data
	Block*** m_blocks;
	unsigned int VBO = 0;
	unsigned int VAO = 0;


};