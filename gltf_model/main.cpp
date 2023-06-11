
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
#include "constants.h"

const unsigned int width = 1200;
const unsigned int height = 800;

int main()
{
	glfwInit();
	//open gl 版本号 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow* window = glfwCreateWindow(width, height, "GL Gems", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "创建 GLFW 窗口失败" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	//加载 glad, 配置 Open GL
	gladLoadGL();
	glViewport(0, 0, width, height);

	Shader shaderProgram("shaders/basic.vert", "shaders/color.frag");
	//Shader shaderProgram("shaders/default.vert", "shaders/color.frag");

	//灯光
	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);

	shaderProgram.Activate();
	glUniform3f(glGetUniformLocation(shaderProgram.ID, nm_lightDir), lightPos.x, lightPos.y, lightPos.z);
	glUniform4f(glGetUniformLocation(shaderProgram.ID, nm_lightColor), lightColor.x, lightColor.y, lightColor.z, lightColor.w);

	//加载纹理
	//std::string texPath = "../Resources/flower.jpg";
	//Texture flower(texPath.c_str(), GL_TEXTURE_2D, GL_TEXTURE0);
	//flower.texUnit(shaderProgram, "tex0", 0);

	float rotate = 0.0f;
	double prevTime = glfwGetTime();
	//开启 深度测试
	glEnable(GL_DEPTH_TEST);
	Camera camera(width, height,45,0.1f,100.0f, glm::vec3(0.0f, 0.0f, 2.0f));

	//模型加载，根节点，位置，缩放，
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
		//更新 camera
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