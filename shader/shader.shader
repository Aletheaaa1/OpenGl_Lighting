#shader vertex
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 2) in vec2 aTexture;

out vec2 TextCoord;

uniform mat4 moduleMat;
uniform mat4 viewMat;
uniform mat4 projMat;

void main()
{
	gl_Positon = Properties * viewMat * moduleMat * vec4(aPos, 1.0f);
	TextCoord = aTexture;
}

#shader fragment
#version 330 core

in vec2 TextCoord;

out vec4  fragColor;

uniform sampler2D ourTexture;
uniform sampler2D ourFace;
void main()
{
	fragColor = mix(texture(ourTexture, TextCoord), texture(ourFace, TextCoord), 0.3f);
}