# Happy Face
A Scene Based OpenGL Renderer.  
This file goes through each file explaining the basics of what each class is there for.
The primary purpose of creating this file was to have a one stop destination for the whole project.  

***

**TestApp.cpp** is what you need to write to use the renderer.
```cpp
#include "HappyFace/HappyFace.h"

class TestScene : public Happy::Scene
{
public:
	TestScene()
	{
		Model backpack("resources/objects/plane/plane.obj");
		backpack.rotate(90.0f, { 0.0f, 1.0f, 0.0f });
		addModel(backpack);
	}
};

class TestApp : public Happy::Application
{
public:
	TestApp()
	{
		loadScene(new TestScene());
	}
};

Happy::Application* createApplication()
{
	return new TestApp();
}
```
***
**HappyFace.h** is the only file needed to be included to use the renderer.
```cpp
#pragma once

#include "Core/Application.h"
#include "Core/EntryPoint.h"
#include "Core/Scene.h"
```
***
**Core/EntryPoint.h** is the file containing the main method. This is seperated from the client side code to let the renderer have a full control over the application.
```cpp
#pragma once

extern Happy::Application* createApplication();

int main()
{
	auto engine = createApplication();
	engine->go();
	delete engine;
}
```

**Core/Application.h** is the main application class where everything is initialized and managed. The Application class has the main loop and it also contains the ```loadScene()``` which will be called by the child class.
```cpp
#pragma once

#include "Renderer.h"
#include "Scene.h"

#include "Platform/Window.h"

namespace Happy {
	class Application
	{
	public:
		Application();
		void go();

	protected:
		void loadScene(Scene* scene);

	private:
		std::string title = "learnopengl.com"; // A thanks to https://learnopengl.com as thats where I've learnt it all from!
		void terminate();
		Scene* m_scene = nullptr;
		Renderer m_renderer;
		Window m_window;
	};
}
```
**Core/Application.cpp**
```cpp
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
		GLFWwindow* window = m_window.init(title);
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
```
***
**Platform/Window.h** is the window manager class.
```cpp
#pragma once

#include <GLFW/glfw3.h>

#include <string>
#include <utility>

class Window
{
public:
	Window() noexcept = default;
	void update();

	GLFWwindow* init(const std::string& title, const unsigned int width = 800, const unsigned int height = 600, const bool fullscreen = false);
	void shutdown() const;

	void swapBuffers() const;

	void enableCursor() const;
	void disableCursor() const;

	void setVsync(const bool vsync) const;

	inline unsigned int getWidth() const noexcept { return m_data.width; }
	inline unsigned int getHeight() const noexcept { return m_data.height; }
	inline std::pair<int, int> getDimensions() const noexcept { return std::make_pair<int, int>((int)m_data.width, (int)m_data.height); }

	inline bool shouldClose() const noexcept { return m_data.shouldWindowClose; }
	inline bool isCursorEnabled() const noexcept { return m_data.showCursor; }

private:
	GLFWwindow* m_window{ nullptr };

	struct WindowData {
		std::string title;
		unsigned int width;
		unsigned int height;

		bool shouldWindowClose;
		bool showCursor;
	}m_data;
};
```
**Platform/Window.cpp**
```cpp
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
```

