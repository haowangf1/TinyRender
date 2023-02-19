#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(const void* datas, int size)
{
	glGenBuffers(1, &m_indexBufferId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, datas, GL_STATIC_DRAW);
}
IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1,&m_indexBufferId);
}

void IndexBuffer::Bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferId);
}
void IndexBuffer::UnBind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}