#include <iostream>

#include "graphics\window.h"
#include "glm/glm.hpp"

int main(void)
{

	glm::vec2 peter(1, 2);
	std::cout << peter.x << std::endl;
	
	Window window(800, 600, "Lex ist lustig!");
	glClearColor(0.6, 1, 0.5, 1);


	while (!window.closed())
	{
		window.clear();
		
		std::cout << window.getMouseX() << ", " << window.getMouseY() << std::endl;

		glBegin(GL_TRIANGLES);
		glVertex2f(-0.5f, -0.5f);
		glVertex2f(0.5f, 0.5f);
		glVertex2f(0.5f, -0.5f);
		glEnd();
		
		window.update();
	}

	return 0;
}