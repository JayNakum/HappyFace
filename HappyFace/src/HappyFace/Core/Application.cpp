#include "Application.h"

#include "Platform/Input.h"

#include "Components/Model.h"

#include "Utility/ResourceManager.h"

#include "GL/ShaderProgram.h"
#include "GL/Shader.h"

static void bindWindowToInput(GLFWwindow* window) {
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

namespace Happy {
	void Application::go()
	{
		while (!m_window.shouldClose())
		{
			// DON'T change the order
			m_renderer.update();
			Input::getInstance().update();
			m_window.update();
			// 

			m_renderer.renderScene(*m_scene);

			m_window.swapBuffers();
		}
		terminate();
	}

	void Application::loadScene(Scene* scene)
	{
		m_scene = scene;
		m_scene->init();
	}

	Application::Application()
	{
		GLFWwindow* window = m_window.init();
		bindWindowToInput(window);
		m_window.setVsync(true);

		m_renderer.init(m_window.getDimensions());
	}

	void Application::terminate()
	{
		m_scene->deleteScene();
		delete m_scene;
		m_window.shutdown();
		m_renderer.shutdown();
	}
}
