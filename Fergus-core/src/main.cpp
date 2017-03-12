#include <iostream>

#include "graphics\window.h"

int main(void)
{
	
	Window window(800, 600, "Lex ist lustig!");
	glClearColor(0.6, 1, 0.5, 1);


	while (!window.closed())
	{
		window.clear();

		glBegin(GL_TRIANGLES);
		glVertex2f(-0.5f, -0.5f);
		glVertex2f(0.5f, 0.5f);
		glVertex2f(0.5f, -0.5f);
		glEnd();
		
		window.update();
	}

	return 0;
}