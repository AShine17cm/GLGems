#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H

//#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>

class Camera
{
public:

	glm::vec3 Position;
	glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);//Y 轴朝上， vulkan是Y轴朝下

	glm::mat4 proj;
	glm::mat4 view;
	glm::mat4 vp;

	bool firstClick = true;
	//屏幕的宽高
	int width;
	int height;
	float fov;
	float near, far;

	float speed = 0.1f;
	float sensitivity = 100.0f;

	Camera(int width, int height,float fov,float near,float far, glm::vec3 position);
	//更新矩阵
	void Update( );
	void Inputs(GLFWwindow* window);
};
#endif
