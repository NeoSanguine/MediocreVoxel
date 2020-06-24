#include "Chunk.h"

#include <random>
#include <MediocreEngine/MediocreMath.h>
#include <iostream>
#include "Util.h"

float vertices[] = {
		-0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,

		-0.5f, -0.5f,  0.5f,
		 0.5f, -0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f,

		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,

		 0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,

		-0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f,  0.5f,
		 0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f, -0.5f,

		-0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f,
};


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

	m_vao = vao_create();
	m_vbo = vbo_create(GL_ARRAY_BUFFER, false);

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

	//std::cout << "chunk destructor " << std::endl;

	for (int i = 0; i < CHUNK_SIZE; ++i)
	{
		for (int j = 0; j < CHUNK_SIZE; ++j)
		{
			delete[] m_blocks[i][j];
		}

		delete[] m_blocks[i];
	}
	delete[] m_blocks;

	vao_destroy(m_vao);
	vbo_destroy(m_vbo);

}

void Chunk::update(float deltaTime)
{

	if (m_ShouldRebuild) {
		//rebuildChunk();

		m_ShouldRebuild = false;
	}

}

void Chunk::render(MediocreEngine::GLSLProgram program, glm::mat4 model)
{

	if (m_loaded) {

		vao_bind(m_vao);

		for (int x = 0; x < CHUNK_SIZE; x++) {
			for (int y = 0; y < CHUNK_SIZE; y++) {
				for (int z = 0; z < CHUNK_SIZE; z++) {

					if (m_blocks[x][y][z].isActive()) {
						glm::ivec3 renderPosition;

						//add the parent chunk position * CHUNK_SIZE  to get the proper location
						renderPosition.x = (m_chunkPosition.x * CHUNK_SIZE) + x;
						renderPosition.y = (m_chunkPosition.y * CHUNK_SIZE) + y;
						renderPosition.z = (m_chunkPosition.z * CHUNK_SIZE) + z;

						m_blocks[x][y][z].render(program, model, renderPosition);

						glDrawArrays(GL_TRIANGLES, 0, 36);
					}

					
				}
			}
		}

		

		vao_unbind();
	}
	
	

}

void Chunk::createMesh()
{
	// build the mesh in a way where we throw away the vertices that aren't in view of the CHUNK
	for (int x = 0; x < CHUNK_SIZE; x++) {
		for (int y = 0; y < CHUNK_SIZE; y++) {
			for (int z = 0; z < CHUNK_SIZE; z++) {

				Block* block = &m_blocks[x][y][z];

				bool px = false; // positive x
				bool nx = false; // negative x
				bool py = false; // positive y
				bool ny = false; // negative y
				bool pz = false; // positive z
				bool nz = false; // negative z

				//PX
				if (x < CHUNK_SIZE - 1) {
					if (block->isActive() == m_blocks[x + 1][y][z].isActive()) {
						px = true;
					}
				}


				//NX
				if (x > 0) {
					if (block->isActive() == m_blocks[x - 1][y][z].isActive()) {
						nx = true;
					}
				}

				//PY
				if (y < CHUNK_SIZE - 1) {
					if (block->isActive() == m_blocks[x][y + 1][z].isActive()) {
						py = true;
					}
				}


				//NY
				if (y > 0) {
					if (block->isActive() == m_blocks[x][y - 1][z].isActive()) {
						ny = true;
					}
				}

				//PZ
				if (z < CHUNK_SIZE - 1) {
					if (block->isActive() == m_blocks[x][y][z + 1].isActive()) {
						pz = true;
					}
				}


				//NZ
				if (z > 0) {
					if (block->isActive() == m_blocks[x][y][z - 1].isActive()) {
						nz = true;
					}
				}

				// add visible faces to the chunk mesh
				if (px && py && pz && nx && ny && nz) {
					block->setActive(false);
					//block->setColor(MediocreEngine::ColorRGBA8(255, 0, 0));
				}		
				else if (x == 0 || y == 0 || z == 0 || x == CHUNK_SIZE-1 || y == CHUNK_SIZE - 1 || z == CHUNK_SIZE - 1) {
					//block->setColor(MediocreEngine::ColorRGBA8(0, 255, 0));
				}
				else {
					block->setActive(false);
					//block->setColor(MediocreEngine::ColorRGBA8(0, 0, 255));
				}
				






			}
		}
	}


	//  then bind and set vertex buffer(s), and then configure vertex attributes(s).
	vao_bind(m_vao);

	vbo_bind(m_vbo);

	vbo_buffer(m_vbo, vertices, 0, sizeof(vertices));

	vao_attribute(m_vao, m_vbo, 0, 3, GL_FLOAT, 3 * sizeof(float), 0);

	vbo_unbind(m_vbo);

	vao_unbind();

}


