#include "GameScreen.h"
#include <iostream>
#include <SDL.h>
#include <MediocreEngine\IGame.h>
#include <MediocreEngine\ResourceManager.h>
#include <random>
#include <GL\glew.h>
#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc/type_ptr.hpp>


namespace
{
	//Block* m_pBlocks[32][32][32]
}


namespace
{
	std::mt19937 randGenerator;
}

GameScreen::GameScreen(MediocreEngine::Window* window) : m_window(window)
{

}

GameScreen::~GameScreen()
{

}

int GameScreen::getNextScreenIndex() const
{
	return 0;
}

int GameScreen::getPreviousScreenIndex() const
{
	return 0;
}

void GameScreen::build()
{

}

void GameScreen::destroy()
{

}

void GameScreen::onEnter()
{
	m_textureProgram.compileShaders("bin/shaders/textureShading.vert", "bin/shaders/textureShading.frag");
	m_textureProgram.addAttribute("vertexPosition");
	m_textureProgram.addAttribute("vertexColor");
	m_textureProgram.addAttribute("vertexUV");
	m_textureProgram.linkShaders();

	

	
	//
	

	m_model = glm::mat4(1.0f);
	m_view = glm::mat4(1.0f);
	m_proj = glm::mat4(1.0f);

	isWireframe = false;


	for (int x = 0; x < 16; x++)
	{
		for (int y = 0; y < 16; y++)
		{
			for (int z = 0; z < 16; z++)
			{
				m_blocks[x][y][z] = new Block();
				m_blocks[x][y][z]->init(glm::vec3(x, y, z));
				// Render m_pBlocks[x][y][z]
			}
		}
	}

	
}

void GameScreen::onExit()
{
	
	m_textureProgram.dispose();
}
void GameScreen::handleInput()
{
	auto input = MediocreEngine::InputManager::get();

	if (input.isKeyDown(SDLK_w)) {

		// move forward
		m_view = glm::translate(m_view, glm::vec3(0.0f, -0.1f, 0.0f));
	}

	if (input.isKeyDown(SDLK_d)) {
		// move right
		m_view = glm::translate(m_view, glm::vec3(-0.1f, 0.0f, 0.0f));
	}

	if (input.isKeyDown(SDLK_a)) {
		// move right
		m_view = glm::translate(m_view, glm::vec3(0.1f, 0.0f, 0.0f));
		
	}

	if (input.isKeyDown(SDLK_s)) {
		// move right
		m_view = glm::translate(m_view, glm::vec3(0.0f, 0.1f, 0.0f));
	}

	if (input.isKeyDown(SDLK_q)) {
		// move right
		m_model = glm::rotate(m_model, glm::radians(-1.0f), glm::vec3(1.0f, 1.0f, 1.0f));
	}

	if (input.isKeyDown(SDLK_e)) {
		// move right
		m_model = glm::rotate(m_model, glm::radians(1.0f), glm::vec3(1.0f, 1.0f, 1.0f));
	}

	if (input.isKeyPressed(SDLK_F2)) {
		if (isWireframe) {
			isWireframe = false;
			std::cout << "DISABLED WIREFRAME" << std::endl;
		}
		else {
			isWireframe = true;
			std::cout << "ENABLED WIREFRAME" << std::endl;
		}
		
	}


}


void GameScreen::update(float deltaTime)
{
	checkInput();
	handleInput();

	const float radius = 10.0f;
	float camX = sin(deltaTime) * radius;
	float camZ = cos(deltaTime) * radius;
	//m_view = glm::lookAt(glm::vec3(camX, 0.0, camZ), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	//m_textureProgram.unBind();

	for (int x = 0; x < 16; x++)
	{
		for (int y = 0; y < 16; y++)
		{
			for (int z = 0; z < 16; z++)
			{
				m_blocks[x][y][z]->update();
			}
		}
	}

}

void GameScreen::draw()
{
	//Enable depth test
	glEnable(GL_DEPTH_TEST);

	glDisable(GL_CULL_FACE);
	// Accept fragment if it closer to the camera than the former one
	//glDepthFunc(GL_LESS);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_proj = glm::perspective(glm::radians(90.0f), (float)m_window->getScreenWidth() / (float)m_window->getScreenHeight(), 0.1f, 500.0f);

	//glm::mat4 model = glm::mat4(1.0f);
	//m_model = glm::rotate(m_model, glm::radians(-1.0f), glm::vec3(1.0f, 1.0f, 1.0f));

	//m_view = glm::mat4(1.0f);
	// note that we're translating the scene in the reverse direction of where we want to move
	//m_view = glm::translate(m_view, glm::vec3(0.0f, 0.0f, -10.0f));

	//glm::mat4 projection;
	//projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

	int modelLocation = m_textureProgram.getUniformLocation("model");
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(m_model));

	int viewLocation = m_textureProgram.getUniformLocation("view");
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(m_view));

	int projectionLocation = m_textureProgram.getUniformLocation("projection");
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(m_proj));

	glUseProgram(m_textureProgram.getShaderProgram());

	if (isWireframe) {
		//Turn on wireframe mode
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}

	for (int x = 0; x < 16; x++)
	{
		for (int y = 0; y < 16; y++)
		{
			for (int z = 0; z < 16; z++)
			{
				m_blocks[x][y][z]->render(m_textureProgram, m_model);
			}
		}
	}
	

	if (isWireframe) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

}

void GameScreen::checkInput()
{
	SDL_Event evnt;
	while (SDL_PollEvent(&evnt))
	{
		if (evnt.type == SDL_MOUSEWHEEL)
		{
			m_view = glm::translate(m_view, glm::vec3(0.0f, 0.0f, evnt.wheel.y * 0.1f));
		}
		m_game->onSDLEvent(evnt);

	}	
}

void GameScreen::drawHud()
{

	
}
