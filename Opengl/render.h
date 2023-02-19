#pragma once
#include<glew.h>
#include<iostream>

//x为GLLogCall() 在返回false的地方中断
#define ASSERT(x) if(!(x)) __debugbreak();

//y为调用的gl函数 为其前后分别添加清楚err和打印err信息的函数
#define GLCALL(y) GLClearErr();\
y;\
ASSERT(GLLogCall())

//错误处理
static void GLClearErr()
{
    while (glGetError() != GL_NO_ERROR);//如果前面的函数有错误会卡在这循环  后面的函数无法执行  需要手动改正前面的错误
}

//错误处理打印
static bool GLLogCall()
{
    while (GLenum err = glGetError())
    {
        std::cout << "[GLERROR]" << err << std::endl;
        return false;
    }
    return true;
}