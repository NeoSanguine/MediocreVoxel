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

	glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	float yaw = -90.0f;
	float pitch = 0.0f;
	bool firstMouse = true;
	float lastX = 400, lastY = 300;
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
	delete m_camera;
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
	// texture shaders
	m_textureProgram.compileShaders("bin/shaders/textureShading.vert", "bin/shaders/textureShading.frag");
	m_textureProgram.addAttribute("vertexPosition");
	m_textureProgram.addAttribute("vertexColor");
	m_textureProgram.addAttribute("vertexUV");
	m_textureProgram.linkShaders();

	m_spriteProgram.compileShaders("bin/shaders/spriteShader.vert", "bin/shaders/spriteShader.frag");
	m_spriteProgram.addAttribute("vertexPosition");
	m_spriteProgram.addAttribute("vertexColor");
	m_spriteProgram.addAttribute("vertexUV");
	m_spriteProgram.linkShaders();

	
	m_hudSpriteBatch.init(); // for rendering hud

	//font
	m_spriteFont = new MediocreEngine::SpriteFont("bin/fonts/font.ttf", 32);

	// hud camera
	m_hudCamera.init(m_window->getScreenWidth(), m_window->getScreenHeight());
	m_hudCamera.setPosition(glm::vec2(m_window->getScreenWidth() / 2.0f, m_window->getScreenHeight() / 2.0f));

	


	m_model = glm::mat4(1.0f);
	m_view = glm::mat4(1.0f);
	m_proj = glm::mat4(1.0f);

	isWireframe = false;
	isLooking = false;


	/*for (int x = 0; x < 16; x++)
	{
		for (int y = 0; y < 16; y++)
		{
			for (int z = 0; z < 16; z++)
			{
				m_blocks[x][y][z] = new Block();
				m_blocks[x][y][z]->init(glm::vec3(x, y, z));

				int r = 0, g = 0, b = 0;

				if (x % 10 == 0) {
					r = 255;
				}
				else {
					r = 200;
				}

				if (y % 2 == 0) {
					g = 255;
				}
				else {
					g = 150;
				}

				if (z % 5 == 0) {
					b = 255;
				}
				else {
					b = 100;
				}

				m_blocks[x][y][z]->setColor(r, g, b,255);
				// Render m_pBlocks[x][y][z]
			}
		}
	}*/

	m_chunkManager = new ChunkManager();
	m_chunkManager->init();

	//SDL_WarpMouseInWindow(m_window->getWindow(), m_window->getScreenWidth(), m_window->getScreenHeight());
	//SDL_SetWindowGrab(m_window->getWindow(), SDL_TRUE);
	//SDL_SetRelativeMouseMode(SDL_TRUE); // bind the cursor to the window

	//SDL_CaptureMouse(SDL_TRUE);

	SDL_SetHintWithPriority(SDL_HINT_MOUSE_RELATIVE_MODE_WARP, "1", SDL_HINT_OVERRIDE);
	SDL_SetRelativeMouseMode(SDL_TRUE);
	SDL_CaptureMouse(SDL_TRUE);
	
	m_camera = new Camera3D();
}

