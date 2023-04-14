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

    for (auto& model : scene.getModels())
    {
        modelShader.setMat4("model", model.getModelMatrix());
        renderModel(model, modelShader);
        model.update();
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

    unsigned int i = 0;
    for (; i < mesh.textures.size(); i++)
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
    
    glActiveTexture(GL_TEXTURE0 + i);
    shader.setInt("texture_filter", i);
    mesh.filter.bind(i);

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
