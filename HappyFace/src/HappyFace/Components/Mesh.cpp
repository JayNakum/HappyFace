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
