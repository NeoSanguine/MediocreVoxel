#include "Chunk.h"

#include <random>
#include <MediocreEngine/MediocreMath.h>

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
	
	m_setup = true;
	m_loaded = true;
	
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
	if (m_loaded) {
		for (int x = 0; x < CHUNK_SIZE; x++) {
			for (int y = 0; y < CHUNK_SIZE; y++) {
				for (int z = 0; z < CHUNK_SIZE; z++) {
					m_blocks[x][y][z].render(program, model);
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

				createCube(x, y, z, x + posx, y + posy, z + posz);

			}
		}
	}
}

void Chunk::createCube(int x, int y, int z, int posx, int posy, int posz)
{
	m_blocks[x][y][z].init(glm::vec3(posx, posy, posz), BlockType::GRASS);
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
}

void Chunk::setColorAll(int r, int g, int b)
{
	MediocreEngine::ColorRGBA8 color;

	color.r = r;
	color.g = g;
	color.b = b;
	color.a = 255;

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
}
