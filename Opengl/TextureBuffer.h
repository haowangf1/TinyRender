#pragma once
#include<glew.h>
#include"stb_image.h"
#include<iostream>

class TextureBuffer
{
	unsigned int m_iTextureBufferId = 0;

public:
	TextureBuffer(int count);
	~TextureBuffer();

	void LoadImage(const char* path);
	void  UseImage();
	void Bind();
	void UnBind();
	


};