**Platform/Input.h** is the basic input handling and polling system used by the renderer.
```cpp
#pragma once

#include <GLFW/glfw3.h>

#include <functional>
#include <array>

class Input
{
	Input() 
	{
		std::fill(m_keys.begin(), m_keys.end(), false);
		std::fill(m_prevKeys.begin(), m_prevKeys.end(), false);
	}
	~Input() = default;

public:

	float lastX = (float)m_windowWidth / 2.0;
	float lastY = (float)m_windowHeight / 2.0;
	bool firstMouse = true;

	enum Key : int{
		W = GLFW_KEY_W,
		A = GLFW_KEY_A,
		S = GLFW_KEY_S,
		D = GLFW_KEY_D,
		SPACE = GLFW_KEY_SPACE,

		UP = GLFW_KEY_UP,
		LEFT = GLFW_KEY_LEFT,
		DOWN = GLFW_KEY_DOWN,
		RIGHT = GLFW_KEY_RIGHT,
		RSHIFT = GLFW_KEY_RIGHT_SHIFT,
		RCTRL = GLFW_KEY_RIGHT_CONTROL,
		
		TAB = GLFW_KEY_TAB,
		ESC = GLFW_KEY_ESCAPE
	};
	
	static Input& getInstance() 
	{
		static Input instance;
		return instance;
	}

	Input(const Input&) = delete;
	Input& operator=(const Input&) = delete;

    // Keyboard
	inline bool isKeyPressed(const std::size_t key) const noexcept 
	{
		return m_keys[key] && !m_prevKeys[key];
	}
	inline bool isKeyHeld(const std::size_t key) const noexcept 
	{
		return m_keys[key];
	}
	std::function<void(int, int, int, int)> keyPressed = [&](auto key, auto scancode, auto action, auto mode) 
	{
		if (key >= 0 && key < 1024) 
		{
			switch (action) 
			{
				case 1:
					this->m_keys[key] = true;
					break;
				case 0:
					this->m_keys[key] = false;
					break;
			}
		}
	};

	// Mouse
	inline bool isMouseMoved() const noexcept { return m_mouseMoved; }
	inline double getMouseX() const noexcept { return m_mouseX; }
	inline double getMouseY() const noexcept { return m_mouseY; }
	std::function<void(double, double)> mouseMoved = [&](auto xPos, auto yPos) 
	{
		this->m_mouseMoved = true;
		this->m_mouseX = xPos;
		this->m_mouseY = yPos;
	};

	// Window
	inline bool isWindowResized() const noexcept { return m_windowResized; }
	inline int getWindowWidth() const noexcept { return (int)m_windowWidth; }
	inline int getWindowHeight() const noexcept { return (int)m_windowHeight; }
	std::function<void(int, int)> windowResized = [&](auto width, auto height) 
	{
		this->m_windowResized = true;
		this->m_windowWidth = width;
		this->m_windowHeight = height;
	};

	void update() 
	{
		m_mouseMoved = false;
		m_windowResized = false;

		std::copy(m_keys.cbegin(), m_keys.cend(), m_prevKeys.begin());
	}

private:
	// Keyboard
	std::array<bool, 1024> m_keys;
	std::array<bool, 1024> m_prevKeys;

	// Mouse
	bool m_mouseMoved = false;
	double m_mouseX, m_mouseY;

	// Window
	bool m_windowResized = false;
	std::size_t m_windowWidth, m_windowHeight;
};
```
***
**Core/Scene.h** is the scene base class encapsulating all the scene components.
```cpp
#pragma once

#include "Components/Model.h"
#include "Components/Camera.h"

#include "GL/ShaderProgram.h"
#include "GL/Shader.h"

#include <string>
#include <unordered_map>

namespace Happy {
	class Scene
	{
	public:
		Camera camera;
		std::vector<Model> models;

		inline GL::ShaderProgram& getShader(const std::string& name) { return shaders.at(name); }

		Scene();

		void init();

		void addModel(const Model& model);
		// TODO: void addLight();

		void deleteScene();

	protected:
		std::vector<std::string> modelShader = { "resources/shaders/model.vs.glsl", "resources/shaders/model.fs.glsl" };
		void addShader(const std::string& name, const std::vector<std::string>& shaders);

	private:
		std::unordered_map<std::string, GL::ShaderProgram> shaders;
	};
}
```
**Core/Scene.cpp**
```cpp
#include "Scene.h"

#include "Utility/ResourceManager.h"

namespace Happy {
	Scene::Scene()
		: camera(glm::vec3(0.0f, 0.0f, 3.0f)) {}

	void Scene::addModel(const Model& model)
	{
		models.push_back(model);
	}

	void Scene::init()
	{
		addShader("modelShader", modelShader);
	}

	void Scene::addShader(const std::string& name, const std::vector<std::string>& shaderPaths)
	{
		GL::ShaderProgram shaderProgram;
		std::vector<GL::Shader> shadersList;

		for (auto& path : shaderPaths)
		{
			GL::Shader shader = ResourceManager::getInstance().loadShader(path);
			shadersList.push_back(shader);
			shaderProgram.attach(shader.getID());
		}

		shaderProgram.linkProgram();
		shaders.insert({ name, shaderProgram });

		for (auto& shader : shadersList)
			shader.deleteShader();
	}

	void Scene::deleteScene()
	{
		for (auto& model : models)
			model.deleteModel();
		models.clear();

		for (auto& shader : shaders)
			(shader.second).deleteProgram();
		shaders.clear();
	}
}
```

