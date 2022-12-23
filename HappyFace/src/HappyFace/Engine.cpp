#include "Engine.h"

#include "Input.h"

#include "Model.h"

#include "ResourceManager.h"

#include "GLShaderProgram.h"
#include "GLShader.h"

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

void Engine::go()
{
	Model backpack("resources/objects/backpack/backpack.obj");

	backpack.translate({ 1.0f, 1.0f, 0.0f });
	backpack.scale({ 1.0f, 1.0f, 1.0f });
	backpack.rotate(0.0f, { 1.0f, 0.0f, 0.0f });

	Scene scene;
	scene.addModel(backpack);

	std::vector<std::string> modelShader = { "resources/shaders/model.vs.glsl", "resources/shaders/model.fs.glsl" };
	scene.addShader("modelShader", modelShader);

	while (!m_window.shouldClose())
	{
		// DON'T change the order
		m_renderer.update();
		Input::getInstance().update();
		m_window.update();
		// 

		m_renderer.renderScene(scene);

		m_window.swapBuffers();
	}

	scene.deleteScene();

	terminate();
}

Engine::Engine()
{
	GLFWwindow* window = m_window.init();
	bindWindowToInput(window);
	m_window.setVsync(true);

	m_renderer.init(m_window.getDimensions());
}

void Engine::terminate()
{
	m_window.shutdown();
	m_renderer.shutdown();
}
