#pragma once

class Material
{
private:
	float* m_ambient;
	float* m_diffuse;
	unsigned int m_material_diffuse;
	float* m_specular;
	float m_shininess;

public:
	Material(float* ambient, float* diffuse, float* specular, float shininess);
	Material(float* ambient, unsigned int diffuse, float* specular, float shininess);

	float* GetAmbient();
	float* GetDiffuse();
	float* GetSpecular();
	float GetShininess();
	unsigned int GetMaterialDiffuse();
};