**Core/Renderer.h** is the heart of the system. This is where all the rendering is initialized and managed.
```cpp
#pragma once

#include "GL/ShaderProgram.h"

#include "Scene.h"

#include <unordered_map>

class Renderer
{
public:
	void init(const std::pair<int, int>& viewport);
	void update();
	
	void renderScene(Happy::Scene& scene);
	void renderModel(const Model& model, const GL::ShaderProgram& shader);
	void renderMesh(const Mesh& mesh, const GL::ShaderProgram& shader);

	void shutdown();
private:
	void defaultGLSettings() const;
	// void compileShaders();

	unsigned int m_viewportWidth, m_viewportHeight;
	std::unordered_map<const char*, GL::ShaderProgram> m_shaderCache;
};
```
**Core/Renderer.cpp**
```cpp
#include "Renderer.h"

#include "Platform/Input.h"
#include "Utility/ResourceManager.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

static float deltaTime = 0.0f;
static float lastFrame = 0.0f;

static void handleCameraEvents(Camera& camera)
{
    Input& inputHandler = Input::getInstance();

    if (inputHandler.isKeyHeld(Input::UP))
        camera.processKeyboard(camera.FORWARD, deltaTime);
    if (inputHandler.isKeyHeld(Input::LEFT))
        camera.processKeyboard(camera.LEFT, deltaTime);
    if (inputHandler.isKeyHeld(Input::DOWN))
        camera.processKeyboard(camera.BACKWARD, deltaTime);
    if (inputHandler.isKeyHeld(Input::RIGHT))
        camera.processKeyboard(camera.RIGHT, deltaTime);
    if (inputHandler.isKeyHeld(Input::RSHIFT))
        camera.processKeyboard(camera.UP, deltaTime);
    if (inputHandler.isKeyHeld(Input::RCTRL))
        camera.processKeyboard(camera.DOWN, deltaTime);

    if (inputHandler.isMouseMoved())
    {
        float xpos = static_cast<float>(inputHandler.getMouseX());
        float ypos = static_cast<float>(inputHandler.getMouseY());
        if (inputHandler.firstMouse)
        {
            inputHandler.lastX = xpos;
            inputHandler.lastY = ypos;
            inputHandler.firstMouse = false;
        }

        float xoffset = xpos - inputHandler.lastX;
        float yoffset = inputHandler.lastY - ypos;

        inputHandler.lastX = xpos;
        inputHandler.lastY = ypos;
        camera.processMouseMovement(xoffset, yoffset);
    }
}

void Renderer::renderScene(Happy::Scene& scene)
{
    glm::mat4 view = scene.camera.getViewMatrix();
    glm::mat4 projection = glm::perspective(glm::radians(scene.camera.zoom), (float)m_viewportWidth / (float)m_viewportHeight, 0.1f, 100.0f);

    auto& modelShader = scene.getShader("modelShader");
    modelShader.use();

    modelShader.setMat4("view", view);
    modelShader.setMat4("projection", projection);

    for (auto& model : scene.models)
    {
        modelShader.setMat4("model", model.getModelMatrix());
        renderModel(model, modelShader);
    }
    modelShader.unUse();

    handleCameraEvents(scene.camera);
}

void Renderer::renderModel(const Model& model, const GL::ShaderProgram& shader)
{
    for (unsigned int i = 0; i < model.meshes.size(); i++)
        renderMesh(model.meshes[i], shader);
}

void Renderer::renderMesh(const Mesh& mesh, const GL::ShaderProgram& shader)
{
    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;
    unsigned int normalNr = 1;
    unsigned int heightNr = 1;
    for (unsigned int i = 0; i < mesh.textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i);

        std::string number;
        std::string name = mesh.textures[i].type;
        if (name == "texture_diffuse")
            number = std::to_string(diffuseNr++);
        else if (name == "texture_specular")
            number = std::to_string(specularNr++);
        else if (name == "texture_normal")
            number = std::to_string(normalNr++);
        else if (name == "texture_height")
            number = std::to_string(heightNr++);

        shader.setInt((name + number).c_str(), i);
        mesh.textures[i].bind(i);
    }

    mesh.VAO.bind();
    glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(mesh.indices.size()), GL_UNSIGNED_INT, 0);
    mesh.VAO.unbind();
    glActiveTexture(GL_TEXTURE0);
}

void Renderer::update()
{
    float currentFrame = static_cast<float>(glfwGetTime());
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    defaultGLSettings();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (Input::getInstance().isWindowResized()) {
        m_viewportWidth = Input::getInstance().getWindowWidth();
        m_viewportHeight = Input::getInstance().getWindowHeight();

        glViewport(0, 0, m_viewportWidth, m_viewportHeight);
    }
}

void Renderer::init(const std::pair<int, int>& viewport)
{
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        std::abort();
    }

    m_viewportWidth = viewport.first;
    m_viewportHeight = viewport.second;

    defaultGLSettings();
}

void Renderer::defaultGLSettings() const
{
    glClearColor(0.07f, 0.07f, 0.07f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    /*
    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    */
    glViewport(0, 0, (int)m_viewportWidth, (int)m_viewportHeight);
}

void Renderer::shutdown()
{
    for (auto& program : m_shaderCache)
        program.second.deleteProgram();
    m_shaderCache.clear();
}
```
***
Now lets go through all the components of the system.  
**Components/Camera.h** has the Camera class which is the moving camera aka the projection matrix of the scene. The class handles the movement of camera.
```cpp
#pragma once

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

static const float YAW = -90.0f;
static const float PITCH = 0.0f;
static const float SPEED = 2.5f;
static const float SENSITIVITY = 0.1f;
static const float ZOOM = 45.0f;

class Camera
{
public:
    enum Camera_Movement {
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT,
        UP,
        DOWN
    };

    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;

    float yaw;
    float pitch;

    float movementSpeed;
    float mouseSensitivity;
    float zoom;

    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);

    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);

    inline glm::mat4 getViewMatrix() const { return glm::lookAt(position, position + front, up); }

    void processKeyboard(Camera_Movement direction, float deltaTime);
    void processMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);
    void processMouseScroll(float yoffset);

private:
    void updateCameraVectors();

    // // Custom implementation of the LookAt function
    // glm::mat4 calculate_lookAt_matrix(glm::vec3 position, glm::vec3 target, glm::vec3 worldUp)
    // {
    //     // 1. Position = known
    //     // 2. Calculate cameraDirection
    //     glm::vec3 zaxis = glm::normalize(position - target);
    //     // 3. Get positive right axis vector
    //     glm::vec3 xaxis = glm::normalize(glm::cross(glm::normalize(worldUp), zaxis));
    //     // 4. Calculate camera up vector
    //     glm::vec3 yaxis = glm::cross(zaxis, xaxis);
       
    //     // Create translation and rotation matrix
    //     // In glm we access elements as mat[col][row] due to column-major layout
    //     glm::mat4 translation = glm::mat4(1.0f); // Identity matrix by default
    //     translation[3][0] = -position.x; // Third column, first row
    //     translation[3][1] = -position.y;
    //     translation[3][2] = -position.z;
    //     glm::mat4 rotation = glm::mat4(1.0f);
    //     rotation[0][0] = xaxis.x; // First column, first row
    //     rotation[1][0] = xaxis.y;
    //     rotation[2][0] = xaxis.z;
    //     rotation[0][1] = yaxis.x; // First column, second row
    //     rotation[1][1] = yaxis.y;
    //     rotation[2][1] = yaxis.z;
    //     rotation[0][2] = zaxis.x; // First column, third row
    //     rotation[1][2] = zaxis.y;
    //     rotation[2][2] = zaxis.z;
       
    //     // Return lookAt matrix as combination of translation and rotation matrix
    //     return rotation * translation; // Remember to read from right to left (first translation then rotation)
    // }
};
```
**Components/Camera.cpp**
```cpp
#include "Camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch)
    : front(glm::vec3(0.0f, 0.0f, -1.0f)), movementSpeed(SPEED), mouseSensitivity(SENSITIVITY), zoom(ZOOM)
{
    this->position = position;
    this->worldUp = up;
    this->yaw = yaw;
    this->pitch = pitch;
    updateCameraVectors();
}

Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch)
    : front(glm::vec3(0.0f, 0.0f, -1.0f)), movementSpeed(SPEED), mouseSensitivity(SENSITIVITY), zoom(ZOOM)
{
    this->position = glm::vec3(posX, posY, posZ);
    this->worldUp = glm::vec3(upX, upY, upZ);
    this->yaw = yaw;
    this->pitch = pitch;
    updateCameraVectors();
}

void Camera::processKeyboard(Camera_Movement direction, float deltaTime)
{
    float velocity = movementSpeed * deltaTime;
    if (direction == FORWARD)
        position += front * velocity;
    if (direction == BACKWARD)
        position -= front * velocity;
    if (direction == LEFT)
        position -= right * velocity;
    if (direction == RIGHT)
        position += right * velocity;
    if (direction == UP)
        position += up * velocity;
    if (direction == DOWN)
        position -= up * velocity;
}

void Camera::processMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch)
{
    xoffset *= mouseSensitivity;
    yoffset *= mouseSensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if (constrainPitch)
    {
        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;
    }

    updateCameraVectors();
}

void Camera::processMouseScroll(float yoffset)
{
    zoom -= (float)yoffset;
    if (zoom < 1.0f)
        zoom = 1.0f;
    if (zoom > 45.0f)
        zoom = 45.0f;
}

void Camera::updateCameraVectors()
{
    glm::vec3 frnt;
    frnt.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    frnt.y = sin(glm::radians(pitch));
    frnt.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(frnt);

    right = glm::normalize(glm::cross(front, worldUp));
    up = glm::normalize(glm::cross(right, front));
}
```

