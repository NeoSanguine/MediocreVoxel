#include "Chunk.h"

#include <random>
#include <MediocreEngine/MediocreMath.h>



Chunk::Chunk(glm::ivec3 position)
{
	//m_blocks = std::unordered_map<glm::ivec3, Block*, BlockFunc>();

	// create the blocks
	/*m_blocks = new Block * *[CHUNK_SIZE];
	for (int i = 0; i < CHUNK_SIZE; i++) {

		m_blocks[i] = new Block * [CHUNK_SIZE];

		for (int j = 0; j < CHUNK_SIZE; j++) {
			m_blocks[i][j] = new Block[CHUNK_SIZE];
		}

	}*/

	m_chunkPosition = position;


	// Create the blocks
	m_blocks = new Block **[CHUNK_SIZE];
	for (int i = 0; i < CHUNK_SIZE; i++)
	{
		m_blocks[i] = new Block * [CHUNK_SIZE];

		for (int j = 0; j < CHUNK_SIZE; j++)
		{
			m_blocks[i][j] = new Block[CHUNK_SIZE];
		}
	}
	
	m_setup = true;
	m_loaded = true;
	
	//vao = vao_create();
	//vbo = vbo_create(GL_ARRAY_BUFFER, false);

}

Chunk::~Chunk()
{
	// delete the blocks
	/*for (int i = 0; i < CHUNK_SIZE; ++i) {
		for (int j = 0; j < CHUNK_SIZE; ++j) {
			delete[] m_blocks[i][j];
		}
		delete[] m_blocks[i];
	}

	delete[] m_blocks;*/

	for (int i = 0; i < CHUNK_SIZE; ++i)
	{
		for (int j = 0; j < CHUNK_SIZE; ++j)
		{
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
	/*if (m_loaded) {
		for (int x = 0; x < CHUNK_SIZE; x++) {
			for (int y = 0; y < CHUNK_SIZE; y++) {
				for (int z = 0; z < CHUNK_SIZE; z++) {
					m_blocks[x][y][z].render(program, model);
				}
			}
		}
	}*/

	if (m_loaded) {
		for (int x = 0; x < CHUNK_SIZE; x++) {
			for (int y = 0; y < CHUNK_SIZE; y++) {
				for (int z = 0; z < CHUNK_SIZE; z++) {


					glm::ivec3 renderPosition;
					
					//add the parent chunk position * CHUNK_SIZE  to get the proper location
					renderPosition.x = (m_chunkPosition.x * CHUNK_SIZE) + x;
					renderPosition.y = (m_chunkPosition.y * CHUNK_SIZE) + y;
					renderPosition.z = (m_chunkPosition.z * CHUNK_SIZE) + z;

					m_blocks[x][y][z].render(program, model, renderPosition);
				}
			}
		}
	}
	
	

}

void Chunk::createMesh(int posx, int posy, int posz)
{
	for (int x = 0; x < CHUNK_SIZE; x++) {
		for (int y = 0; y < CHUNK_SIZE; y++) {
			for (int z = 0; z < CHUNK_SIZE; z++) {

				// if the block is not active
				if (m_blocks[x][y][z].isActive() == false) {
					continue;
				}

				createCube(x, y, z,(x + posx * CHUNK_SIZE), (y + posy * CHUNK_SIZE), (z + posz * CHUNK_SIZE));

			}
		}
	}

	/*for (auto& block : m_blocks) {
		if (block.second->isActive() == false) {
			continue;
		}

		// multiply the world position by the chunk size so that the blocks don't appear inside of one another
		createCube(block.first.x, block.first.y, block.first.z,
			(block.first.x + posx * CHUNK_SIZE) , (block.first.y + posy * CHUNK_SIZE) , (block.first.z + posz * CHUNK_SIZE) );
	}*/


}

void Chunk::createCube(int x, int y, int z, int posx, int posy, int posz)
{
	//m_blocks.at(glm::ivec3(x, y, z))->init(glm::vec3(posx, posy, posz), BlockType::GRASS);
	m_blocks[x][y][z].init(glm::ivec3(posx, posy, posz), BlockType::GRASS);
}

bool Chunk::isLoaded()
{
	return m_loaded;
}

void Chunk::load()
{
	m_loaded = true;
}

void Chunk::unload()
{
	m_loaded = false;
}

void Chunk::setAllActive()
{
	/*for (int x = 0; x < CHUNK_SIZE; x++) {
		for (int y = 0; y < CHUNK_SIZE; y++) {
			for (int z = 0; z < CHUNK_SIZE; z++) {

				m_blocks[x][y][z].setActive(true);
			}
		}
	}*/
}

void Chunk::setAllInactive()
{
	/*for (int x = 0; x < CHUNK_SIZE; x++) {
		for (int y = 0; y < CHUNK_SIZE; y++) {
			for (int z = 0; z < CHUNK_SIZE; z++) {

				m_blocks[x][y][z].setActive(false);
			}
		}
	}*/
}

void Chunk::setColorAll(int r, int g, int b)
{
	MediocreEngine::ColorRGBA8 color;

	color.r = r;
	color.g = g;
	color.b = b;
	color.a = 255;

	/*for (auto& block : m_blocks) {

		block.second->setColor(color);
	}*/

	for (int x = 0; x < CHUNK_SIZE; x++) {
		for (int y = 0; y < CHUNK_SIZE; y++) {
			for (int z = 0; z < CHUNK_SIZE; z++) {

				m_blocks[x][y][z].setColor(color);
			}
		}
	}
}

void Chunk::setColorRandom()
{
	int randomR = MediocreEngine::MediocreMath::random(0, 255);
	int randomG = MediocreEngine::MediocreMath::random(0, 255);
	int randomB = MediocreEngine::MediocreMath::random(0, 255);


	MediocreEngine::ColorRGBA8 color;

	color.r = randomR;
	color.g = randomG;
	color.g = randomB;
	color.a = 255;

	for (int x = 0; x < CHUNK_SIZE; x++) {
		for (int y = 0; y < CHUNK_SIZE; y++) {
			for (int z = 0; z < CHUNK_SIZE; z++) {

				m_blocks[x][y][z].setColor(color);
			}
		}
	}

	/*for (auto& block : m_blocks) {
		block.second->setColor(color);
	}*/
}


void Chunk::deleteBlocks()
{
	//delete every block in this chunk
	/*for (auto block : m_blocks) {

		if (block.second == nullptr) {
			continue;
		}

		glm::ivec3 blockLocation = block.first;

		delete m_blocks.at(blockLocation);
		m_blocks.at(blockLocation) = nullptr;
		m_blocks.erase(blockLocation);
	}*/

	
	
	/*for (std::pair<glm::ivec3, Block*> element : m_blocks)
	{
		delete element.second;
		element.second = nullptr;
		m_blocks.erase(element.first);
	}*/

	// Iterator pointing to first element in map
	//std::unordered_map<glm::ivec3, Block*>::iterator it = m_blocks.begin();

	/*while (it != m_blocks.end()) {

		if (it->second != nullptr) {
			delete it->second;
			it->second = nullptr;
			it = m_blocks.erase(it);
		}
		else {
			it++;
		}
		

		
	}*/

	/*std::for_each(m_blocks.begin(), m_blocks.end(), [](std::pair<glm::ivec3, Block* > element) {
		delete element.second;
		element.second = nullptr;
		});

	m_blocks.clear();*/

	for (int x = 0; x < CHUNK_SIZE; x++) {
		for (int y = 0; y < CHUNK_SIZE; y++) {
			for (int z = 0; z < CHUNK_SIZE; z++) {

				m_blocks[x][y][z].erase();
			}
		}
	}

}

void Chunk::deleteBlock(int x, int y, int z)
{
	/*glm::ivec3 blockLocation = glm::ivec3(x, y, z);

	if (blockExist(blockLocation)) {
		
		delete m_blocks.at(blockLocation);
		m_blocks.at(blockLocation) = nullptr;
		m_blocks.erase(blockLocation);

	}*/


	m_blocks[x][y][z].erase();

}

void Chunk::deleteBlock(glm::ivec3 blockLocation)
{

	// check if the block is visible
	if (m_blocks[blockLocation.x][blockLocation.y][blockLocation.z].isActive())
	{
		m_blocks[blockLocation.x][blockLocation.y][blockLocation.z].erase();
	}

	/*if (blockExist(blockLocation)) {

		//delete m_blocks.at(blockLocation);
		//m_blocks.at(blockLocation) = nullptr;
		//m_blocks.erase(blockLocation);

		m_blocks[blockLocation.x][blockLocation.y][blockLocation.z] = NULL;

	}*/
}

bool Chunk::blockExist(int x, int y, int z)
{
	//auto block = m_blocks.find(glm::ivec3(x, y, z));

	if (m_blocks[x][y] == nullptr) {
		return false;
	}

	return true;
}

bool Chunk::blockExist(glm::ivec3 blockLocation)
{
	if (m_blocks[blockLocation.x][blockLocation.y] == nullptr) {
		return false;
	}

	return true;
}

bool Chunk::isEmpty()
{
	bool empty = true;

	for (int x = 0; x < CHUNK_SIZE; x++) {
		for (int y = 0; y < CHUNK_SIZE; y++) {
			for (int z = 0; z < CHUNK_SIZE; z++) {

				if (m_blocks[x][y][z].isActive()) {
					empty = false;
				}
			}
		}
	}

	return empty;
}

glm::ivec3 Chunk::getChunkPosition()
{
	return m_chunkPosition;
}

