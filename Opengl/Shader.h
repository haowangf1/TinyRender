#pragma once
#include<iostream>
#include<glew.h>
#include<GLFW\glfw3.h>
#include<string>
#include<fstream>
#include"stb_image.h"
#include<glm.hpp>
#include<gtc/matrix_transform.hpp>
#include<gtc/type_ptr.hpp>
#include<sstream>
#include"ErrLog.h"
#include"VertexBuffer.h"
#include"indexBuffer.h"
#include"VertexBufferLayout.h"
#include"VertexArray.h"
#include"ShaderUtil.h"

class Shader
{

	


public:

	unsigned int m_ShaderId = 0;

	Shader(const std::string& filePath);
	~Shader();

	void Bind();
	void UnBind();

	void SetUniformMatrix4fv(const string& VarName,glm::mat4 mat);

};