#shader vertex 
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 normal;
layout (location = 3) in vec2 aUVCoord;

uniform mat4 moduleMat;
uniform mat4 viewMat;
uniform mat4 projMat;

out vec3 Normal;
out vec3 FragPos;
out vec2 UVCoord;

void main()
{
    gl_Position = projMat * viewMat * moduleMat * vec4(aPos, 1.0);
    FragPos = (moduleMat * vec4(aPos.xyz, 1.0)).xyz;
    Normal = normalize(mat3(transpose(inverse(moduleMat))) * normal);    
    UVCoord = aUVCoord;
}

#shader fragment
#version 330 core

struct Material
{
    vec3 ambient;
    sampler2D diffuse;
    vec3 specular;
    float shininess;
};

in vec3 Normal;
in vec3 FragPos;
in vec2 UVCoord;

uniform Material material;
uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 ambientColor;
uniform vec3 objectColor;
uniform vec3 cameraPos;


out vec4 color;

void main()
{
    vec3 lightDirection = normalize(lightPos - FragPos);
    vec3 reflectVec = reflect(-lightDirection, Normal);
    vec3 cameraVec = normalize(cameraPos - FragPos);

    float specularStrength = 0.1f;
    float specularRate = pow(max(dot(cameraVec, reflectVec), 0.0), material.shininess);
    vec3 specularColor = specularRate * lightColor;

    vec3 diffuseColor = max(dot(lightDirection, Normal), 0) * lightColor;

    vec3 ambient = ambientColor * texture(material.diffuse, UVCoord).rgb;

    vec3 diffuse = texture(material.diffuse, UVCoord).rgb * diffuseColor;
    vec3 specular = material.specular * specularColor;

    color = vec4( (ambient + diffuse + specular) * objectColor, 1.0);


    // color = texture(Texture, UVCoord);
}