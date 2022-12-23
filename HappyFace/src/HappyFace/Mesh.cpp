#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<GLTexture> textures)
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
        tex.deleteTexture();
    textures.clear();
}

void Mesh::setupMesh()
{
    VAO.create();
    VAO.attachBuffer(GLVertexArray::ARRAY, vertices.size() * sizeof(Vertex), &vertices[0], GLVertexArray::STATIC);
    VAO.attachBuffer(GLVertexArray::ELEMENT, indices.size() * sizeof(unsigned int), &indices[0], GLVertexArray::STATIC);

    // vertex Positions
    VAO.enableAttribute(0, 3, GLVertexArray::FLOAT, sizeof(Vertex), (void*)0);
    // vertex normals
    VAO.enableAttribute(1, 3, GLVertexArray::FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, normal));
    // vertex texture coords
    VAO.enableAttribute(2, 2, GLVertexArray::FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));
    // vertex tangent
    VAO.enableAttribute(3, 3, GLVertexArray::FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, tangent));
    // vertex bitangent
    VAO.enableAttribute(4, 3, GLVertexArray::FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, bitangent));
    // ids
    VAO.enableAttribute(5, 4, GLVertexArray::INT, sizeof(Vertex), (void*)offsetof(Vertex, m_BoneIDs));
    // weights
    VAO.enableAttribute(6, 4, GLVertexArray::FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, m_Weights));

    VAO.unbind();
}
