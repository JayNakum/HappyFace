#pragma once

#include "GL/Vertex.h"
#include "GL/VertexArray.h"
#include "GL/Texture.h"

#include "Utility/ResourceManager.h"

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

    GL::Texture filter = ResourceManager::getInstance().loadTexture("resources/textures", "wall.jpg", "filter");

private:
    void setupMesh();
};