**Components/Mesh.h** has the Mesh calss which is the basic shape containing verticies indicies and textures.
```cpp
#pragma once

#include "GL/Vertex.h"
#include "GL/VertexArray.h"
#include "GL/Texture.h"

#include <string>
#include <vector>

class Mesh
{
public:
    std::vector<GL::Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<GL::Texture> textures;
    GL::VertexArray VAO;

    Mesh(std::vector<GL::Vertex> vertices, std::vector<unsigned int> indices, std::vector<GL::Texture> textures);
    void deleteMesh();
private:
    void setupMesh();
};
```
**Components/Mesh.cpp**
```cpp
#include "Mesh.h"

Mesh::Mesh(std::vector<GL::Vertex> vertices, std::vector<unsigned int> indices, std::vector<GL::Texture> textures)
{
    this->vertices = vertices;
    this->indices = indices;
    this->textures = textures;
    setupMesh();
}

void Mesh::deleteMesh()
{
    VAO.deleteVAO();
    vertices.clear();
    indices.clear();
    for (auto& tex : textures)
    {
        tex.deleteTexture();
    }
    textures.clear();
}

void Mesh::setupMesh()
{
    VAO.create();
    VAO.attachBuffer(GL::VertexArray::ARRAY, vertices.size() * sizeof(GL::Vertex), &vertices[0], GL::VertexArray::STATIC);
    VAO.attachBuffer(GL::VertexArray::ELEMENT, indices.size() * sizeof(unsigned int), &indices[0], GL::VertexArray::STATIC);

    unsigned int offset = sizeof(GL::Vertex);
    // vertex Positions
    VAO.enableAttribute(0, 3, GL::VertexArray::FLOAT, offset, (void*)0);
    // vertex normals
    VAO.enableAttribute(1, 3, GL::VertexArray::FLOAT, offset, (void*)offsetof(GL::Vertex, normal));
    // vertex texture coords
    VAO.enableAttribute(2, 2, GL::VertexArray::FLOAT, offset, (void*)offsetof(GL::Vertex, texCoords));
    // vertex tangent
    VAO.enableAttribute(3, 3, GL::VertexArray::FLOAT, offset, (void*)offsetof(GL::Vertex, tangent));
    // vertex bitangent
    VAO.enableAttribute(4, 3, GL::VertexArray::FLOAT, offset, (void*)offsetof(GL::Vertex, bitangent));
    // ids
    VAO.enableAttribute(5, 4, GL::VertexArray::INT, offset, (void*)offsetof(GL::Vertex, m_BoneIDs));
    // weights
    VAO.enableAttribute(6, 4, GL::VertexArray::FLOAT, offset, (void*)offsetof(GL::Vertex, m_Weights));

    VAO.unbind();
}
```

