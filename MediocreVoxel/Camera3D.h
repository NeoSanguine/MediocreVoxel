#pragma once

#ifndef CAMERA3D_H_
#define CAMERA3D_H_

#include <glm.hpp>
#include <GL/glew.h>

enum CAMERA_MOVEMENT {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 0.01f;
const float SENSITIVITY = 1.0f;
const float ZOOM = 45.0f;

class Camera3D {
public:
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 worldUp;

	//euler angles
	float yaw;
	float pitch;

	// camera options
	float movementSpeed;
	float mouseSensitivity;
	float zoom;

	Camera3D(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = -90.0f, float pitch = 0.0f);
	Camera3D(float x, float y, float z, float upX, float upy, float upZ, float yaw, float pitch);

	glm::mat4 getViewMatrix();

	void processKeyboard(CAMERA_MOVEMENT direction, float deltaTime);

	void processMouse(float xoffset, float yoffset, bool contrainPitch = true);

	void processMouseScroll(float yoffset);

private:
	void updateCameraVectors();
};

#endif /// CAMERA3D_H_