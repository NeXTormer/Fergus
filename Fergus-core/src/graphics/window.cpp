#include "window.h"

void window_resize(GLFWwindow *window, int width, int height);

bool Window::m_keys[MAX_KEYS];
bool Window::m_mouseButtons[MAX_MOUSEBUTTONS];

double Window::m_mousex;
double Window::m_mousey;

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
	glfwSetWindowSizeCallback(m_window, window_resize);
	glfwSetWindowUserPointer(m_window, this);
	glfwSetKeyCallback(m_window, key_callback);
	glfwSetMouseButtonCallback(m_window, mouse_button_callback);
	glfwSetCursorPosCallback(m_window, cursor_position_callback);

	//VSync
	glfwSwapInterval(0.0);
	//glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

	if (glewInit() != GLEW_OK)
	{
		printf("Failed to initialize GLEW!");
		return;
	}

	for (int i = 0; i < MAX_KEYS; i++)
	{
		m_keys[i] = false;
	}
	
	for (int i = 0; i < MAX_MOUSEBUTTONS; i++)
	{
		m_mouseButtons[i] = false;
	}


	std::cout << glGetString(GL_VERSION) << std::endl;
}


Window::~Window()
{
	glfwTerminate();
}

void Window::update()
{

	GLenum error = glGetError();
	if (error != GL_NO_ERROR)
	{
		std::cout << "OpenGL Error: " << error << std::endl;
	}

	//glfwPollEvents();
	glfwWaitEvents();

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


bool Window::isKeyPressed(unsigned int keycode)
{
	if (keycode >= MAX_KEYS)
	{
		return false;
		printf("Key index out of range!");
	}
	return m_keys[keycode];
}

bool Window::isMouseButtonPressed(unsigned int keycode)
{
	if (keycode >= MAX_MOUSEBUTTONS)
	{
		return false;
		printf("Mousebutton index out of range!");
	}
	return m_mouseButtons[keycode];
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) 
{
	Window *win = (Window *) glfwGetWindowUserPointer(window);
	win->m_keys[key] = action != GLFW_RELEASE;
}

void mouse_button_callback(GLFWwindow *window, int button, int action, int mods)
{
	Window *win = (Window *) glfwGetWindowUserPointer(window);
	win->m_mouseButtons[button] = action != GLFW_RELEASE;
}

void cursor_position_callback(GLFWwindow *window, double mx, double my)
{
	Window *win = (Window *) glfwGetWindowUserPointer(window);
	win->m_mousex = mx;
	win->m_mousey = my;
}

double Window::getMouseX()
{
	return m_mousex;
}

double Window::getMouseY()
{
	return m_mousey;
}

void window_resize(GLFWwindow *window, int width, int height) 
{
	glViewport(0, 0, width, height);
}

