#include "Renderer.h"

#include "Input.h"
#include "ResourceManager.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

void Renderer::render(const Mesh& mesh)
{
    static auto& meshShader = m_shaderCache.at("mesh");

    mesh.getTexture().bind();
    meshShader.use();
    meshShader.setInt("texture1", 0);
    mesh.getVAO().bind();
    glDrawElements(GL_TRIANGLES, mesh.getIndicesCount(), GL_UNSIGNED_INT, 0);
    mesh.getVAO().unbind();
    mesh.getTexture().unbind();
}

void Renderer::update()
{
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

    compileShaders();
}

void Renderer::defaultGLSettings() const
{
    glClearColor(0.07f, 0.07f, 0.07f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    /*
    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    */
    glViewport(0, 0, (int)m_viewportWidth, (int)m_viewportHeight);
}

void Renderer::compileShaders()
{
    GLShaderProgram mesh;
    GLShader vertexShader = ResourceManager::getInstance().loadShader("res/shaders/test_shader.vs.glsl");
    GLShader fragmentShader = ResourceManager::getInstance().loadShader("res/shaders/test_shader.fs.glsl");

    mesh.attach(vertexShader.getID());
    mesh.attach(fragmentShader.getID());
    mesh.linkProgram();

    vertexShader.deleteShader();
    fragmentShader.deleteShader();

    m_shaderCache.insert({"mesh", mesh});
}

void Renderer::shutdown()
{
    for (auto& program : m_shaderCache)
    {
        program.second.deleteProgram();
    }
    m_shaderCache.clear();
}
