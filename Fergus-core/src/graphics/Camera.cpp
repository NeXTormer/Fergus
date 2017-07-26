#include "camera.h"

Camera::Camera(glm::vec3& pos, Window& window)
	: position(pos), window(window)
{
	pitch = 0;
	yaw = 0;
	roll = 0;
}

void Camera::update()
{
	if(window.isKeyPressed(GLFW_KEY_W))
	{
		position.z -= 0.001;
	}
	if (window.isKeyPressed(GLFW_KEY_A))
	{
		position.x -= 0.001;
	}
	if (window.isKeyPressed(GLFW_KEY_S))
	{
		position.z += 0.001;
	}
	if (window.isKeyPressed(GLFW_KEY_D))
	{
		position.x += 0.001;
	}

	updateViewMatrix();
}

glm::mat4& Camera::getViewMatrix()
{
	return vw_matrix;
}

void Camera::updateViewMatrix()
{
	glm::mat4 mat;

	mat = glm::rotate(mat, toRadians(pitch), glm::vec3(1, 0, 0));
	mat = glm::rotate(mat, toRadians(yaw), glm::vec3(0, 1, 0));
	mat = glm::rotate(mat, toRadians(roll), glm::vec3(0, 0, 1));
	
	mat = glm::translate(mat, glm::vec3(-position.x, -position.y, -position.z));

	vw_matrix = mat;
}
