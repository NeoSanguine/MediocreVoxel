#pragma once

#include "Block.h"
#include <unordered_map>

#include "VAO.h"
#include "VBO.h"

const static int CHUNK_SIZE = 3;

struct BlockFunc
{
	size_t operator()(const glm::ivec3& k)const
	{
		return std::hash<int>()(k.x) ^ std::hash<int>()(k.y) ^ std::hash<int>()(k.z);
	}

	bool operator()(const glm::ivec3& a, const glm::ivec3& b, const glm::ivec3& c)const
	{
		return a.x == b.x && a.y == b.y && a.z == b.z;
	}
};

class Chunk {

public:

	

	Chunk(glm::ivec3 postion);
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

	void deleteBlocks();
	void deleteBlock(int x, int y, int z);
	void deleteBlock(glm::ivec3 blockPosition);

	bool blockExist(int x, int y, int z);
	bool blockExist(glm::ivec3 blockLocation);

	bool isEmpty();

	// block data
	Block*** m_blocks;
	//std::unordered_map<glm::ivec3, Block*, BlockFunc> m_blocks;

	glm::ivec3 getChunkPosition();

private:
	glm::ivec3 m_chunkPosition;
	bool m_loaded = false;
	bool m_setup = false;

};