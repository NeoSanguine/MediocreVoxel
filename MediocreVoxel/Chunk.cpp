#include "Chunk.h"

Chunk::Chunk()
{
	// create the blocks
	m_blocks = new Block * *[CHUNK_SIZE];
	for (int i = 0; i < CHUNK_SIZE; i++) {

		m_blocks[i] = new Block * [CHUNK_SIZE];

		for (int j = 0; j < CHUNK_SIZE; j++) {
			m_blocks[i][j] = new Block[CHUNK_SIZE];
		}

	}

	createMesh();
}

Chunk::~Chunk()
{
	// delete the blocks
	for (int i = 0; i < CHUNK_SIZE; ++i) {
		for (int j = 0; j < CHUNK_SIZE; ++j) {
			delete[] m_blocks[i][j];
		}
		delete[] m_blocks[i];
	}

	delete[] m_blocks;
}

void Chunk::update(float deltaTime)
{
}

void Chunk::render(MediocreEngine::GLSLProgram program, glm::mat4 model)
{
	for (int x = 0; x < CHUNK_SIZE; x++) {
		for (int y = 0; y < CHUNK_SIZE; y++) {
			for (int z = 0; z < CHUNK_SIZE; z++) {
				m_blocks[x][y][z].render(program, model);
			}
		}
	}


}

void Chunk::createMesh()
{
	for (int x = 0; x < CHUNK_SIZE; x++) {
		for (int y = 0; y < CHUNK_SIZE; y++) {
			for (int z = 0; z < CHUNK_SIZE; z++) {

				// if the block is not active
				if (m_blocks[x][y][z].isActive() == false) {
					continue;
				}

				createCube( x,  y,  z);

			}
		}
	}
}

void Chunk::createCube(int x, int y, int z)
{
	m_blocks[x][y][z].init(glm::vec3(x, y, z), BlockType::GRASS);
}
