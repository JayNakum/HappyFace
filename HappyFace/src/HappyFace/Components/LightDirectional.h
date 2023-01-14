#pragma once

#include "Light.h"

#include <glm/vec3.hpp>

class DirectionalLight : public Light
{
public:
	DirectionalLight(glm::vec3 direction, glm::vec3 ambient = { 0.05f, 0.05f, 0.05f }, glm::vec3 diffuse = { 1.0f, 1.0f, 1.0f }, glm::vec3 specular = { 1.0f, 1.0f, 1.0f });
private:
	glm::vec3 m_direction;
};