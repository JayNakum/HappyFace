#include "Renderer.h"

#include <iostream>
#include "Input.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>


void Renderer::render(const Entity& entity)
{
    glBindTexture(GL_TEXTURE_2D, entity.getTextureID());
    entity.getShader().use();
    entity.getVAO().bind();
    glDrawElements(GL_TRIANGLES, entity.getIndices().size(), GL_UNSIGNED_INT, 0);
    entity.getVAO().unbind();
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

void Renderer::init(const unsigned int viewportWidth, const unsigned int viewportHeight)
{
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        std::abort();
    }

    m_viewportWidth = viewportWidth;
    m_viewportHeight = viewportHeight;

    glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
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
