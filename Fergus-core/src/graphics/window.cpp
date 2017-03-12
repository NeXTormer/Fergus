#include "window.h"

void windowResize(GLFWwindow *window, int width, int height);

Window::Window(int width, int height, char *title)
{

	m_width = width;
	m_height = height;
	m_title = title;

	if (!glfwInit())
	{
		printf("Failed to initialize GLFW!");
		glfwTerminate();
		return;
	}

	m_window = glfwCreateWindow(width, height, title, NULL, NULL);
	if (!m_window)
	{
		glfwTerminate();
		printf("Failed to create Window!");
		return;
	}

	glfwMakeContextCurrent(m_window);
	glfwSetWindowSizeCallback(m_window, windowResize);

}


Window::~Window()
{
	glfwTerminate();
}

void Window::update()
{
	glfwPollEvents();
	glfwGetFramebufferSize(m_window, &m_width, &m_height);
	glViewport(0, 0, m_width, m_height);
	glfwSwapBuffers(m_window);
}

bool Window::closed() const
{
	return glfwWindowShouldClose(m_window);
}

void Window::clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void windowResize(GLFWwindow *window, int width, int height) 
{
	glViewport(0, 0, width, height);
}