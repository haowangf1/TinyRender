#include "VertexArray.h"



VertexArray::VertexArray():m_VertexArrayId(0)
{
	//创建顶点数组对象
	GLCALL(glGenVertexArrays(1, &m_VertexArrayId))
	
}

VertexArray::~VertexArray()
{
	GLCALL(glDeleteBuffers(1, &m_VertexArrayId))
}

	
void VertexArray::BindBuffer(VertexBuffer& vb, VertexBufferLayout& layout)
{

	//创建顶顶点缓冲区对象并绑定
	vb.Bind();

	//配置顶点属性布局(一个顶点缓冲区需要多个顶点属性的解释，如顶点坐标分布+颜色坐标分布+纹理坐标分布)
	unsigned int offset = 0;
	auto size = layout.GetSize();
	for (int i = 0; i < layout.GetSize(); i++)
	{
		const auto& lay = layout.m_ElementLayouts[i];
		
		GLCALL(glVertexAttribPointer(i, lay.m_iCountsData, lay.m_iTypeData, lay.m_iIfNormalized, layout.m_iStride, (const void*)offset))//第一个属性无偏移量
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