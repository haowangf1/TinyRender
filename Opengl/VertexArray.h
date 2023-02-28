#pragma once
#include"VertexBuffer.h"
#include"VertexBufferLayout.h"
#include<glew.h>


//类的意义
//创建一个VAO 并绑定相应的顶点缓冲区和顶点布局  以重复使用
class VertexArray
{
private:
	unsigned int m_VertexArrayId;
public:
	VertexArray();
	~VertexArray();
public:
	//创建顶点数组对象并绑定 绑定顶点缓冲 设置顶点布局
	void BindBuffer(VertexBuffer &vb,VertexBufferLayout &layout);
	//创建顶点数组对象并绑定
	void Bind();
	void UnBind();
};