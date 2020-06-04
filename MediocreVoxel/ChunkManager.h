#pragma once

#include <glm.hpp>
#include <vector>
#include <map>
#include <unordered_map>
#include "Chunk.h"

const int NUM_CHUNKS_PER_FRAME = 4;

const int MIN_CHUNKS_X = -10;
const int MIN_CHUNKS_Y = 0;
const int MIN_CHUNKS_Z = -10;

const int MAX_CHUNKS_X = 10;
const int MAX_CHUNKS_Y = 1;
const int MAX_CHUNKS_Z = 10;

struct ChunkFunc
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

class ChunkManager {

public:
	ChunkManager();

	void init();
	void update(float deltaTime, glm::vec3 cameraPosition, glm::mat4 cameraView);
	void render(MediocreEngine::GLSLProgram program, glm::mat4 model);

	void createChunk(int x, int y, int z, bool partyColor = false);

	bool chunkExist(int x, int y, int z);


private:

	glm::vec3 m_cameraPosition;
	glm::mat4 m_cameraView;

	std::unordered_map<glm::ivec3, Chunk*, ChunkFunc> m_chunks;

	std::vector<Chunk*> m_chunkList;
	std::vector<Chunk*> m_loadChunkList;

	bool m_forceVisibilityUpdate = false;

	int numChunks = 2;

};