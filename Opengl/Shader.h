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
	unsigned int m_ShaderId = 0;
public:

	Shader(const std::string& filePath);
	~Shader();

	void Bind();
	void UnBind();

	void SetUniformMatrix4fv(const string& VarName,glm::mat4 mat);
	void SetUniformVec4(const string& VarName, float v1, float v2, float v3, float v4);
	void SetUniformVec3(const string& VarName, float v1, float v2, float v3);
};