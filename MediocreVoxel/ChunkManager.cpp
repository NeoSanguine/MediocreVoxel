#include "ChunkManager.h"
#include <iostream>
#include <MediocreEngine/InputManager.h>
#include <SDL.h>

ChunkManager::ChunkManager()
{
	//m_chunks = std::unordered_map<glm::ivec3, Chunk*,ChunkFunc>();
}

void ChunkManager::init()
{

	/*for (int x = 0; x < MAX_CHUNKS_X; x++) {
		for (int y = 0; y < MAX_CHUNKS_Y; y++) {
			for (int z = 0; z < MAX_CHUNKS_Z; z++) {


				m_chunks.insert(std::make_pair(glm::ivec3(x, y, z), new Chunk(glm::ivec3(x,y,z))));

				m_chunks.at(glm::ivec3(x, y, z))->createMesh(x,y,z);

				//m_chunks.at(glm::ivec3(x, y, z))->updateMeshVisibility();

				m_chunks.at(glm::ivec3(x, y, z))->setColorRandom();
			}
		}
	}*/

	//glm::ivec3 chunk1 = glm::ivec3(0, 0, 0);

	createChunk(0, 0, 0, false);
	//createChunk(1, 0, 1, true);

}

void ChunkManager::handleEvents()
{

	if (MediocreEngine::InputManager::get().isKeyPressed(SDLK_e)) {

		std::cout << "Num Chunks: " << m_chunks.size() << std::endl;
		for (auto& chunk : m_chunks) {

			if (chunk.second != nullptr) {

				for (int x = 0; x < CHUNK_SIZE; x++) {
					for (int y = 0; y < CHUNK_SIZE; y++) {
						for (int z = 0; z < CHUNK_SIZE; z++) {


							//chunk.second->m_blocks[x][y][z].setActive(true);

							if (x == 0 && y == 0 && z == 0) {
								//std::cout << "erasing block" << std::endl;
								//chunk.second->deleteBlock(glm::ivec3(x, y, z));
								
								//delete chunk.second->m_blocks[x][y];
								//chunk.second->m_blocks[x][y] = nullptr;
							}
							

						}
					}
				}

				

			}
		}


		
	}

	if (MediocreEngine::InputManager::get().isKeyPressed(SDLK_q)) {

		std::cout << "Num Blocks: " << getNumBlocks() << std::endl;

	}

}

void ChunkManager::update(float deltaTime, glm::vec3 cameraPosition, glm::mat4 cameraView)
{

	// update chunks
	for (auto chunk : m_chunks) {

		if (chunk.second != nullptr) {

			chunk.second->update(deltaTime);
		}


	}

	if (m_cameraPosition != cameraPosition || m_cameraView != cameraView) {

		// create a chunk in the direction that the player is moving towards
		/*for (int x = 0; x < (int)cameraPosition.x + 10; x++) {
			for (int z = (int)(cameraPosition.z - 10); z < (int)cameraPosition.z; z++) {
				if (!chunkExist(x, 0, z)) {
					createChunk(x, 0, z, true);
				}
			}
		}*/
		
	}

	

	/*
	for (auto& chunk : m_chunks) {

		if (chunk.second != nullptr) {

			if (chunk.second->isEmpty()) {
				continue;
			}

			for (int x = 0; x < CHUNK_SIZE; x++) {
				for (int y = 0; y < CHUNK_SIZE; y++) {
					for (int z = 0; z < CHUNK_SIZE; z++) {


						glm::ivec3 blockPosition;
						glm::ivec3 worldPosition;

						glm::ivec3 chunkPosition = chunk.second->getChunkPosition();

						worldPosition.x = (chunkPosition.x * CHUNK_SIZE) + x;
						worldPosition.y = (chunkPosition.y * CHUNK_SIZE) + y;
						worldPosition.z = (chunkPosition.z * CHUNK_SIZE) + z;

						int distX = (int)(cameraPosition.x - worldPosition.x);
						int distY = (int)(cameraPosition.y - worldPosition.y);
						int distZ = (int)(cameraPosition.z - worldPosition.z);

						if (distX < 0) {
							distX = -distX;
						}

						if (distY < 0) {
							distY = -distY;
						}

						if (distZ < 0) {
							distZ = -distZ;
						}

						//std::cout << dist << std::endl;
						

						if (distX > 10 || distZ > 10) {
							//m_blockRemovalList.insert(std::pair<glm::ivec3, Block*>(glm::ivec3(x,y,z), block.second));
							//chunk.second->deleteBlock(glm::ivec3(x, y, z));
							//chunk.second->m_blocks[x][y][z].setActive(false);
							//std::cout << "world position: " << worldPosition.x << " " << worldPosition.y << " " << worldPosition.z << std::endl;
							//std::cout << "trying to remove block at: " << x << " " << y << " " << z << std::endl;
							m_chunkRemovalList.push_back(chunk.first);
						}

					}
				}
			}



		}
	}
	*/
	m_cameraPosition = cameraPosition;
	m_cameraView = cameraView;

	
	updateBlockRemovalList();
	updateChunkRemovalList();
	//clearEmptyChunks();
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
	m_chunks.insert(std::make_pair(glm::ivec3(x,y,z), new Chunk(glm::ivec3(x, y, z))));
	m_chunks.at(glm::ivec3(x, y, z))->createMesh();

	if (partyColor) {
		m_chunks.at(glm::ivec3(x, y, z))->setColorRandom();
	}
	
}


