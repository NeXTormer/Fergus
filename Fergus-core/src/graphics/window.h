#pragma once

#include <iostream>
#include <GL\glew.h>
#include <GLFW\glfw3.h>

class Window
{
	//TODO: Make Input class or make input not static

	friend struct GLFWwindow;
private:
	const char *m_title;
	//TODO: update m_width, m_height when resizeing
	int m_width;
	int m_height;

	GLFWwindow *m_window;

	static const int MAX_KEYS = 1024;
	static const int MAX_MOUSEBUTTONS = 32;

	static bool m_keys[MAX_KEYS];
	static bool m_mouseButtons[MAX_MOUSEBUTTONS];
	static double m_mousex;
	static double m_mousey;

	friend static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
	friend static void mouse_button_callback(GLFWwindow *window, int button, int action, int mods);
	friend static void cursor_position_callback(GLFWwindow *window, double mx, double my);

public:
	Window(int witdh, int height, char *title);
	~Window();


	void update();
	bool closed() const;
	void clear();
	inline int getWidth() const { return m_width; }
	inline int getHeight() const { return m_height; }

	static bool isKeyPressed(unsigned int keycode);
	static bool isMouseButtonPressed(unsigned int keycode);
	static double getMouseX();
	static double getMouseY();
};