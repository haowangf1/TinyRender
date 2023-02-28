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

using namespace std;

//��Դ�ļ���ȡ��ɫ��
static void ReadShaderFromFile(const string& filePath, string& VertexShader, string& FragmentShader)
{
    ifstream fileShader(filePath);

    if (!fileShader.is_open())
        cout << "shaderfile open failed! ";

    enum class ShaderType
    {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    ShaderType Type;//��ɫ������

    stringstream ss[2];//�ַ�����,��ͬ���ַ�����  �洢�����ַ���
    string line;

    while (getline(fileShader, line))
    {
        if (line.find("#shader") != string::npos)
        {
            //����Ԥ�����õ���ɫ������ʶ������ж���ɫ������
            if (line.find("vertex") != string::npos)
            {
                Type = ShaderType::VERTEX;
            }
            else
            {
                Type = ShaderType::FRAGMENT;
            }

        }
        else
        {
            ss[(int)Type] << line << "\n";//���� cout<<string   �������������ַ�����
        }

    }

    fileShader.close();

    VertexShader = ss[0].str();
    FragmentShader = ss[1].str();

}


//������ɫ����������ɫ��id����
static unsigned int CompileShader(unsigned int type, const string& ShaderSrc)
{

    unsigned int id = glCreateShader(type);
    const char* src = ShaderSrc.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    //TODO: Error Handling
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);

    //��ӡ������־  ���������Կ��б����
    if (result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        cout << (type == GL_VERTEX_SHADER ? "vertex Shader compile failed" : "fragment Shader compile failed") << endl;
        cout << message << endl;
    }

    return id;

}


//������ɫ���ͳ��� ���س���id
static unsigned int CreateShader(const string& VertexShader, const string& fragmentShader)
{
    unsigned int program = glCreateProgram();//��������
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, VertexShader);//GPU������ɫ������
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);//��ɫ�����ӳ���
    glAttachShader(program, fs);
    glLinkProgram(program);//���ӳ���
    glValidateProgram(program);//��������

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;

};
