#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include<glad/glad.h>
#include<vector>

class ElementBufferObject
{
public:
	GLuint ID;
	//���첢��ʼ�� ������
	ElementBufferObject(std::vector<GLuint>& indices);
	ElementBufferObject(GLuint* indices,GLsizeiptr size);

	void Bind();
	void Unbind();
	void Delete();
};

#endif