**Components/Model.h** is the 3D textured model class loaded using ASSIMP library.
```cpp
#pragma once

#include "Mesh.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <string>
#include <vector>

class Model
{
public:
	std::string directory;
	std::vector<Mesh> meshes;
	std::vector<GL::Texture> textures_loaded;
	bool gammaCorrection = false;
	
	Model(const std::string& path, bool gamma = false);
	void deleteModel();

	void scale(const glm::vec3& scale);
	void rotate(const float angle, const glm::vec3& axis);
	void translate(const glm::vec3& pos);
	glm::mat4 getModelMatrix() const;

private:
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);

	std::vector<GL::Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);

	glm::vec3 m_scale = {1.0f, 1.0f, 1.0f}, m_position;
	
	glm::vec3 m_axis;
	float m_radians = 0.0f;
};
```
**Components/Model.cpp**
```cpp
#include "Model.h"

#include "Utility/ResourceManager.h"

#include <iostream>

Model::Model(const std::string& path, bool gamma)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace | aiProcess_OptimizeMeshes);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
    {
        std::cerr << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
        return;
    }

    directory = path.substr(0, path.find_last_of('/'));

    processNode(scene->mRootNode, scene);
}

void Model::scale(const glm::vec3& scale) 
{
    m_scale = scale;
}

void Model::rotate(const float angle, const glm::vec3& axis) {
    m_radians = glm::radians(angle);
    m_axis = axis;
}
void Model::translate(const glm::vec3& pos) {
    m_position = pos;
}

glm::mat4 Model::getModelMatrix() const 
{
    const auto scale = glm::scale(glm::mat4(1.0f), m_scale);
    const auto translate = glm::translate(glm::mat4(1.0f), m_position);
    const auto rotate = glm::rotate(translate, m_radians, m_axis);
    return scale * rotate;
}

void Model::deleteModel()
{
    textures_loaded.clear();
    for (auto& mesh : meshes)
    {
        mesh.deleteMesh();
    }
}

void Model::processNode(aiNode* node, const aiScene* scene)
{
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(processMesh(mesh, scene));
    }

    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene);
    }
}

Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene)
{
    std::vector<GL::Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<GL::Texture> textures;

    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        GL::Vertex vertex;
        glm::vec3 vector;

        // positions
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.position = vector;
        
        // normals
        if (mesh->HasNormals())
        {
            vector.x = mesh->mNormals[i].x;
            vector.y = mesh->mNormals[i].y;
            vector.z = mesh->mNormals[i].z;
            vertex.normal = vector;
        }

        // texture coordinates
        if (mesh->mTextureCoords[0])
        {
            glm::vec2 vec;

            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.texCoords = vec;
            
            vector.x = mesh->mTangents[i].x;
            vector.y = mesh->mTangents[i].y;
            vector.z = mesh->mTangents[i].z;
            vertex.tangent = vector;
            
            vector.x = mesh->mBitangents[i].x;
            vector.y = mesh->mBitangents[i].y;
            vector.z = mesh->mBitangents[i].z;
            vertex.bitangent = vector;
        }
        else
            vertex.texCoords = glm::vec2(0.0f, 0.0f);

        vertices.push_back(vertex);
    }

    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];

        for (unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }

    // process materials
    aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

    // 1. diffuse maps
    std::vector<GL::Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
    textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
    // 2. specular maps
    std::vector<GL::Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
    textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    // 3. normal maps
    std::vector<GL::Texture> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
    textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
    // 4. height maps
    std::vector<GL::Texture> heightMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
    textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

    // return a mesh object created from the extracted mesh data
    return Mesh(vertices, indices, textures);
}

std::vector<GL::Texture> Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName)
{
    std::vector<GL::Texture> textures;
    for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str;
        mat->GetTexture(type, i, &str);

        bool skip = false;
        for (unsigned int j = 0; j < textures_loaded.size(); j++)
        {
            if (std::strcmp(textures_loaded[j].path.data(), str.C_Str()) == 0)
            {
                textures.push_back(textures_loaded[j]);
                skip = true;
                break;
            }
        }
        if (!skip)
        {
            GL::Texture texture = ResourceManager::getInstance().loadTexture(directory, str.C_Str(), typeName);
            textures.push_back(texture);
            textures_loaded.push_back(texture);
        }
    }
    return textures;
}
```

