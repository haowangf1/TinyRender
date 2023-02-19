#pragma once
#include<glew.h>
#include<iostream>

//xΪGLLogCall() �ڷ���false�ĵط��ж�
#define ASSERT(x) if(!(x)) __debugbreak();

//yΪ���õ�gl���� Ϊ��ǰ��ֱ�������err�ʹ�ӡerr��Ϣ�ĺ���
#define GLCALL(y) GLClearErr();\
y;\
ASSERT(GLLogCall())

//������
static void GLClearErr()
{
    while (glGetError() != GL_NO_ERROR);//���ǰ��ĺ����д���Ῠ����ѭ��  ����ĺ����޷�ִ��  ��Ҫ�ֶ�����ǰ��Ĵ���
}

//�������ӡ
static bool GLLogCall()
{
    while (GLenum err = glGetError())
    {
        std::cout << "[GLERROR]" << err << std::endl;
        return false;
    }
    return true;
}