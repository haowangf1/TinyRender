#include"Shader.h"



Shader::Shader(const std::string& filePath)
{
	
	string VertexShader, FragmentShader;
	ReadShaderFromFile(filePath, VertexShader, FragmentShader);
	m_ShaderId =  CreateShader(VertexShader, FragmentShader);

}
Shader::~Shader()
{

	glDeleteProgram(m_ShaderId);

}

void Shader::Bind()
{

	glUseProgram(m_ShaderId);

}
void Shader::UnBind()
{
	glUseProgram(0);

}

void Shader::SetUniformMatrix4fv(const string& VarName, glm::mat4 mat)
{

	unsigned int MatrixLoc = glGetUniformLocation(m_ShaderId, VarName.c_str());
	glUniformMatrix4fv(MatrixLoc, 1, GL_FALSE, glm::value_ptr(mat));


}