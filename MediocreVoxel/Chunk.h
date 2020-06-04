#pragma once

#include "Block.h"

const static int CHUNK_SIZE = 1;

class Chunk {

public:

	

	Chunk();
	~Chunk();

	void update(float deltaTime);

	void render(MediocreEngine::GLSLProgram program, glm::mat4 model);

	

	void createMesh(int x, int y, int z);

	void createCube(int x, int y, int z, int posx, int posy, int posz);

	bool isLoaded();

	void load();

	void unload();

	void setAllActive();
	void setAllInactive();
	void setColorAll(int r, int g, int b);
	void setColorRandom();

private:
	// block data
	Block*** m_blocks;
	unsigned int VBO = 0;
	unsigned int VAO = 0;
	bool m_loaded = false;
	bool m_setup = false;

};