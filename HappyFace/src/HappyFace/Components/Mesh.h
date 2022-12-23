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
