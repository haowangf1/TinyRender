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

#define GLEW_STATIC

using namespace std;

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

//从源文件读取着色器
void ReadShaderFromFile(const string& filePath,string &VertexShader,string& FragmentShader)
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
static unsigned int CreateShader(const string& VertexShader,const string& fragmentShader)
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


int main(void)
{

    
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(2160, 1440, "Hello World by wanghao", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    glewInit();//初始化glew

    glEnable(GL_DEPTH_TEST);

    float pos0[] =
    {
        // positions          // colors           // texture coords
          0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   0.0f, 1.0f, // top right
          0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   0.0f, 0.0f, // bottom right
         -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   1.0f, 0.0f, // bottom left
         -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   1.0f, 1.0f  // top left 

      //  -0.5f,0.5f, 0.0f,   1.0f,0.6f,1.0f  //第二个三角形唯一的unique顶点   其他顶点可重复使用
      
    };

    float pos[] = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };


    unsigned int indices[] = {
         0, 1, 3, // first triangle
         1, 2, 3  // second triangle
    };


#if 0
    //现代opengl画三角形 基于缓冲区(顶点和索引)和着色器 顶点缓冲区提供用于渲染的顶点数据
    unsigned int buffers;//生成的缓冲区id  
    glGenBuffers(1, &buffers);//生成1个缓冲区返回id
    glBindBuffer(GL_ARRAY_BUFFER, buffers);//绑定这个缓冲区为当前缓冲区
    glBufferData(GL_ARRAY_BUFFER, 4 * 2 * sizeof(float), pos, GL_STATIC_DRAW);//将自定义数据复制到当前绑定缓冲区中   数据从cpu发送到GPU

    //生成索引缓冲区 //允许同时绑定多个类型不同的缓冲区
    unsigned int ibo;//生成的缓冲区id  例子：渲染id为1的缓冲区
    glGenBuffers(1, &ibo);//生成一个缓冲区返回id
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);//绑定这个缓冲区为当前缓冲区
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), index, GL_STATIC_DRAW);//将自定义数据复制到当前绑定缓冲区中

    //顶点是一个一个被顶点着色器处理的
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)0);//告诉显卡缓冲区中数据的布局和用法 layout(location = 0)传到0，两个顶点，步长为2
    glEnableVertexAttribArray(0);//启用顶点属性数组

    //顶点是一个一个被顶点着色器处理的
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)(3 * sizeof(float)));//告诉显卡缓冲区中数据的布局和用法 layout(location = 0)传到0，两个顶点，步长为2
    glEnableVertexAttribArray(1);//启用顶点属性数组

#endif


    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(pos), pos, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);


    // load and create a texture 
    // -------------------------
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
    const char* path = "D:/OpenGl/wang.jpg";
    unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);   

    string vex;
    string fra;
    //从源文件读取着色器源码
    ReadShaderFromFile("Shader.shader", vex, fra);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    unsigned int shader = CreateShader(vex, fra);
    glUseProgram(shader);//状态机的体现  设置状态后 所有的draw指令都会使用当前状态绘制


   // int location = glGetUniformLocation(shader, "u_Color");//找到GPU中定义的uniform变量的内存位置
   // _ASSERT(location!=-1);//确保找到变量位置
   // glUniform4f(location,0.8f,0.5f,0.4f,1);//给uniform变量传数据


    float r = 1.0f;
    float increment = 0.001f;
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))//glfw提供窗口 glew进行绘制图形
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // also clear the depth buffer now!

        //定义变换矩阵并传递给着色器
        glm::mat4 trans = glm::mat4(1.0f);//初始化
        trans = glm::rotate(trans, (float)(glfwGetTime()), glm::vec3(0.0, 0.0, 1.0));
        trans = glm::scale(trans, glm::vec3(1.5, 1.5, 1.5));
        unsigned int transformLoc = glGetUniformLocation(shader, "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

        // create transformations
        glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);
        model = glm::rotate(model, (float)glfwGetTime() * glm::radians(20.0f), glm::vec3(0.5f, 1.0f, 0.0f));
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -4.0f));
        projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 1.0f, 100.0f);
        // retrieve the matrix uniform locations
        unsigned int modelLoc = glGetUniformLocation(shader, "model");
        unsigned int viewLoc = glGetUniformLocation(shader, "view");
        unsigned int projectLoc = glGetUniformLocation(shader, "projection");
        // pass them to the shaders (3 different ways)
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(projectLoc, 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
 

        glBindTexture(GL_TEXTURE_2D, texture);
        glBindVertexArray(VAO);
       // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glDrawArrays(GL_TRIANGLES, 0, 36);//绘制缓冲区中的数据  无索引缓冲
       // glUniform4f(location, 1,r, 0.4f, 1);//给uniform变量传数据
        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);//利用顶点  和索引缓冲区的数据进行绘制，状态机特性  将顶点和索引设置好后直接绘制，不用再给数据

        

        increment = -0.0025f;
        r += increment;

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glDeleteProgram(shader);

    glfwTerminate();
    return 0;
}