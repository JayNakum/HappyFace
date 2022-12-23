#pragma once

#include "Vertex.h"
#include "GLVertexArray.h"
#include "GLTexture.h"

#include <string>
#include <vector>

class Mesh
{
public:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<GLTexture> textures;
    GLVertexArray VAO;

    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<GLTexture> textures);
    void deleteMesh();
private:
    void setupMesh();
};
