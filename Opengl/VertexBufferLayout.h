#pragma once
#include<vector>

//设置顶点属性所需要的数据合集
struct ElementLayout
{
	//只要这三个参数  别的参数都是冗余的 可以计算出来
	unsigned int m_iCountsData = 0;
	unsigned int m_iTypeData = 0;
	unsigned int m_iIfNormalized = 0;


	int m_iOffset = 0;
	
	//每一个顶点属性步长是前面所有属性+当前属性的 size之和
	int getCurAttributeSize() const
	{
		return m_iCountsData * sizeof(m_iTypeData);
	}
};



//顶点属性合集，一个顶点缓冲区需要多个顶点属性来解释，顶点+颜色+纹理
class VertexBufferLayout
{
public:
	std::vector<ElementLayout> m_ElementLayouts;
	int m_iStride = 0;
public:
	VertexBufferLayout()
	{
		m_ElementLayouts.clear();
	}
	~VertexBufferLayout()
	{

	}

	int  GetSize() const
	{
		return m_ElementLayouts.size();
	}

public:
	//像vector中添加一个顶点属性（颜色/纹理/顶点）

	template<typename T>
	void push(unsigned int count)
	{
		
	}

	template<>
	void push<float>(unsigned int count)
	{
		int stride = 0;
		for (auto iter : m_ElementLayouts)
		{
			stride += iter.getCurAttributeSize();
		}
		m_iStride += count * sizeof(float);

		m_ElementLayouts.push_back({ count,GL_FLOAT,GL_FALSE});
	}

	template<>
	void push<int>(unsigned int count)
	{
		int stride = 0;
		for (auto iter : m_ElementLayouts)
		{
			stride += iter.getCurAttributeSize();
		}
		stride += count * sizeof(float);

		m_ElementLayouts.push_back({ count,GL_INT,GL_FALSE });
	}
	
};