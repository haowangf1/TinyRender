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

//从源文件读取着色器
static void ReadShaderFromFile(const string& filePath, string& VertexShader, string& FragmentShader)
{
    ifstream fileShader(filePath);

    if (!fileShader.is_open())
        cout << "shaderfile open failed! ";

    enum class ShaderType
    {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    ShaderType Type;//着色器类型

    stringstream ss[2];//字符串流,不同于字符串，  存储两个字符串
    string line;

    while (getline(fileShader, line))
    {
        if (line.find("#shader") != string::npos)
        {
            //根据预先设置的着色器类型识别符来判断着色器类型
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
            ss[(int)Type] << line << "\n";//类似 cout<<string   这里的输出流是字符串流
        }

    }

    fileShader.close();

    VertexShader = ss[0].str();
    FragmentShader = ss[1].str();

}


//编译着色器并返回着色器id索引
static unsigned int CompileShader(unsigned int type, const string& ShaderSrc)
{

    unsigned int id = glCreateShader(type);
    const char* src = ShaderSrc.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    //TODO: Error Handling
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);

    //打印错误日志  程序是在显卡中编译的
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


//创建着色器和程序 返回程序id
static unsigned int CreateShader(const string& VertexShader, const string& fragmentShader)
{
    unsigned int program = glCreateProgram();//创建程序
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, VertexShader);//GPU编译着色器程序
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);//着色器附加程序
    glAttachShader(program, fs);
    glLinkProgram(program);//连接程序
    glValidateProgram(program);//启动程序

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;

};
