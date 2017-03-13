#include <iostream>
#include <string>

#include "graphics\window.h"
#include "maths\maths.h"
#include "utils\fileutils.h"

int main(void)
{

	std::string file = read_file("rendl.vert");

	std::cout << file << std::endl;

	system("pause");

	Window window(800, 600, "Lex ist lustig!");
	glClearColor(0.6, 1, 0.5, 1);

	vec2 peter(1, 1);
	vec2 rendl(2, 2);

	vec2 lex = rendl + peter;

	std::cout << lex << std::endl;
	
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