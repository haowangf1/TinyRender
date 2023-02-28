#pragma once
#include<vector>

//���ö�����������Ҫ�����ݺϼ�
struct ElementLayout
{
	//ֻҪ����������  ��Ĳ������������ ���Լ������
	unsigned int m_iCountsData = 0;
	unsigned int m_iTypeData = 0;
	unsigned int m_iIfNormalized = 0;


	int m_iOffset = 0;
	
	//ÿһ���������Բ�����ǰ����������+��ǰ���Ե� size֮��
	int getCurAttributeSize() const
	{
		return m_iCountsData * sizeof(m_iTypeData);
	}
};



//�������Ժϼ���һ�����㻺������Ҫ����������������ͣ�����+��ɫ+����
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
	//��vector�����һ���������ԣ���ɫ/����/���㣩

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