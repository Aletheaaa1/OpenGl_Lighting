#shader vertex
#version 330 core
layout (location = 2) in vec3 aPos;

uniform mat4 projMat;
uniform mat4 moduleMat;
uniform mat4 viewMat;

void main()
{
    gl_Position = projMat * viewMat * moduleMat * vec4(aPos, 1.0);   
}

#shader fragment
#version 330 core

uniform vec3 lightColor;

out vec4 color;
void main()
{
    color = vec4(lightColor, 1.0);   
}