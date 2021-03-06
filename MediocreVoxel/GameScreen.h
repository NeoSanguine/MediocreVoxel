#pragma once

#include <MediocreEngine/IScreen.h>
#include <MediocreEngine/Window.h>
#include <MediocreEngine/GLSLProgram.h>
#include <GL\glew.h>
#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include "Block.h"
#include <MediocreEngine/SpriteBatch.h>
#include <MediocreEngine/SpriteFont.h>
#include <MediocreEngine/Camera2D.h>
#include "Camera3D.h"
#include "ChunkManager.h"

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
	void handleInput(float deltaTime);
	virtual void update(float deltaTime) override;
	virtual void draw() override;


	const float cameraSpeed = 1.0f;
	const float maxCameraSpeed = 2.0f;

private:
	void checkInput();

	void drawHud();

	MediocreEngine::GLSLProgram m_textureProgram;
	MediocreEngine::GLSLProgram m_spriteProgram;
	MediocreEngine::Window * m_window;

	unsigned int VAO;
	unsigned int VBO;

	ChunkManager * m_chunkManager;

	MediocreEngine::SpriteBatch m_hudSpriteBatch;
	MediocreEngine::SpriteFont* m_spriteFont;
	MediocreEngine::Camera2D m_hudCamera;

	Camera3D * m_camera;
	
	glm::mat4 m_proj;
	glm::mat4 m_model;
	glm::mat4 m_view;

	bool isWireframe;
	bool isLooking;

};