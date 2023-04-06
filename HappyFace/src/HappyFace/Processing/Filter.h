#pragma once

#include "GL/ShaderProgram.h"

#include <string>

class Filter
{
public:
	std::string shader;
	virtual void apply(const GL::ShaderProgram& shader) {}
};
