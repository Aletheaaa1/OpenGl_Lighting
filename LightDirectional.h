#pragma once
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>

class LightDirectional
{
  public:
    glm::vec3 m_light_color;
    glm::vec3 m_light_direction = glm::vec3(0.0f, 0.0f, 1.0f);
    glm::vec3 m_light_position;
    glm::vec3 m_angles;

  public:
    LightDirectional(glm::vec3 light_position, glm::vec3 angles, glm::vec3 light_color = glm::vec3(2.0f, 2.0f, 2.0f));

    void UpdateDirection();
};
