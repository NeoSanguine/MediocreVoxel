#include "GameScreen.h"
#include <iostream>
#include <SDL.h>
#include <MediocreEngine\IGame.h>
#include <MediocreEngine\ResourceManager.h>
#include <random>
#include <GL\glew.h>


namespace
{

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
	
}

void GameScreen::onExit()
{
	
}
void GameScreen::handleInput()
{


}


void GameScreen::update(float deltaTime)
{
	
}

void GameScreen::draw()
{
	glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glDisable(GL_DEPTH_TEST);
	glDepthRange(0.0f, 1.0f);
	glClearDepth(0.0f);

	glDepthFunc(GL_LEQUAL);

	// DRAW

	
}

void GameScreen::checkInput()
{
	SDL_Event evnt;
	while (SDL_PollEvent(&evnt))
	{
		
		m_game->onSDLEvent(evnt);

	}
}

void GameScreen::drawHud()
{

	
}
