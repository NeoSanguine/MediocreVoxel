#pragma once

#include <MediocreEngine/IScreen.h>
#include <MediocreEngine/Window.h>

class GameScreen : public MediocreEngine::IScreen
{
public:
	GameScreen(MediocreEngine::Window* window);
	~GameScreen();

	// Inherited via IScreen
	virtual int getNextScreenIndex() const override;
	virtual int getPreviousScreenIndex() const override;
	virtual void build() override;
	virtual void destroy() override;
	virtual void onEnter() override;
	virtual void onExit() override;
	// TODO: add abstract to IGame class in MediocreEngine, and override here
	void handleInput();
	virtual void update(float deltaTime) override;
	virtual void draw() override;


	const float cameraSpeed = 1.0f;
	const float maxCameraSpeed = 2.0f;

private:
	void checkInput();

	void drawHud();

	MediocreEngine::Window * m_window;

};