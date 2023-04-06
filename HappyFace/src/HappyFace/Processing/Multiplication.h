#pragma once

#include "Filter.h"

#include <glm/glm.hpp>

class Multiplication : public Filter
{
	glm::vec4 m_value;
public:
	Multiplication(const glm::vec4& value = {1.0f, 1.0f, 1.0f, 1.0f});
	void apply(const GL::ShaderProgram& shader) override;
};
