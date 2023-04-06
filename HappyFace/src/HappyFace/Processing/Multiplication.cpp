#include "Multiplication.h"

Multiplication::Multiplication(const glm::vec4& value)
	: m_value(value)
{
	shader = "resources/shaders/processing/multiply.fs.glsl";
}

void Multiplication::apply(const GL::ShaderProgram& shader)
{
	shader.setVec4("mul_value", m_value);
}