void Chunk::recreateMesh()
{
	// clear the vbo

	//vao_destroy(m_vao);
	vbo_destroy(m_vbo);

	//m_vao = vao_create();
	m_vbo = vbo_create(GL_ARRAY_BUFFER, false);

	createMesh();
}

void Chunk::initBlocks(int x, int y, int z)
{
	for (int x = 0; x < CHUNK_SIZE; x++) {
		for (int y = 0; y < CHUNK_SIZE; y++) {
			for (int z = 0; z < CHUNK_SIZE; z++) {
				m_blocks[x][y][z].init(BlockType::GRASS);
			}
		}
	}
	
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
	for (int x = 0; x < CHUNK_SIZE; x++) {
		for (int y = 0; y < CHUNK_SIZE; y++) {
			for (int z = 0; z < CHUNK_SIZE; z++) {

				m_blocks[x][y][z].setActive(true);
			}
		}
	}

	m_ShouldRebuild = true;
}

void Chunk::setAllInactive()
{
	for (int x = 0; x < CHUNK_SIZE; x++) {
		for (int y = 0; y < CHUNK_SIZE; y++) {
			for (int z = 0; z < CHUNK_SIZE; z++) {

				m_blocks[x][y][z].setActive(false);
			}
		}
	}

	m_ShouldRebuild = true;
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
	for (int x = 0; x < CHUNK_SIZE; x++) {
		for (int y = 0; y < CHUNK_SIZE; y++) {
			for (int z = 0; z < CHUNK_SIZE; z++) {

				m_blocks[x][y][z].erase();
			}
		}
	}

	m_ShouldRebuild = false;
}

void Chunk::deleteBlock(int x, int y, int z)
{
	m_blocks[x][y][z].erase();

	m_ShouldRebuild = true;

}

void Chunk::deleteBlock(glm::ivec3 blockLocation)
{

	// check if the block is visible
	m_blocks[blockLocation.x][blockLocation.y][blockLocation.z].erase();
	// now we want to rebuild the chunk and ignore any inactive 
	m_ShouldRebuild = true;
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

// loop through all of the blocks, and if the block on the outer most layer is active,
// set everything inside to inactive, as we can't see the block anyways
void Chunk::updateMeshVisibility()
{
	for (int x = 0; x < CHUNK_SIZE; x++) {
		for (int y = 0; y < CHUNK_SIZE; y++) {
			for (int z = 0; z < CHUNK_SIZE; z++) {

				/*if (x != 0 && x != (CHUNK_SIZE - 1) &&
					y != 0 && y != (CHUNK_SIZE - 1) &&
					z != 0 && z != (CHUNK_SIZE - 1)) {
					m_blocks[x][y][z].setActive(false);
				}*/

				// get the blocks on the outer most rim

				// X FACE
				if (x != (CHUNK_SIZE - 1) &&
					y != (CHUNK_SIZE - 1) &&
					z != (CHUNK_SIZE - 1)) {

					m_blocks[x][y][z].setActive(false);

				}

			}
		}
	}

	m_ShouldRebuild = true;
}

bool Chunk::isEmpty()
{
	// if any block we find is active, return false;
	for (int x = 0; x < CHUNK_SIZE; x++) {
		for (int y = 0; y < CHUNK_SIZE; y++) {
			for (int z = 0; z < CHUNK_SIZE; z++) {

				if (m_blocks[x][y][z].isActive()) {
					return false;
				}
			}
		}
	}

	return true;
}

glm::ivec3 Chunk::getChunkPosition()	
{
	return m_chunkPosition;
}

void Chunk::rebuildChunk()
{
	//std::cout << "recreating mesh" << std::endl;
	recreateMesh();
}

