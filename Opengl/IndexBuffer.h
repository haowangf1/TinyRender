#pragma once
#include "render.h"

class IndexBuffer
{
public:
	IndexBuffer(const void* datas,int size);
	~IndexBuffer();
private:
	unsigned int m_indexBufferId;//buffer unique id in shader
public:
	void Bind();
	void UnBind();
};