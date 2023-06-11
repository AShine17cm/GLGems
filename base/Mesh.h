#ifndef MESH_CLASS_H
#define MESH_CLASS_H

#include<string>

#include"VertexArrayObject.h"
#include"ElementBufferObject.h"
#include"Camera.h"
#include"Texture.h"

#include "constants.h"
class Mesh
{
public:
	std::vector <Vertex> vertices;
	std::vector <GLuint> indices;
	std::vector <Texture> textures;

	VertexArrayObject vertexAO;
	Mesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices, std::vector<Texture>& textures);

	void Draw
	(
		Shader& shader,
		Camera& camera,
		glm::mat4 model	=	glm::mat4(1.0f)
	);


};


#endif
