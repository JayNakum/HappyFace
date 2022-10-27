#pragma once

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

struct Vertex {
	Vertex() = default;

	Vertex(const glm::vec3& position, const glm::vec2& texcoords)
		: Position(position), TexCoords(texcoords) {}

	Vertex(const glm::vec3& position, const glm::vec2& texcoords, const glm::vec3& normal)
		: Position(position), TexCoords(texcoords), Normal(normal) {}

	Vertex(const glm::vec3& position, const glm::vec2& texcoords, const glm::vec3& normal, const glm::vec3& tangent)
		: Position(position), TexCoords(texcoords), Normal(normal), Tangent(tangent) {}

	glm::vec3 Position;
	glm::vec2 TexCoords;
	glm::vec3 Normal;
	glm::vec3 Tangent;
};
