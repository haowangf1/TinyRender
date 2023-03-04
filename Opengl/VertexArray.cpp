#include "VertexArray.h"



VertexArray::VertexArray():m_VertexArrayId(0)
{
	//���������������
	GLCALL(glGenVertexArrays(1, &m_VertexArrayId))
	
}

VertexArray::~VertexArray()
{
	GLCALL(glDeleteBuffers(1, &m_VertexArrayId))
}

	
void VertexArray::BindBuffer(VertexBuffer& vb, VertexBufferLayout& layout)
{

	//���������㻺�������󲢰�
	vb.Bind();

	//���ö������Բ���(һ�����㻺������Ҫ����������ԵĽ��ͣ��綥������ֲ�+��ɫ����ֲ�+��������ֲ�)
	unsigned int offset = 0;
	auto size = layout.GetSize();
	for (int i = 0; i < layout.GetSize(); i++)
	{
		const auto& lay = layout.m_ElementLayouts[i];
		
		GLCALL(glVertexAttribPointer(i, lay.m_iCountsData, lay.m_iTypeData, lay.m_iIfNormalized, layout.m_iStride, (const void*)offset))//��һ��������ƫ����
		GLCALL(glEnableVertexAttribArray(i))

		offset += lay.getCurAttributeSize();
	}
	
}
	
void VertexArray::Bind()
{
	GLCALL(glBindVertexArray(m_VertexArrayId))

}

void VertexArray::UnBind()
{
	GLCALL(glBindVertexArray(0))

}