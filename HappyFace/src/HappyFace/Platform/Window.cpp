#include "Window.h"

#include "Input.h"

#include <iostream>

void Window::update()
{
	glfwPollEvents();
	if (Input::getInstance().isKeyPressed(Input::TAB)) {
		if (m_data.showCursor)
			enableCursor();
		else
			disableCursor();
		m_data.showCursor = !m_data.showCursor;
	}

	if (glfwWindowShouldClose(m_window) || Input::getInstance().isKeyPressed(Input::ESC)) {
		m_data.shouldWindowClose = true;
		glfwSetWindowShouldClose(m_window, true);
	}
}

GLFWwindow* Window::init(const std::string& title, const unsigned int width, const unsigned int height, const bool fullscreen)
{
	if (!glfwInit()) {
		std::cerr << "Failed to start GLFW." << std::endl;
		std::abort();
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Determine if fullscreen is requested
	if (fullscreen) {
		m_window = glfwCreateWindow((int)width, (int)height, title.c_str(), glfwGetPrimaryMonitor(), nullptr);
	}
	else {
		m_window = glfwCreateWindow((int)width, (int)height, title.c_str(), nullptr, nullptr);
	}

	if (!m_window) {
		std::cerr << "Failed to create GLFW window." << std::endl;
		std::abort();
	}

	glfwMakeContextCurrent(m_window);
	glfwFocusWindow(m_window);

	// Center window
	const auto mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	glfwSetWindowPos(m_window, (mode->width / 2) - width / 2, (mode->height / 2) - height / 2);

	m_data.title = title;
	m_data.width = width;
	m_data.height = height;

	return m_window;
}

void Window::swapBuffers() const
{
	glfwSwapBuffers(m_window);
}

void Window::enableCursor() const
{
	glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void Window::disableCursor() const
{
	glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Window::setVsync(const bool vsync) const
{
	glfwSwapInterval(static_cast<int>(vsync));
}

void Window::shutdown() const
{
	glfwDestroyWindow(m_window);
	glfwTerminate();
}