**NOTE: I am still experimenting with a dynamic way to add directional light, point light and spot light**  
```cpp
// I will add the code here when I finish it.
```  

***
**Utility/ResourceManager.h** is the class used to load up shaders, textures and files.
```cpp
#pragma once

#include "GL/Shader.h"
#include "GL/Texture.h"

#include <string>

class ResourceManager
{
	ResourceManager() = default;
	~ResourceManager() = default;

public:
	static ResourceManager& getInstance()
	{
		static ResourceManager instance;
		return instance;
	}

	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator=(const ResourceManager&) = delete;

	GL::Shader loadShader(const std::string& filepath) const;
	GL::Texture loadTexture(const std::string& dir, const std::string& path, const std::string& type = "texture_diffuse") const;
	std::string loadFile(const std::string& filepath) const;

};
```
**Utility/ResourceManager.cpp**
```cpp
#include "ResourceManager.h"

#include <stb_image/stb_image.h>

#include <iostream>
#include <sstream>
#include <fstream>

GL::Shader ResourceManager::loadShader(const std::string& filepath) const
{
	std::string shaderSource = loadFile(filepath);

	GL::Shader::ShaderType type = GL::Shader::UNDEFINED;

	std::string ext = filepath.substr(filepath.find_first_of("."));
	if (ext == ".vs.glsl")
		type = GL::Shader::VERTEX;
	else if (ext == ".fs.glsl")
		type = GL::Shader::FRAGMENT;
	else if (ext == ".gs.glsl")
		type = GL::Shader::GEOMETRY;

	return GL::Shader(type, shaderSource);
}

GL::Texture ResourceManager::loadTexture(const std::string& dir, const std::string& path, const std::string& type) const
{
	stbi_set_flip_vertically_on_load(true);
    int width, height, nrComponents;
	unsigned char* data = stbi_load((dir + '/' + path).c_str(), &width, &height, &nrComponents, 0);
    
	if (!data)
	{
		std::cerr << "STB::ERROR::UNABLE TO LOAD TEXTURE" << std::endl;
		std::cerr << path << std::endl;
	}
	return GL::Texture(path, type, width, height, nrComponents, data);
}

std::string ResourceManager::loadFile(const std::string& filepath) const
{
	std::string data = "";

	std::ifstream file;
	file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		file.open(filepath.c_str());
		std::stringstream dataStream;
		dataStream << file.rdbuf();
		file.close();
		data = dataStream.str();
	}
	catch (std::ifstream::failure& e)
	{
		std::cerr << "ERROR::FILE_NOT_SUCCESFULLY_READ: " << filepath << std::endl << e.what() << std::endl;
	}

	
	return data;
}
```
***
And last but not least, the core opengl components.  

**GL/Vertex.h** is the basic vertex structure containing positions, texturecoords, normals etc.
```cpp
#pragma once

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#define MAX_BONE_INFLUENCE 4

namespace GL {
	struct Vertex {
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec2 texCoords;
		glm::vec3 tangent;
		glm::vec3 bitangent;

		int m_BoneIDs[MAX_BONE_INFLUENCE];
		float m_Weights[MAX_BONE_INFLUENCE];
	};
}
```

**GL/VertexArray.h** is an abstraction over the opengl vertex arrays to use them easily.

