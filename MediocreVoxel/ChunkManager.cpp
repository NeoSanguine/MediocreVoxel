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

	for (int x = 0; x < MAX_CHUNKS_X; x++) {
		for (int y = 0; y < MAX_CHUNKS_Y; y++) {
			for (int z = 0; z < MAX_CHUNKS_Z; z++) {


				m_chunks.insert(std::make_pair(glm::ivec3(x, y, z), new Chunk()));

				m_chunks.at(glm::ivec3(x, y, z))->createMesh(x,y,z);

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

void ChunkManager::handleEvents()
{

	if (MediocreEngine::InputManager::get().isKeyPressed(SDLK_e)) {

		std::cout << "Num Chunks: " << m_chunks.size() << std::endl;
		for (auto& chunk : m_chunks) {

			if (chunk.second != nullptr) {

				for (int x = 0; x < CHUNK_SIZE; x++) {
					for (int y = 0; y < CHUNK_SIZE; y++) {
						for (int z = 0; z < CHUNK_SIZE; z++) {


							if (x == 0 && y == 0 && z == 0) {
								//std::cout << "erasing block" << std::endl;
								//chunk.second->m_blocks[x][y][z].erase();
								//delete chunk.second->m_blocks[x][y];
								//chunk.second->m_blocks[x][y] = nullptr;
							}
							

						}
					}
				}

				

			}
		}


		
	}

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
		for (int x = (int)cameraPosition.x; x < (int)cameraPosition.x + 10; x++) {
			for (int z = (int)cameraPosition.z - 10; z < (int)cameraPosition.z; z++) {
				if (!chunkExist(x , 0, z)) {
					createChunk(x, 0, z, true);
				}
			}
		}

		
	}

	for (auto& chunk : m_chunks) {

		if (chunk.second != nullptr) {

			for (int x = 0; x < CHUNK_SIZE; x++) {
				for (int y = 0; y < CHUNK_SIZE; y++) {
					for (int z = 0; z < CHUNK_SIZE; z++) {


						glm::ivec3 blockPosition;
						glm::ivec3 worldPositon = chunk.second->m_blocks[x][y][z].getPosition();

						blockPosition.x = (worldPositon.x / CHUNK_SIZE);
						blockPosition.y = (worldPositon.y / CHUNK_SIZE);
						blockPosition.z = (worldPositon.z / CHUNK_SIZE);

						int distX = (int)(cameraPosition.x - blockPosition.x);
						int distZ = (int)(cameraPosition.z - blockPosition.z);

						if (distX < 0) {
							distX = -distX;
						}

						if (distZ < 0) {
							distZ = -distZ;
						}

						

						if (distX > 20 || distZ > 20) {
							//chunk.second->m_blocks[x][y][z].erase();
							//std::cout << m_chunkRemovalList.size() << std::endl;
							//m_chunkRemovalList.push_back(glm::ivec3(x, y, z));
							//m_blockRemovalList.insert(std::pair<glm::ivec3, Block*>(glm::ivec3(x,y,z), block.second));

							m_chunkRemovalList.push_back(chunk.first);
							//m_blockRemovalList.push_back(BlockRemovalData(chunk.first, glm::ivec3(x, y, z)));
						}

					}
				}
			}



		}
	}

	/*
	glm::ivec3 blockPosition;
					glm::ivec3 worldPositon = block.second->getPosition();

					blockPosition.x = (worldPositon.x / CHUNK_SIZE);
					blockPosition.y = (worldPositon.y / CHUNK_SIZE);
					blockPosition.z = (worldPositon.z / CHUNK_SIZE);

					int distX = (int)(cameraPosition.x - blockPosition.x);
					int distZ = (int)(cameraPosition.z - blockPosition.z);

					if (distX < 0) {
						distX = -distX;
					}

					if (distZ < 0) {
						distZ = -distZ;
					}

					std::cout << distZ << std::endl;

					if (distX > 10 || distZ > 10) {
						m_blockRemovalList.insert(std::pair<glm::ivec3, Block*>(blockPosition, block.second));
					}*/


	m_cameraPosition = cameraPosition;
	m_cameraView = cameraView;

	
	updateBlockRemovalList();
	updateChunkRemovalList();
	clearEmptyChunks();
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
	m_chunks.at(glm::ivec3(x, y, z))->createMesh(x, y, z);

	if (partyColor) {
		m_chunks.at(glm::ivec3(x, y, z))->setColorRandom();
	}
	
}

bool ChunkManager::chunkExist(int x, int y, int z)
{
	auto chunk = m_chunks.find(glm::ivec3(x, y, z));

	if (chunk == m_chunks.end()) {
		return false;
	}
	
	return true;
}

bool ChunkManager::chunkExist(glm::ivec3 chunkLocation)
{
	auto chunk = m_chunks.find(chunkLocation);

	if (chunk == m_chunks.end()) {
		return false;
	}

	return true;
}

void ChunkManager::deleteChunk(int x, int y, int z)
{
	glm::ivec3 chunkLocation = glm::ivec3(x, y, z);

	// for every block in the chunk, delete it
	//m_chunks.at(chunkLocation)->deleteBlocks();

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

		if (chunkExist(removalChunk)) {

			//std::cout << "Chunk exist and is being deleted: X: " + chunkPosition.x << " Y: " << chunkPosition.y << " Z: " << chunkPosition.z << std::endl;
			deleteChunk(removalChunk);
		}
		else {
			//std::cout << "ERROR: TRYING TO DELETE A CHUNK THAT DOES NOT EXIST" << std::endl;
		}
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

