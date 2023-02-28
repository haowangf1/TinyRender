#include"VertexBuffer.h"

VertexBuffer::VertexBuffer(const void* datas, int size)
{
	glGenBuffers(1, &m_VertexBufferId);
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferId);
	glBufferData(GL_ARRAY_BUFFER, size, datas, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1,&m_VertexBufferId);
}

void VertexBuffer::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferId);
}
void VertexBuffer::UnBind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}