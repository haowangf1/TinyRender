#include"VertexBuffer.h"

VertexBuffer::VertexBuffer(const void* datas, int size)
{
	GLCALL(glGenBuffers(1, &m_VertexBufferId))
	GLCALL(glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferId))
	GLCALL(glBufferData(GL_ARRAY_BUFFER, size, datas, GL_STATIC_DRAW))
}

VertexBuffer::~VertexBuffer()
{
	GLCALL(glDeleteBuffers(1, &m_VertexBufferId))
}

void VertexBuffer::Bind()
{
	GLCALL(glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferId))
}
void VertexBuffer::UnBind()
{
	GLCALL(glBindBuffer(GL_ARRAY_BUFFER, 0))
}