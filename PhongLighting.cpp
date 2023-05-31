#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

#include "VertexBufferObject.h"
#include "VertexArrayObject.h"
#include "Shader.h"
#include "Texture.h"
#include "Camera.h"
//#include "Material.h"

float vertices[] = {
	-0.5f, -0.5f, -0.5f, 0.0f,  0.0f,  -1.0f, //
	0.5f,  -0.5f, -0.5f, 0.0f,  0.0f,  -1.0f, //
	0.5f,  0.5f,  -0.5f, 0.0f,  0.0f,  -1.0f, //
	0.5f,  0.5f,  -0.5f, 0.0f,  0.0f,  -1.0f, //
	-0.5f, 0.5f,  -0.5f, 0.0f,  0.0f,  -1.0f, //
	-0.5f, -0.5f, -0.5f, 0.0f,  0.0f,  -1.0f, //

	-0.5f, -0.5f, 0.5f,  0.0f,  0.0f,  1.0f, //
	0.5f,  -0.5f, 0.5f,  0.0f,  0.0f,  1.0f, //
	0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f, //
	0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f, //
	-0.5f, 0.5f,  0.5f,  0.0f,  0.0f,  1.0f, //
	-0.5f, -0.5f, 0.5f,  0.0f,  0.0f,  1.0f, //

	-0.5f, 0.5f,  0.5f,  -1.0f, 0.0f,  0.0f, //
	-0.5f, 0.5f,  -0.5f, -1.0f, 0.0f,  0.0f, //
	-0.5f, -0.5f, -0.5f, -1.0f, 0.0f,  0.0f, //
	-0.5f, -0.5f, -0.5f, -1.0f, 0.0f,  0.0f, //
	-0.5f, -0.5f, 0.5f,  -1.0f, 0.0f,  0.0f, //
	-0.5f, 0.5f,  0.5f,  -1.0f, 0.0f,  0.0f, //

	0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f, //
	0.5f,  0.5f,  -0.5f, 1.0f,  0.0f,  0.0f, //
	0.5f,  -0.5f, -0.5f, 1.0f,  0.0f,  0.0f, //
	0.5f,  -0.5f, -0.5f, 1.0f,  0.0f,  0.0f, //
	0.5f,  -0.5f, 0.5f,  1.0f,  0.0f,  0.0f, //
	0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f, //

	-0.5f, -0.5f, -0.5f, 0.0f,  -1.0f, 0.0f, //
	0.5f,  -0.5f, -0.5f, 0.0f,  -1.0f, 0.0f, //
	0.5f,  -0.5f, 0.5f,  0.0f,  -1.0f, 0.0f, //
	0.5f,  -0.5f, 0.5f,  0.0f,  -1.0f, 0.0f, //
	-0.5f, -0.5f, 0.5f,  0.0f,  -1.0f, 0.0f, //
	-0.5f, -0.5f, -0.5f, 0.0f,  -1.0f, 0.0f, //

	-0.5f, 0.5f,  -0.5f, 0.0f,  1.0f,  0.0f, //
	0.5f,  0.5f,  -0.5f, 0.0f,  1.0f,  0.0f, //
	0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, //
	0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, //
	-0.5f, 0.5f,  0.5f,  0.0f,  1.0f,  0.0f, //
	-0.5f, 0.5f,  -0.5f, 0.0f,  1.0f,  0.0f  //
};
glm::vec3 cube_positions[] = {
	glm::vec3(0.0f, 0.0f, 0.0f),     //
	glm::vec3(2.0f, 5.0f, -15.0f),   //
	glm::vec3(-1.5f, -2.2f, -2.5f),  //
	glm::vec3(-3.8f, -2.0f, -12.3f), //
	glm::vec3(2.4f, -0.4f, -3.5f),   //
	glm::vec3(-1.7f, 3.0f, -7.5f),   //
	glm::vec3(1.3f, -2.0f, -2.5f),   //
	glm::vec3(1.5f, 2.0f, -2.5f),    //
	glm::vec3(1.5f, 0.2f, -1.5f),    //
	glm::vec3(-1.3f, 1.0f, -1.5f)    //
};

Camera camera(glm::vec3(0, 0, 5.0f), 5.0f, 0.0f, glm::vec3(0, 1.0f, 0));

void ProcessInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		camera.speedZ = -0.03f;
	}
	else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		camera.speedZ = 0.03f;
	}
	else
	{
		camera.speedZ = 0.0f;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		camera.speedX = -0.03f;
	}
	else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		camera.speedX = 0.03f;
	}
	else
	{
		camera.speedX = 0.0f;
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		camera.speedY = 0.03f;
	}
	else if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
	{
		camera.speedY = -0.03f;
	}
	else
	{
		camera.speedY = 0.0f;
	}
}

