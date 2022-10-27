#include "Engine.h"

#include "Input.h"

#include <vector>
#include "Vertex.h"
#include "Entity.h"

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
	std::vector<Vertex> vertices = {
		Vertex(glm::vec3(0.5f, 0.5f, 0.0f), glm::vec2(1.0f, 1.0f)),
		Vertex(glm::vec3(0.5f, -0.5f, 0.0f), glm::vec2(1.0f, 0.0f)),
		Vertex(glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec2(0.0f, 0.0f)),
		Vertex(glm::vec3(-0.5f, 0.5f, 0.0f), glm::vec2(0.0f, 1.0f)),
	};
	std::vector<unsigned int> indices = {
		0, 1, 3,
		1, 2, 3
	};

	Entity test(vertices, indices);

	while (!m_window.shouldClose())
	{
		Input::getInstance().update();
		m_renderer.update();
		m_window.update();

		m_renderer.render(test);

		m_window.swapBuffers();
	}
	terminate();
}

Engine::Engine()
{
	GLFWwindow* window = m_window.init();
	connectWindowInstanceToInput(window);
	m_window.setVsync(true);
	m_renderer.init(m_window.getWidth(), m_window.getHeight());
}

void Engine::loadScene()
{
}

void Engine::terminate()
{
	m_window.shutdown();
}
