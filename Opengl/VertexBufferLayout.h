#pragma once

struct ElementLayout
{



};


class VertexBufferLayout
{
private:
	ElementLayout m_ElementLayou;
public:
	VertexBufferLayout();
	~VertexBufferLayout();
public:
	void push();
};