float x_last, y_last;
bool first_mouse = true;
void MouseCallback(GLFWwindow* window, double x_pos, double y_pos)
{
	if (first_mouse == true)
	{
		x_last = x_pos;
		y_last = y_pos;
		first_mouse = false;
	}

	float x_offset = x_pos - x_last;
	float y_offset = y_pos - y_last;

	x_last = x_pos;
	y_last = y_pos;

	camera.UpdateCameraView(x_offset, y_offset);
	camera.GetViewMatrix();
}

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(800, 600, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwWindowHint(GLFW_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, MouseCallback);

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	VertexBufferObject vbo(vertices, sizeof(vertices));

	vbo.Bind();
	VertexArrayObject vao;
	vao.AddBuffer(0, 3, GL_FLOAT, false, 6 * sizeof(float), 0);
	vao.AddBuffer(1, 3, GL_FLOAT, false, 6 * sizeof(float), 3 * sizeof(float));

	VertexArrayObject lighting_vao;
	lighting_vao.AddBuffer(2, 3, GL_FLOAT, false, 6 * sizeof(float), 0);

	Shader shader("./shader/phongLighting.shader");
	Shader lighting_shdaer("./shader/lightingCube.shader");

	// Camera
	glm::mat4 module_mat = glm::mat4(1.0f);
	glm::mat4 view_mat = glm::mat4(1.0f);
	glm::mat4 project_mat = glm::mat4(1.0f);
	project_mat = glm::perspective(45.0f, 800.0f / 600.0f, 0.1f, 100.0f);

	// Material
	float material_ambient[] = { 0.1745f, 0.01175f, 0.01175f };
	float material_diffuse[] = { 0.61424f, 0.04136f, 0.04136f };
	float material_speculatr[] = { 0.727811f, 0.626959f, 0.626959f };
	float material_shininess = 32.0f;
	Material material(material_ambient, material_diffuse, material_speculatr, material_shininess);
	// std::cout << material.GetShininess();

	vbo.Unbind();
	lighting_vao.Unbind();
	vao.Unbind();

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		camera.UpdateCameraPosition();

		/* Render here */
		glEnable(GL_DEPTH_TEST);
		// glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		ProcessInput(window);

		vbo.Bind();

		float object_color[3] = { 1.0f, 0.5f, 0.3f };
		float ambient_color[3] = { 0.5f, 0.5f, 0.5f };
		float light_color[3] = { 1.0f, 1.0f, 1.0f };
		float light_position[3] = { 10.0f, 10.0f, -5.0f };

		light_position[0] = 1.0f + sin(glfwGetTime()) * 6.0f;
		light_position[1] = sin(glfwGetTime() / 2.0f) * 3.0f;

		view_mat = camera.GetViewMatrix();
		float camera_position[3] = { camera.position.x, camera.position.y, camera.position.z };
		for (int i = 0; i < 10; i++)
		{
			module_mat = glm::mat4(1.0f);
			module_mat = glm::translate(module_mat, cube_positions[i]);

			vao.Bind();
			shader.Bind();

            // object_color[0] = sin(glfwGetTime());
			shader.SetUniform3f("objectColor", object_color);
			shader.SetUniform3f("ambientColor", ambient_color);
			shader.SetUniform3f("lightPos", light_position);
			shader.SetUniform3f("lightColor", light_color);
			shader.SetUniform3f("cameraPos", camera_position);

			// Material
			shader.SetUniformMateria("material", material);

			shader.SetUniformMat4("moduleMat", glm::value_ptr(module_mat));
			shader.SetUniformMat4("viewMat", glm::value_ptr(view_mat));
			shader.SetUniformMat4("projMat", glm::value_ptr(project_mat));

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		lighting_vao.Bind();
		lighting_shdaer.Bind();

		module_mat = glm::mat4(1.0f);
		module_mat = glm::translate(module_mat, glm::vec3(light_position[0], light_position[1], light_position[2]));
		module_mat = glm::scale(module_mat, glm::vec3(0.25f, 0.25f, 0.25f));
		lighting_shdaer.SetUniformMat4("moduleMat", module_mat);
		lighting_shdaer.SetUniformMat4("viewMat", view_mat);
		lighting_shdaer.SetUniformMat4("projMat", project_mat);
		lighting_shdaer.SetUniform3f("lightColor", light_color);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}