```cpp
#pragma once

#include <glad/glad.h>

namespace GL {
	class VertexArray
	{
	public:
		enum BufferType : int {
			ARRAY = GL_ARRAY_BUFFER,
			ELEMENT = GL_ELEMENT_ARRAY_BUFFER
		};

		enum DrawMode : int {
			STATIC = GL_STATIC_DRAW,
			DYNAMIC = GL_DYNAMIC_DRAW,
			STREAM = GL_STREAM_DRAW
		};

		enum AttribType : int {
			INT = GL_INT,
			FLOAT = GL_FLOAT
		};

	public:
		inline unsigned int getID() const { return m_id; }

		void create() noexcept;
		void bind() const noexcept;
		void attachBuffer(const BufferType type, const size_t size, const void* data, const DrawMode mode) noexcept;
		void enableAttribute(const unsigned int index, const int size, AttribType type, const unsigned int offset, const void* data) noexcept;
		void unbind() const noexcept;
		void deleteVAO() noexcept;

	private:
		unsigned int m_id;
	};
}
```
**GL/VertexArray.cpp**
```cpp
#include "VertexArray.h"

namespace GL {
	void VertexArray::create() noexcept
	{
		glGenVertexArrays(1, &m_id);
	}

	void VertexArray::bind() const noexcept
	{
		glBindVertexArray(m_id);
	}

	void VertexArray::attachBuffer(const BufferType type, const size_t size, const void* data, const DrawMode mode) noexcept
	{
		bind();
		unsigned int buffer;
		glGenBuffers(1, &buffer);

		glBindBuffer(type, buffer);
		glBufferData(type, size, data, mode);
	}

	void VertexArray::enableAttribute(const unsigned int index, const int size, AttribType type, const unsigned int offset, const void* data) noexcept
	{
		glEnableVertexAttribArray(index);
		glVertexAttribPointer(index, size, type, GL_FALSE, offset, data);
	}

	void VertexArray::unbind() const noexcept
	{
		glBindVertexArray(0);
	}

	void VertexArray::deleteVAO() noexcept
	{
		glDeleteVertexArrays(1, &m_id);
	}
}
```

**GL/Shader.h** is an abstraction over opengl shaders.
```cpp
#pragma once

#include <glad/glad.h>

#include <string>

namespace GL {
    class Shader
    {
    public:
        enum ShaderType : int {
            UNDEFINED = -1,
            VERTEX = GL_VERTEX_SHADER,
            FRAGMENT = GL_FRAGMENT_SHADER,
            GEOMETRY = GL_GEOMETRY_SHADER
        };

        Shader(const ShaderType type, const std::string& source);
        ~Shader();

        inline unsigned int getID() const { return m_id; }
        inline ShaderType getType() const { return m_type; }
        inline std::string getSourceCode() const { return m_source; }

        void deleteShader();

    private:
        unsigned int m_id{ 0 };
        std::string m_source;
        ShaderType m_type;
    };
}
```
**GL/Shader.cpp**
```cpp
#include "Shader.h"

#include "Utility/ResourceManager.h"

#include <iostream>

namespace GL {
	Shader::Shader(const ShaderType type, const std::string& source)
		: m_source(source), m_type(type)
	{
		m_id = glCreateShader(m_type);

		const char* src = m_source.c_str();
		glShaderSource(m_id, 1, &src, NULL);

		glCompileShader(m_id);
		int success;
		char infoLog[1024];
		glGetShaderiv(m_id, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(m_id, 1024, NULL, infoLog);
			std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << m_type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
		}
	}

	Shader::~Shader()
	{
		deleteShader();
	}

	void Shader::deleteShader()
	{
		glDeleteShader(m_id);
	}
}
```