void GameScreen::onExit()
{
	
	m_textureProgram.dispose();
}
void GameScreen::handleInput(float deltaTime)
{
	auto input = MediocreEngine::InputManager::get();

	const float cameraSpeed = 0.025f * deltaTime; // adjust accordingly


	if (input.isKeyDown(SDLK_ESCAPE)) {
		m_game->exitGame();
	}

	if (input.isKeyDown(SDL_BUTTON_RIGHT)) {
		isLooking = true;
	}
	else {
		if (isLooking == true) {
			isLooking = false;
		}
	}

	if (input.isKeyDown(SDLK_w)) {

		m_camera->processKeyboard(FORWARD, deltaTime);
	}

	if (input.isKeyDown(SDLK_d)) {
		// move right
		//cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;

		m_camera->processKeyboard(RIGHT, deltaTime);
	}

	if (input.isKeyDown(SDLK_a)) {
		// move right
		//cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
		m_camera->processKeyboard(LEFT, deltaTime);
	}

	if (input.isKeyDown(SDLK_s)) {
		// move right
		// move forward
		/*if (isLooking) {
			m_view = glm::translate(m_view, glm::vec3(0.0f, 0.f, -0.1f));
		}
		else {
			cameraPos -= cameraSpeed * cameraFront;
		}*/

		m_camera->processKeyboard(BACKWARD, deltaTime);
		
	}

	if (input.isKeyDown(SDLK_q)) {
		//m_chunk->setAllInactive();
	}

	if (input.isKeyDown(SDLK_e)) {
		//m_chunk->setAllActive();
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


	//float mouseX = input.getMouseCoordsX();
	//float mouseY = input.getMouseCoordsY();


	int mouseX;
	int mouseY;

	//auto relativeMouse = SDL_GetRelativeMouseState(&mouseX, &mouseY);
	SDL_GetMouseState(&mouseX, &mouseY);
	

	if (firstMouse)
	{
		lastX = mouseX;
		lastY = mouseY;
		firstMouse = false;
	}

	
	float xoffset = mouseX - lastX;
	float yoffset = lastY - mouseY; // reversed since y-coordinates range from bottom to top

	lastX = mouseX;
	lastY = mouseY;


	int relX;
	int relY;

	SDL_GetRelativeMouseState(&relX, &relY);

	// makes it so we can rotate infinitely over the x axis
	if (xoffset == 0) {
		if (relX != 0) {
			xoffset = relX;
		}	
	}

	/*if (yoffset == 0) {
		if (relY != 0) {
			yoffset = relY;
		}
	}*/

	//std::cout << xoffset << std::endl;

	//SDL_WarpMouseInWindow(m_window->getWindow(), 1280 / 2, 720 / 2);

	m_camera->processMouse(xoffset, yoffset);


	m_chunkManager->handleEvents();
	
	

	/*const float sensitivity = 1.0f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 direction;
	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

	cameraFront = glm::normalize(direction);
	*/
}


void GameScreen::update(float deltaTime)
{
	checkInput();
	handleInput(deltaTime);

	const float radius = 10.0f;
	float camX = sin(deltaTime) * radius;
	float camZ = cos(deltaTime) * radius;
	//m_view = glm::lookAt(glm::vec3(camX, 0.0, camZ), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	//m_textureProgram.unBind();

	/*for (int x = 0; x < 16; x++)
	{
		for (int y = 0; y < 16; y++)
		{
			for (int z = 0; z < 16; z++)
			{
				m_blocks[x][y][z]->update(deltaTime);
			}
		}
	}*/

	

	//m_chunk->update(deltaTime);
	m_chunkManager->update(deltaTime, m_camera->position, m_camera->getViewMatrix());

	m_hudCamera.update(deltaTime);

	//glm::vec3 direction;
	//direction.x = cos(glm::radians(yaw)); // Note that we convert the angle to radians first
	//direction.z = sin(glm::radians(yaw));

	m_view = m_camera->getViewMatrix();//glm::lookAt(m_camera->position, m_camera->position + m_camera->front, cameraUp);
}

void GameScreen::draw()
{
	

	//Enable depth test
	glEnable(GL_DEPTH_TEST);

	glDisable(GL_CULL_FACE);
	// Accept fragment if it closer to the camera than the former one
	//glDepthFunc(GL_LESS);

	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_proj = glm::perspective(glm::radians(m_camera->zoom), (float)m_window->getScreenWidth() / (float)m_window->getScreenHeight(), 0.1f, 500.0f);

	//glm::mat4 model = glm::mat4(1.0f);
	//m_model = glm::rotate(m_model, glm::radians(-1.0f), glm::vec3(1.0f, 1.0f, 1.0f));

	//m_view = glm::mat4(1.0f);
	// note that we're translating the scene in the reverse direction of where we want to move
	//m_view = glm::translate(m_view, glm::vec3(0.0f, 0.0f, -10.0f));

	//glm::mat4 projection;
	//projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

	m_textureProgram.bind();

	int modelLocation = m_textureProgram.getUniformLocation("model");
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(m_model));

	int viewLocation = m_textureProgram.getUniformLocation("view");
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(m_view));

	int projectionLocation = m_textureProgram.getUniformLocation("projection");
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(m_proj));

	
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();

	

	if (isWireframe) {
		//Turn on wireframe mode
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}

	//glColor3f(1.0f, 0.0f, 0.0f);

	/*for (int x = 0; x < 16; x++)
	{
		for (int y = 0; y < 16; y++)
		{
			for (int z = 0; z < 16; z++)
			{
				if (y > 2) {
					m_blocks[x][y][z]->setActive(false);
				}

				m_blocks[x][y][z]->render(m_textureProgram, m_model);
			}
		}
	}*/

	m_chunkManager->render(m_textureProgram, m_model);
	//m_chunk->render(m_textureProgram, m_model);
	

	if (isWireframe) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	

	m_textureProgram.unBind();

	m_spriteProgram.bind();
	glm::mat4  projectionMatrixHUD = m_hudCamera.getCameraMatrix();
	GLint pUniformHUD = m_spriteProgram.getUniformLocation("P");
	glUniformMatrix4fv(pUniformHUD, 1, GL_FALSE, glm::value_ptr(projectionMatrixHUD));
	drawHud();
	m_spriteProgram.unBind();
	
}

void GameScreen::checkInput()
{
	SDL_Event evnt;
	while (SDL_PollEvent(&evnt))
	{
		if (evnt.type == SDL_MOUSEWHEEL)
		{
			m_camera->processMouseScroll(evnt.wheel.y);
			//m_view = glm::translate(m_view, glm::vec3(0.0f, 0.0f, evnt.wheel.y * 0.1f));
		}

		m_game->onSDLEvent(evnt);

		
	}	

	
}

void GameScreen::drawHud()
{
	m_hudSpriteBatch.begin();

	// draw fps
	std::string fps = "FPS: " + std::to_string(m_game->getFPS());

	m_spriteFont->draw(m_hudSpriteBatch, fps.c_str(), glm::vec2(0, m_window->getScreenHeight() - 30),
		glm::vec2(1.0), 0.0f, MediocreEngine::ColorRGBA8(255, 255, 0, 255));

	m_hudSpriteBatch.end();
	m_hudSpriteBatch.renderBatch();
}
