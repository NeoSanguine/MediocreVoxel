#pragma once
#include <MediocreEngine\IGame.h>
#include "GameScreen.h"
#include <memory>



class App : public MediocreEngine::IGame
{
public:
	App();
	~App();

	// Inherited via IGame
	virtual void onInit() override;
	virtual void addScreens() override;
	virtual void onExit() override;

private:
	std::unique_ptr<GameScreen> m_gameScreen = nullptr;

};

