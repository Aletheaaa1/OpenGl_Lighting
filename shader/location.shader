#shader vertex
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 2) in vec2 aTexture;

out vec4 vertexColor;
out vec2 TextCoord;

uniform mat4 trans;
uniform mat4 moduleMat;
uniform mat4 viewMat;
uniform mat4 projMat;
void main()
{
	gl_Position = projMat * viewMat * moduleMat * vec4(aPos, 1);
	
	TextCoord = aTexture;
}

#shader fragment
#version 330 core

in vec2 TextCoord;
in vec4 vertexColor;
out vec4 FragColor;

uniform sampler2D ourTexture;
uniform sampler2D ourFace;
void main()
{
	FragColor = mix(texture(ourTexture, TextCoord) ,  texture(ourFace, TextCoord), 0.3f);
}