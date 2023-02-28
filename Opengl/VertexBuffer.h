#pragma once
#include"ErrLog.h"
#include<glew.h>
class VertexBuffer
{
private:
	unsigned int m_VertexBufferId;//buffer unique id in shader
public:
	VertexBuffer(const void* datas,int size);
	~VertexBuffer();
public:
	void Bind();
	void UnBind();
};