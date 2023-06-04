
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Texture.h"
#include "shaderClass.h"
#include "VertexArrayObject.h"
#include "VertexBufferObject.h"
#include "ElementBufferObject.h"
#include "Camera.h"

#include "Model.h"

const unsigned int width = 800;
const unsigned int height = 800;

int main()
{
	glfwInit();
	//open gl �汾�� 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow* window = glfwCreateWindow(800, 800, "GL Gems", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "���� GLFW ����ʧ��" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	//���� glad, ���� Open GL
	gladLoadGL();
	glViewport(0, 0, width, height);

	Shader shaderProgram("shaders/default.vert", "shaders/default.frag");

	//�ƹ�
	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);

	shaderProgram.Activate();
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);


	//��������
	//std::string texPath = "../Resources/flower.jpg";
	//Texture flower(texPath.c_str(), GL_TEXTURE_2D, GL_TEXTURE0);
	//flower.texUnit(shaderProgram, "tex0", 0);

	float rotate = 0.0f;
	double prevTime = glfwGetTime();
	//���� ��Ȳ���
	glEnable(GL_DEPTH_TEST);
	Camera camera(width, height,45,0.1f,100.0f, glm::vec3(0.0f, 0.0f, 2.0f));

	//ģ�ͼ��أ����ڵ㣬λ�ã����ţ�
	std::string modelPath = "../Resources/models/bunny/scene.gltf";
	//std::string modelPath = "../Resources/models/bunny/armor.gltf";
	Model model(modelPath.c_str());
	glm::mat4 pose = glm::mat4(1.0f);
	pose = glm::translate(pose, glm::vec3(0, 0.3f, 0));
	model.pose= glm::scale(pose, glm::vec3(1.0f, 1.0f, 1.0f)*3.0f);

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.1f, 0.1f, 0.13f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		//���� camera
		camera.Inputs(window);
		camera.Update();

		model.Draw(shaderProgram, camera);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	shaderProgram.Delete();

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}