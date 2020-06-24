#pragma once

#include "Block.h"
#include <unordered_map>

#include "VAO.h"
#include "VBO.h"
#include "Vertex3D.h"

const static int CHUNK_SIZE = 16;

class Chunk {

public:

	Chunk(glm::ivec3 postion);
	~Chunk();

	void update(float deltaTime);

	void render(MediocreEngine::GLSLProgram program, glm::mat4 model);

	void createMesh();
	void recreateMesh();

	void initBlocks(int x, int y, int z);

	bool isLoaded();

	void load();

	void unload();
 

	void setAllActive();
	void setAllInactive();
	void setColorAll(int r, int g, int b);
	void setColorRandom();

	void deleteBlocks();
	void deleteBlock(int x, int y, int z);
	void deleteBlock(glm::ivec3 blockPosition);

	bool blockExist(int x, int y, int z);
	bool blockExist(glm::ivec3 blockLocation);

	void updateMeshVisibility();

	bool isEmpty();

	// block data
	Block*** m_blocks;
	//std::unordered_map<glm::ivec3, Block*, BlockFunc> m_blocks;

	glm::ivec3 getChunkPosition();

private:

	void rebuildChunk();

	glm::ivec3 m_chunkPosition;
	bool m_loaded = false;
	bool m_setup = false;
	bool m_ShouldRebuild = false;

	struct VBO m_vbo;
	struct VAO m_vao;
	struct VBO m_ibo;

	std::vector<Vertex3D>m_vertices;

};