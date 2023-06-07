#pragma once
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>

class LightSpot
{
public:
    glm::vec3 m_light_position;
    glm::vec3 m_light_color;
    glm::vec3 m_angles;
    glm::vec3 m_light_direction;

    float m_cosPhi = 0.9;
public:
    LightSpot(glm::vec3 light_position, glm::vec3 angles, glm::vec3 light_color = glm::vec3(2.0f, 2.0f, 2.0f));

    void UpdataDirection();
};
