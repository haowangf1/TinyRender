#include"Shader.h"



Shader::Shader(const std::string& filePath)
{
	
	string VertexShader, FragmentShader;
	ReadShaderFromFile(filePath, VertexShader, FragmentShader);
	m_ShaderId =  CreateShader(VertexShader, FragmentShader);

}
Shader::~Shader()
{

	GLCALL(glDeleteProgram(m_ShaderId))

}

void Shader::Bind()
{

	GLCALL(glUseProgram(m_ShaderId))

}
void Shader::UnBind()
{
	GLCALL(glUseProgram(0))

}

void Shader::SetUniformMatrix4fv(const string& VarName, glm::mat4 mat)
{

	GLCALL(glUniformMatrix4fv(glGetUniformLocation(m_ShaderId, VarName.c_str()), 1, GL_FALSE, glm::value_ptr(mat)))


}

void Shader::SetUniformVec4(const string& VarName, float v1, float v2, float v3, float v4)
{

	GLfloat vec[4] = { v1,v2,v3,v4 };
	GLCALL(glUniform4fv(glGetUniformLocation(m_ShaderId, VarName.c_str()), 1, vec))


}


void Shader::SetUniformVec3(const string& VarName, float v1, float v2, float v3)
{

	GLfloat vec[3] = { v1,v2,v3 };
	GLCALL(glUniform3fv(glGetUniformLocation(m_ShaderId, VarName.c_str()), 1, vec))


}