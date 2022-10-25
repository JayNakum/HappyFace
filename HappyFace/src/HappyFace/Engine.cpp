#include "Engine.h"

#include "Input.h"

#include <GLFW/glfw3.h>

static void connectWindowInstanceToInput(GLFWwindow* window) {
	const auto resizeCallback = [](GLFWwindow* w, auto width, auto height) {
		Input::getInstance().windowResized(width, height);
	};
	glfwSetWindowSizeCallback(window, resizeCallback);

	const auto keyCallback = [](GLFWwindow* w, auto key, auto scancode, auto action, auto mode) {
		Input::getInstance().keyPressed(key, scancode, action, mode);
	};
	glfwSetKeyCallback(window, keyCallback);

	const auto cursorPosCallback = [](GLFWwindow* w, auto xPos, auto yPos) {
		Input::getInstance().mouseMoved(xPos, yPos);
	};
	glfwSetCursorPosCallback(window, cursorPosCallback);
}

void Engine::go()
{
	while (!m_window.shouldClose())
	{
		m_renderer.update();
		Input::getInstance().update();
		m_window.update();

		m_window.swapBuffers();
	}
	terminate();
}

Engine::Engine()
{
	GLFWwindow* window = m_window.init();
	connectWindowInstanceToInput(window);

	m_renderer.init(m_window.getWidth(), m_window.getHeight());
}

void Engine::terminate()
{
	m_window.shutdown();
}
