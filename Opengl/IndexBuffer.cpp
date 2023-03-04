#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(const void* datas, int size)
{
	GLCALL(glGenBuffers(1, &m_indexBufferId))
	GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferId))
	GLCALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, datas, GL_STATIC_DRAW))
}
IndexBuffer::~IndexBuffer()
{
	GLCALL(glDeleteBuffers(1, &m_indexBufferId))
}

void IndexBuffer::Bind()
{
	GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferId))
}
void IndexBuffer::UnBind()
{
	GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0))
}