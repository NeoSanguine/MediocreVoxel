#include "App.h"
#include <memory>
#include <MediocreEngine\ScreenList.h>
#include <iostream>

App::App()
{
}

App::~App()
{
}

void App::onInit()
{
	//std::cout << "Setting fullscreen" << std::endl;
	//m_window.setWindowSize(1280, 720); // 
	//m_window.setFlags(SDL_WINDOW_FULLSCREEN);
	

	m_window.setWindowSize(1280, 720); // 


	m_window.setWindowName("MediocreVoxel");
}

void App::addScreens()
{
	m_gameScreen = std::make_unique<GameScreen>(&m_window);
	m_screenList->addScreen(m_gameScreen.get());

	m_screenList->setScreen(m_gameScreen.get()->getScreenIndex());
}

void App::onExit()
{

}
