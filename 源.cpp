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

#pragma region Data
float vertices[] = {
	-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, //
	0.5f,  -0.5f, -0.5f, 1.0f, 0.0f, //
	0.5f,  0.5f,  -0.5f, 1.0f, 1.0f, //
	0.5f,  0.5f,  -0.5f, 1.0f, 1.0f, //
	-0.5f, 0.5f,  -0.5f, 0.0f, 1.0f, //
	-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, //

	-0.5f, -0.5f, 0.5f,  0.0f, 0.0f, //
	0.5f,  -0.5f, 0.5f,  1.0f, 0.0f, //
	0.5f,  0.5f,  0.5f,  1.0f, 1.0f, //
	0.5f,  0.5f,  0.5f,  1.0f, 1.0f, //
	-0.5f, 0.5f,  0.5f,  0.0f, 1.0f, //
	-0.5f, -0.5f, 0.5f,  0.0f, 0.0f, //

	-0.5f, 0.5f,  0.5f,  1.0f, 0.0f, //
	-0.5f, 0.5f,  -0.5f, 1.0f, 1.0f, //
	-0.5f, -0.5f, -0.5f, 0.0f, 1.0f, //
	-0.5f, -0.5f, -0.5f, 0.0f, 1.0f, //
	-0.5f, -0.5f, 0.5f,  0.0f, 0.0f, //
	-0.5f, 0.5f,  0.5f,  1.0f, 0.0f, //

	0.5f,  0.5f,  0.5f,  1.0f, 0.0f, //
	0.5f,  0.5f,  -0.5f, 1.0f, 1.0f, //
	0.5f,  -0.5f, -0.5f, 0.0f, 1.0f, //
	0.5f,  -0.5f, -0.5f, 0.0f, 1.0f, //
	0.5f,  -0.5f, 0.5f,  0.0f, 0.0f, //
	0.5f,  0.5f,  0.5f,  1.0f, 0.0f, //

	-0.5f, -0.5f, -0.5f, 0.0f, 1.0f, //
	0.5f,  -0.5f, -0.5f, 1.0f, 1.0f, //
	0.5f,  -0.5f, 0.5f,  1.0f, 0.0f, //
	0.5f,  -0.5f, 0.5f,  1.0f, 0.0f, //
	-0.5f, -0.5f, 0.5f,  0.0f, 0.0f, //
	-0.5f, -0.5f, -0.5f, 0.0f, 1.0f, //

	-0.5f, 0.5f,  -0.5f, 0.0f, 1.0f, //
	0.5f,  0.5f,  -0.5f, 1.0f, 1.0f, //
	0.5f,  0.5f,  0.5f,  1.0f, 0.0f, //
	0.5f,  0.5f,  0.5f,  1.0f, 0.0f, //
	-0.5f, 0.5f,  0.5f,  0.0f, 0.0f, //
	-0.5f, 0.5f,  -0.5f, 0.0f, 1.0f  //
};
unsigned int index[] = {
	0, 1, 2, //
	2, 3, 0  //
};

glm::vec3 cube_positions[] = { glm::vec3(0.0f, 0.0f, 0.0f),    glm::vec3(2.0f, 5.0f, -15.0f),
							  glm::vec3(-1.5f, -2.2f, -2.5f), glm::vec3(-3.8f, -2.0f, -12.3f),
							  glm::vec3(2.4f, -0.4f, -3.5f),  glm::vec3(-1.7f, 3.0f, -7.5f),
							  glm::vec3(1.3f, -2.0f, -2.5f),  glm::vec3(1.5f, 2.0f, -2.5f),
							  glm::vec3(1.5f, 0.2f, -1.5f),   glm::vec3(-1.3f, 1.0f, -1.5f) };
#pragma endregion

Camera camera(glm::vec3(0, 0, 5.0f), 0.0f, 0.0f, glm::vec3(0, 1.0f, 0));

#pragma region Moving
void ProcessInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		camera.speedZ = -0.01f;
	}
	else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		camera.speedZ = 0.01f;
	}
	else
	{
		camera.speedZ = 0.0f;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		camera.speedX = -0.01f;
	}
	else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		camera.speedX = 0.01f;
	}
	else
	{
		camera.speedX = 0.0f;
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
#pragma endregion

int main()
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
	VertexArrayObject vao;
	vao.AddBuffer(0, 3, GL_FLOAT, false, 5 * sizeof(float), 0);
	vao.AddBuffer(2, 2, GL_FLOAT, false, 5 * sizeof(float), (3 * sizeof(float)));

	Shader shader("./shader/location.shader");

	Texture texture_A("./container2.png", GL_RGBA);
	Texture texture_B("./awesomeface.png", GL_RGBA);

	glm::mat4 moduleMat = glm::mat4(1.0f);
	glm::mat4 viewMat = glm::mat4(1.0f);
	glm::mat4 projMat = glm::mat4(1.0f);
	projMat = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

	vao.Unbind();
	vbo.Unbind();

	//texture_A.Unbind();
	//texture_B.Unbind();
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		ProcessInput(window);

		vao.Bind();
		vbo.Bind();
		texture_A.Usetexture(GL_TEXTURE0);
		texture_A.Bind();
		texture_B.Usetexture(GL_TEXTURE1);
		texture_B.Bind();
		shader.SetUniform1i("ourTexture", 0);
		shader.SetUniform1i("ourFace", 1);
		// glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices));
		for (int i = 0; i < std::size(cube_positions); i++)
		{
			moduleMat = glm::mat4(1.0f);
			moduleMat = glm::translate(moduleMat, cube_positions[i]);
			viewMat = camera.GetViewMatrix();

			shader.SetUniformMat4("moduleMat", glm::value_ptr(moduleMat));
			shader.SetUniformMat4("viewMat", glm::value_ptr(viewMat));
			shader.SetUniformMat4("projMat", glm::value_ptr(projMat));
			shader.Bind();
			glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices));
		}

		camera.UpdateCameraPosition();

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}