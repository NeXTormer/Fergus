#pragma once

#include <iostream>
#include <GLFW\glfw3.h>

class Window
{
private:
	const char *m_title;
	//TODO: update m_width, m_height when resizeing
	int m_width;
	int m_height;

	GLFWwindow *m_window;

public:
	Window(int witdh, int height, char *title);
	~Window();
	void update();
	bool closed() const;
	void clear();
	inline int getWidth() const { return m_width; }
	inline int getHeight() const { return m_height; }

};