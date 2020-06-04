#include <gtc/matrix_transform.hpp>
#include "Camera3D.h"
#include <iostream>


Camera3D::Camera3D(glm::vec3 position, glm::vec3 up, float yaw, float pitch)
{
	this->position = position;
	this->worldUp = up;
	this->yaw = yaw;
	this->pitch = pitch;
	this->front = glm::vec3(0.0f, 0.0f, -1.0f);
	this->movementSpeed = SPEED;
	this->mouseSensitivity = SENSITIVITY;
	this->zoom = zoom;
	updateCameraVectors();
}

Camera3D::Camera3D(float x, float y, float z, float upX, float upY, float upZ, float yaw, float pitch)
{
	position = glm::vec3(x, y, z);
	worldUp = glm::vec3(upX, upY, upZ);
	this->yaw = yaw;
	this->pitch = pitch;
	updateCameraVectors();
}

glm::mat4 Camera3D::getViewMatrix()
{
	return glm::lookAt(this->position, this->position + this->front, this->up);
}

void Camera3D::processKeyboard(CAMERA_MOVEMENT direction, float deltaTime)
{
	float veloctiy = movementSpeed * deltaTime;
	
	if (hasCameraMoved) {
		hasCameraMoved = false;
	}

	if (direction == FORWARD) {
		position += front * veloctiy;
		hasCameraMoved = true;
	}

	if (direction == BACKWARD) {
		position -= front * veloctiy;
		hasCameraMoved = true;
	}

	if (direction == LEFT) {
		position -= right * veloctiy;
		hasCameraMoved = true;
	}

	if (direction == RIGHT) {
		position += right * veloctiy;
		hasCameraMoved = true;
	}

	//std::cout << hasCameraMoved << std::endl;
}

void Camera3D::processMouse(float xoffset, float yoffset, bool contrainPitch)
{
	xoffset *= mouseSensitivity;
	yoffset *= mouseSensitivity;

	yaw += xoffset;
	pitch += yoffset;

	// makre sure that when the pitch is out of bounds, that 
	// the screen doesn't get flipped

	if (contrainPitch) {
		if (pitch > 89.0f) {
			pitch = 89.0f;
		}

		if (pitch < -89.0f) {
			pitch = -89.0f;
		}
	}

	updateCameraVectors();
}

void Camera3D::processMouseScroll(float yoffset)
{
	zoom -= (float)yoffset;
	if (zoom < 1.0f) {
		zoom = 1.0f;
	}
	
	if (zoom > 45.0f) {
		zoom = 45.0f;
	}
}

void Camera3D::updateCameraVectors()
{
	// calculate the new front vector
	glm::vec3 front;

	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

	this->front = glm::normalize(front);

	//also recalculate the right and up vector
	right = glm::normalize(glm::cross(this->front, worldUp)); // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	up = glm::normalize(glm::cross(right, this->front));
}