**GL/ShaderProgram.h** is the collection of compiled Shaders. This class also has methods to set uniforms.
```cpp
#pragma once

#include <glad/glad.h>

#include <glm/glm.hpp>

#include <string>

namespace GL {
    class ShaderProgram
    {
    public:
        ShaderProgram();

        inline unsigned int getProgramID() const { return m_id; }
        void use() const;
        void unUse() const;

        void attach(unsigned int shaderID);
        void linkProgram();
        void deleteProgram();

    public:
        void setBool(const std::string& name, bool value) const;

        void setInt(const std::string& name, int value) const;

        void setFloat(const std::string& name, float value) const;

        void setVec2(const std::string& name, const glm::vec2& value) const;
        void setVec2(const std::string& name, float x, float y) const;

        void setVec3(const std::string& name, const glm::vec3& value) const;
        void setVec3(const std::string& name, float x, float y, float z) const;

        void setVec4(const std::string& name, const glm::vec4& value) const;
        void setVec4(const std::string& name, float x, float y, float z, float w);

        void setMat2(const std::string& name, const glm::mat2& mat) const;

        void setMat3(const std::string& name, const glm::mat3& mat) const;

        void setMat4(const std::string& name, const glm::mat4& mat) const;

    private:
        unsigned int m_id;
    };
}
```
**GL/ShaderProgram.cpp**
```cpp
#include "ShaderProgram.h"

#include <iostream>

namespace GL {
    ShaderProgram::ShaderProgram()
    {
        m_id = glCreateProgram();
    }

    void ShaderProgram::deleteProgram()
    {
        glDeleteProgram(m_id);
    }

    void ShaderProgram::attach(unsigned int shaderID)
    {
        glAttachShader(m_id, shaderID);
    }

    void ShaderProgram::linkProgram()
    {
        glLinkProgram(m_id);
        int success;
        char infoLog[1024];
        glGetProgramiv(m_id, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(m_id, 1024, NULL, infoLog);
            std::cerr << "ERROR::PROGRAM_LINKING_ERROR" << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }

    void ShaderProgram::use() const
    {
        glUseProgram(m_id);
    }

    void ShaderProgram::unUse() const
    {
        glUseProgram(0);
    }

    void ShaderProgram::setBool(const std::string& name, bool value) const
    {
        glUniform1i(glGetUniformLocation(m_id, name.c_str()), (int)value);
    }

    void ShaderProgram::setInt(const std::string& name, int value) const
    {
        glUniform1i(glGetUniformLocation(m_id, name.c_str()), value);
    }

    void ShaderProgram::setFloat(const std::string& name, float value) const
    {
        glUniform1f(glGetUniformLocation(m_id, name.c_str()), value);
    }

    void ShaderProgram::setVec2(const std::string& name, const glm::vec2& value) const
    {
        glUniform2fv(glGetUniformLocation(m_id, name.c_str()), 1, &value[0]);
    }
    void ShaderProgram::setVec2(const std::string& name, float x, float y) const
    {
        glUniform2f(glGetUniformLocation(m_id, name.c_str()), x, y);
    }

    void ShaderProgram::setVec3(const std::string& name, const glm::vec3& value) const
    {
        glUniform3fv(glGetUniformLocation(m_id, name.c_str()), 1, &value[0]);
    }
    void ShaderProgram::setVec3(const std::string& name, float x, float y, float z) const
    {
        glUniform3f(glGetUniformLocation(m_id, name.c_str()), x, y, z);
    }

    void ShaderProgram::setVec4(const std::string& name, const glm::vec4& value) const
    {
        glUniform4fv(glGetUniformLocation(m_id, name.c_str()), 1, &value[0]);
    }
    void ShaderProgram::setVec4(const std::string& name, float x, float y, float z, float w)
    {
        glUniform4f(glGetUniformLocation(m_id, name.c_str()), x, y, z, w);
    }

    void ShaderProgram::setMat2(const std::string& name, const glm::mat2& mat) const
    {
        glUniformMatrix2fv(glGetUniformLocation(m_id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

    void ShaderProgram::setMat3(const std::string& name, const glm::mat3& mat) const
    {
        glUniformMatrix3fv(glGetUniformLocation(m_id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

    void ShaderProgram::setMat4(const std::string& name, const glm::mat4& mat) const
    {
        glUniformMatrix4fv(glGetUniformLocation(m_id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }
}
```

**GL/Texture.h** is an abstraction over the textures. The textures are loaded using stb_image library.
```cpp
#pragma once

#include <glad/glad.h>

#include <string>

namespace GL {
    class Texture
    {
    public:
        enum Format : int {
            R = GL_RED,
            RG = GL_RG,
            RGB = GL_RGB,
            RGBA = GL_RGBA
        };

        Texture(
            const std::string& path,
            const std::string& type,
            const int width,
            const int height,
            const int bpp,
            unsigned char* pixelBuffer
        );

        std::string path;
        std::string type;

    public:
        void bind(unsigned int slot = 0) const;
        void unbind() const;
        void deleteTexture() const;
        inline int getWidth() const { return m_width; }
        inline int getHeight() const { return m_height; }

    private:
        unsigned int m_id = 0;
        int m_width, m_height, m_nrComponents;
        Format m_format;
    };
}
```
**GL/Texture.cpp**
```cpp
#include "Texture.h"

#include <stb_image/stb_image.h>

namespace GL {
    Texture::Texture(const std::string& path, const std::string& type, const int width, const int height, const int bpp, unsigned char* pixelBuffer)
        : m_width(width), m_height(height), m_nrComponents(bpp), m_format(RGBA)
    {
        this->path = path;
        this->type = type;
        glGenTextures(1, &m_id);
        switch (m_nrComponents)
        {
        case 1: m_format = Texture::R;
            break;
            //case 2: m_format = Texture::RG;
            //    break;
        case 3: m_format = Texture::RGB;
            break;
        case 4: m_format = Texture::RGBA;
            break;
        }

        glBindTexture(GL_TEXTURE_2D, m_id);
        glTexImage2D(GL_TEXTURE_2D, 0, m_format, m_width, m_height, 0, m_format, GL_UNSIGNED_BYTE, pixelBuffer);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(pixelBuffer);
    }

    void Texture::bind(unsigned int slot) const
    {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, m_id);
    }

    void Texture::unbind() const
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void Texture::deleteTexture() const
    {
        unbind();
        glDeleteTextures(1, &m_id);
    }
}
```
  
# Thank You :)
A project by [Jay Nakum](https://jaynakum.github.io/)