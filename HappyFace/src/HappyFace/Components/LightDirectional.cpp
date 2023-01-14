#include "LightDirectional.h"

DirectionalLight::DirectionalLight(glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular)
	: Light(ambient, diffuse, specular), m_direction(direction) {}
