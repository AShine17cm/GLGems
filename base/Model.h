#ifndef MODEL_CLASS_H
#define MODEL_CLASS_H

#include<json/json.h>
#include"Mesh.h"

using json = nlohmann::json;

class Model
{
public:
	Model(const char* file);
	void Draw(Shader& shader, Camera& camera);

	glm::mat4 pose=glm::mat4(1.0f);	//平移，缩放，旋转
private:
	const char* file;
	std::vector<unsigned char> data;
	json JSON;

	//一堆 submesh
	std::vector<Mesh> meshes;
	std::vector<glm::vec3> translationsMeshes;
	std::vector<glm::quat> rotationsMeshes;
	std::vector<glm::vec3> scalesMeshes;
	std::vector<glm::mat4> matricesMeshes;

	//放置多次加载纹理
	std::vector<std::string> loadedTexName;
	std::vector<Texture> loadedTex;

	//加载 submesh
	void loadMesh(unsigned int indMesh);
	//遍历 节点层级
	void traverseNode(unsigned int nextNode, glm::mat4 matrix = glm::mat4(1.0f));

	//读二进制数据
	std::vector<unsigned char> getData();
	//获取 顶点数据，纹理
	std::vector<float> getFloats(json accessor);
	std::vector<GLuint> getIndices(json accessor);
	std::vector<Texture> getTextures();

	//将顶点的不同属性数据  组合成一个顶点
	std::vector<Vertex> assembleVertices
	(
		std::vector<glm::vec3> positions,
		std::vector<glm::vec3> normals,
		std::vector<glm::vec2> texUVs
	);

	std::vector<glm::vec2> groupFloatsVec2(std::vector<float> floatVec);
	std::vector<glm::vec3> groupFloatsVec3(std::vector<float> floatVec);
	std::vector<glm::vec4> groupFloatsVec4(std::vector<float> floatVec);
};


#endif
