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

	glm::mat4 pose=glm::mat4(1.0f);	//ƽ�ƣ����ţ���ת
private:
	const char* file;
	std::vector<unsigned char> data;
	json JSON;

	//һ�� submesh
	std::vector<Mesh> meshes;
	std::vector<glm::vec3> translationsMeshes;
	std::vector<glm::quat> rotationsMeshes;
	std::vector<glm::vec3> scalesMeshes;
	std::vector<glm::mat4> matricesMeshes;

	//���ö�μ�������
	std::vector<std::string> loadedTexName;
	std::vector<Texture> loadedTex;

	//���� submesh
	void loadMesh(unsigned int indMesh);
	//���� �ڵ�㼶
	void traverseNode(unsigned int nextNode, glm::mat4 matrix = glm::mat4(1.0f));

	//������������
	std::vector<unsigned char> getData();
	//��ȡ �������ݣ�����
	std::vector<float> getFloats(json accessor);
	std::vector<GLuint> getIndices(json accessor);
	std::vector<Texture> getTextures();

	//������Ĳ�ͬ��������  ��ϳ�һ������
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