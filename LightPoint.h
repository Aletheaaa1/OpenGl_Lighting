#pragma once
#include <glm/glm.hpp>
#include <iostream>

class LightPoint
{
public:
	glm::vec3 m_light_position;
	glm::vec3 m_light_color;
	glm::vec3 m_light_direction;
	glm::vec3 m_angles;

	float constant = 1.0f;
	float linear = 0.09f;
	float quadratic = 0.032f;

public:
	LightPoint(glm::vec3 light_position, glm::vec3 angles, glm::vec3 light_color = glm::vec3(5.0f, 2.0f, 2.0f));
};