bool ChunkManager::chunkExist(int x, int y, int z)
{
	return m_chunks.find(glm::ivec3(x, y, z)) != m_chunks.end();
}

bool ChunkManager::chunkExist(glm::ivec3 chunkLocation)
{
	return m_chunks.find(chunkLocation) != m_chunks.end();
}

void ChunkManager::deleteChunk(int x, int y, int z)
{
	glm::ivec3 chunkLocation = glm::ivec3(x, y, z);

	// for every block in the chunk, delete it
	m_chunks.at(chunkLocation)->deleteBlocks();

	delete m_chunks.at(chunkLocation);
	m_chunks.at(chunkLocation) = nullptr;

	m_chunks.erase(chunkLocation);
}

void ChunkManager::deleteChunk(glm::ivec3 chunkLocation)
{
	
	// for every block in the chunk, delete it
	m_chunks.at(chunkLocation)->deleteBlocks();


	delete m_chunks.at(chunkLocation);
	m_chunks.at(chunkLocation) = nullptr;

	m_chunks.erase(chunkLocation);
}

bool ChunkManager::hasNeighbors(glm::ivec3 chunkPosition)
{
	const auto& cp = chunkPosition;
	return chunkExist(chunkPosition) &&
		// Top
		chunkExist({ cp.x, cp.y + 1, cp.z }) &&
		// Bottom
		chunkExist({ cp.x, cp.y - 1, cp.z }) &&
		// Left
		chunkExist({ cp.x - 1, cp.y, cp.z }) &&
		// Right
		chunkExist({ cp.x + 1, cp.y, cp.z }) &&
		// Front
		chunkExist({ cp.x, cp.y, cp.z - 1 }) &&
		// Back
		chunkExist({ cp.x, cp.y, cp.z + 1 });
}

int ChunkManager::getNumBlocks()
{
	int counter = 0;
	for (auto& chunk : m_chunks) {
		
		for (size_t x = 0; x < CHUNK_SIZE; x++) {
			for (size_t y = 0; y < CHUNK_SIZE; y++) {
				for (size_t z = 0; z < CHUNK_SIZE; z++) {

					if (chunk.second->m_blocks[x][y][z].isActive()) {
						counter++;
					}

				}
			}
		}

	}

	return counter;
}

void ChunkManager::updateBlockRemovalList()
{

	for (auto& data : m_blockRemovalList) {

		m_chunks.at(data.chunkLocation)->deleteBlock(data.blockLocation);
	}


	m_blockRemovalList.clear();
	
}

void ChunkManager::updateChunkRemovalList()
{
	for (auto& removalChunk : m_chunkRemovalList) {

		deleteChunk(removalChunk);
	}


	m_chunkRemovalList.clear();
}

void ChunkManager::clearEmptyChunks()
{
	// if the chunk is empty, delete it

	for (auto& chunk : m_chunks) {
		if (chunk.second->isEmpty()) {
			//deleteChunk(chunk.first);
			m_chunkRemovalList.push_back(chunk.first);
			//std::cout << "Removing Empty Chunk at X:" << chunk.first.x << " Y: " << chunk.first.y << " Z: " << chunk.first.z << std::endl;
		}
	}
}

