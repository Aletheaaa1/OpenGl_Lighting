#shader vertex
#version 330 core
layout (location = 0) in vec3 aPos;

uniform mat4 moduleMat;
uniform mat4 viewMat;
uniform mat4 projMat;

void main()
{
    gl_Position = projMat * viewMat * moduleMat * vec4(aPos, 1);
    // gl_Position =vec4(aPos, 1);
}

#shader fragment
#version 330 core
out vec4 color;

uniform vec3  objectColor;
uniform vec3 lightColor;
void main()
{
    color = vec4(objectColor * lightColor, 0.0f);
    // color = vec4(0.5f, 0.5f, 0.5f, 1.0f);
}