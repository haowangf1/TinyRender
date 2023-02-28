#pragma once
#include"VertexBuffer.h"
#include"VertexBufferLayout.h"
#include<glew.h>


//�������
//����һ��VAO ������Ӧ�Ķ��㻺�����Ͷ��㲼��  ���ظ�ʹ��
class VertexArray
{
private:
	unsigned int m_VertexArrayId;
public:
	VertexArray();
	~VertexArray();
public:
	//��������������󲢰� �󶨶��㻺�� ���ö��㲼��
	void BindBuffer(VertexBuffer &vb,VertexBufferLayout &layout);
	//��������������󲢰�
	void Bind();
	void UnBind();
};