#include "ChunkManager.h"

ChunkManager::ChunkManager()
{
	m_chunks = std::unordered_map<glm::ivec3, Chunk*,ChunkFunc>();
}

void ChunkManager::init()
{

	for (int x = 0; x < MAX_CHUNKS_X; x++) {
		for (int y = 0; y < MAX_CHUNKS_Y; y++) {
			for (int z = MIN_CHUNKS_Z; z < MAX_CHUNKS_Z; z++) {
				m_chunks.insert(std::make_pair(glm::ivec3(x, y, z), new Chunk()));

				m_chunks.at(glm::ivec3(x, y, z))->createMesh(x * CHUNK_SIZE, y * CHUNK_SIZE, z * CHUNK_SIZE);

				m_chunks.at(glm::ivec3(x, y, z))->setColorRandom();
			}
		}
	}
	

	/*for (auto chunk : m_chunks) {

		if (chunk.second != nullptr) {

			//todo check if the chunk is visible

			chunk.second->createMesh(chunk.first.x * chunk.second->CHUNK_SIZE,
				chunk.first.y * chunk.second->CHUNK_SIZE,
				chunk.first.z * chunk.second->CHUNK_SIZE);
		}


	}*/

	
	//m_chunks.at(glm::ivec3(1, 0, 0))->setColorRandom();
	//m_chunks.at(glm::ivec3(2, 0, 0))->setColorRandom();

	//m_chunks.at(glm::ivec3(3, 0, 0))->setColorRandom();
	//m_chunks.at(glm::ivec3(4, 0, 0))->setColorRandom();
	//m_chunks.at(glm::ivec3(5, 0, 0))->setColorRandom();

}

void ChunkManager::update(float deltaTime, glm::vec3 cameraPosition, glm::mat4 cameraView)
{

	// update chunks
	for (auto chunk : m_chunks) {

		if (chunk.second != nullptr) {

			//todo check if the chunk is visible

			chunk.second->update(deltaTime);
		}


	}

	if (m_cameraPosition != cameraPosition || m_cameraView != cameraView) {

		// create a chunk in the direction that the player is moving towards
		for (int x = (int)cameraPosition.x - 10; x < cameraPosition.x + 10; x++) {
			for (int z = -10; z < 10; z++) {
				if (!chunkExist(x, 0, z)) {
					createChunk(x, 0, z, false);
				}
				
				
			}
		}
	}

	m_cameraPosition = cameraPosition;
	m_cameraView = cameraView;

}

void ChunkManager::render(MediocreEngine::GLSLProgram program, glm::mat4 model)
{
	for (auto chunk : m_chunks) {

		if (chunk.second != nullptr) {

			//todo check if the chunk is visible

			chunk.second->render(program, model);
		}

		
	}
}

void ChunkManager::createChunk(int x, int y, int z, bool partyColor /*= false*/)
{
	m_chunks.insert(std::make_pair(glm::ivec3(x, y, z), new Chunk()));
	m_chunks.at(glm::ivec3(x, y, z))->createMesh(x * CHUNK_SIZE, y * CHUNK_SIZE, z * CHUNK_SIZE);

	if (partyColor) {
		m_chunks.at(glm::ivec3(x, y, z))->setColorRandom();
	}
	
}

bool ChunkManager::chunkExist(int x, int y, int z)
{
	auto chunk = m_chunks.find(glm::ivec3(x, y, z))->second;

	if (chunk == nullptr) {
		return false;
	}
	
	return true;
}

