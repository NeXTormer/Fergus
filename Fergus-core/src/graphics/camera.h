#pragma once

#include <GL\glew.h>
#include <iostream>
#include "GLFW\glfw3.h"

#include "../maths/maths.h"
#include "../graphics/window.h"

class Camera
{
public:
	Camera(glm::vec3& pos, Window& window);

	glm::vec3 position;
	float pitch;
	float yaw;
	float roll;

	void update();

	glm::mat4& getViewMatrix();

private:

	Window& window;
	glm::mat4 vw_matrix;

	void updateViewMatrix();

};