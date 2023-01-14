#include "Light.h"

Light::Light(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular)
	: m_ambient(ambient), m_diffuse(diffuse), m_specular(specular) {}
