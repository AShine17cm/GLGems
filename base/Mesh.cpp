#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices, std::vector<Texture>& textures)
{
	this->vertices = vertices;
	this->indices = indices;
	this->textures = textures;

	vertexAO.Bind();
	VertexBufferObject vertexBO(vertices);
	ElementBufferObject elemBO(indices);

	//顶点布局 pos+normal+color+uv
	vertexAO.LinkAttrib(vertexBO, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
	vertexAO.LinkAttrib(vertexBO, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float)));
	vertexAO.LinkAttrib(vertexBO, 2, 3, GL_FLOAT, sizeof(Vertex), (void*)(6 * sizeof(float)));
	vertexAO.LinkAttrib(vertexBO, 3, 2, GL_FLOAT, sizeof(Vertex), (void*)(9 * sizeof(float)));

	vertexAO.Unbind();
	vertexBO.Unbind();
	elemBO.Unbind();
}
void Mesh::Draw
(
	Shader& shader,
	Camera& camera,
	glm::mat4 model
)
{
	shader.Activate();
	vertexAO.Bind();
	//纹理数量
	unsigned int numDiff = 0;
	unsigned int numSpec = 0;
	for (unsigned int i = 0; i < textures.size(); i++)
	{
		std::string num;
		std::string type = textures[i].type;

		if (type == "diffuse")
		{
			num = std::to_string(numDiff++);
		}
		else if (type == "specular")
		{
			num = std::to_string(numSpec++);
		}
		//将 纹理名称和一个ID 关联 ?
		textures[i].texUnit(shader, (type + num).c_str(), i);
		textures[i].Bind();
	}

	//mvp
	glm::mat4 vp = camera.vp;

	//相机位置 高光
	glUniform3f(glGetUniformLocation(shader.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "vp"), 1, GL_FALSE, glm::value_ptr(vp));
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));

	//画 Mesh
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}