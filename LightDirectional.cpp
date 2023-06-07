#include "LightDirectional.h"

LightDirectional::LightDirectional(glm::vec3 light_position, glm::vec3 angles, glm::vec3 light_color)
    : m_light_position(light_position), m_angles(angles), m_light_color(light_color)
{
    UpdateDirection();
}

void LightDirectional::UpdateDirection()
{
    m_light_direction = glm::vec3(0.0, 0.0, 1.0f);
    m_light_direction = glm::rotateX(m_light_direction, m_angles.x);
    m_light_direction = glm::rotateY(m_light_direction, m_angles.y);
    m_light_direction = glm::rotateZ(m_light_direction, m_angles.z);
    // std::cout << m_light_direction.x << " " << m_light_direction.y << " " << m_light_direction.z << std::endl;
    m_light_direction *= -1;
}
