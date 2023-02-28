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
#include"TextureBuffer.h"
#include<imgui_impl_glfw.h>
#include<imgui_impl_opengl3.h>

using namespace std;

#define GLEW_STATIC

// 窗口尺寸
const unsigned int SCR_WIDTH = 2160;
const unsigned int SCR_HEIGHT = 1440;

int main(void)
{

    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Hello World by wanghao", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glewInit();//初始化glew



    // Setup Dear ImGui context
    // GL 3.0 + GLSL 130
    const char* glsl_version = "#version 130";
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);




    //开启深度测试
    glEnable(GL_DEPTH_TEST);

    float pos[] = {
    -0.5f, -0.5f, -0.5f, 1.0f,0.0f,0.0f,     0.0f, 0.0f,
     0.5f, -0.5f, -0.5f, 1.0f,0.0f,0.0f,     1.0f, 0.0f,
     0.5f,  0.5f, -0.5f, 1.0f,0.0f,0.0f,     1.0f, 1.0f,
     0.5f,  0.5f, -0.5f, 1.0f,0.0f,0.0f,     1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f, 1.0f,0.0f,0.0f,     0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 1.0f,0.0f,0.0f,     0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f, 1.0f,0.0f,0.0f,   0.0f, 0.0f,
     0.5f, -0.5f,  0.5f, 1.0f,0.0f,0.0f,   1.0f, 0.0f,
     0.5f,  0.5f,  0.5f, 1.0f,0.0f,0.0f,   1.0f, 1.0f,
     0.5f,  0.5f,  0.5f, 1.0f,0.0f,0.0f,   1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f, 1.0f,0.0f,0.0f,   0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f, 1.0f,0.0f,0.0f,   0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f, 1.0f,0.0f,0.0f,    0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f, 1.0f,0.0f,0.0f,    1.0f, 0.0f,
    -0.5f, -0.5f, -0.5f, 1.0f,0.0f,0.0f,    1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 1.0f,0.0f,0.0f,   1.0f, 1.0f,
    -0.5f, -0.5f,  0.5f, 1.0f,0.0f,0.0f,   0.0f, 1.0f,
    -0.5f,  0.5f,  0.5f, 1.0f,0.0f,0.0f,   0.0f, 0.0f,

     0.5f,  0.5f,  0.5f, 1.0f,0.0f,0.0f,   1.0f, 0.0f,
     0.5f,  0.5f, -0.5f, 1.0f,0.0f,0.0f,   1.0f, 1.0f,
     0.5f, -0.5f, -0.5f, 1.0f,0.0f,0.0f,   0.0f, 1.0f,
     0.5f, -0.5f, -0.5f, 1.0f,0.0f,0.0f,   0.0f, 1.0f,
     0.5f, -0.5f,  0.5f, 1.0f,0.0f,0.0f,   0.0f, 0.0f,
     0.5f,  0.5f,  0.5f, 1.0f,0.0f,0.0f,   1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f, 1.0f,0.0f,0.0f,   0.0f, 1.0f,
     0.5f, -0.5f, -0.5f, 1.0f,0.0f,0.0f,   1.0f, 1.0f,
     0.5f, -0.5f,  0.5f, 1.0f,0.0f,0.0f,   1.0f, 0.0f,
     0.5f, -0.5f,  0.5f, 1.0f,0.0f,0.0f,   1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f, 1.0f,0.0f,0.0f,   0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f, 1.0f,0.0f,0.0f,   0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f, 1.0f,0.0f,0.0f,   0.0f, 1.0f,
     0.5f,  0.5f, -0.5f, 1.0f,0.0f,0.0f,   1.0f, 1.0f,
     0.5f,  0.5f,  0.5f, 1.0f,0.0f,0.0f,   1.0f, 0.0f,
     0.5f,  0.5f,  0.5f, 1.0f,0.0f,0.0f,   1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f, 1.0f,0.0f,0.0f,   0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f, 1.0f,0.0f,0.0f,   0.0f, 1.0f
    };

    unsigned int indices[] = {
         0, 1, 3, // first triangle
         1, 2, 3  // second triangle
    };

    //创建顶点缓冲区并绑定
    VertexBuffer VB(pos, sizeof(pos));

    //设置顶点属性数据
    VertexBufferLayout layout;
    layout.push<float>(3);
    layout.push<float>(3);
    layout.push<float>(2);
   
    //创建顶点数组缓冲区,绑定顶点缓冲，并设置顶点属性布局
    VertexArray VA;
    VA.BindBuffer(VB, layout);
  
    //创建索引缓冲区并绑定
    IndexBuffer IB(indices,sizeof(indices));
    IB.Bind();

    //创建纹理缓冲并绑定
    TextureBuffer Texture(1);
    Texture.Bind();
    Texture.LoadImage("../wang.jpg");  
   
    //从源文件读取着色器源码，并绑定
    string vex;
    string fra;
    ReadShaderFromFile("Shader.shader", vex, fra);
    unsigned int shader = CreateShader(vex, fra);
    glUseProgram(shader);//状态机的体现  设置状态后 所有的draw指令都会使用当前状态绘制

   // int location = glGetUniformLocation(shader, "u_Color");//找到GPU中定义的uniform变量的内存位置
   // _ASSERT(location!=-1);//确保找到变量位置
   // glUniform4f(location,0.8f,0.5f,0.4f,1);//给uniform变量传数据


     // Our state
    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))//glfw提供窗口 glew进行绘制图形
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // also clear the depth buffer now!


        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
        if (show_demo_window)
            ImGui::ShowDemoWindow(&show_demo_window);

        // 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
        {
            static float f = 0.0f;
            static int counter = 0;

            ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

            ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
            ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
            ImGui::Checkbox("Another Window", &show_another_window);

            ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
            ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

            if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
                counter++;
            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::End();
        }

        // 3. Show another simple window.
        if (show_another_window)
        {
            ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
            ImGui::Text("Hello from another window!");
            if (ImGui::Button("Close Me"))
                show_another_window = false;
            ImGui::End();
        }



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
        projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH  / (float)SCR_HEIGHT, 1.0f, 100.0f);

        // retrieve the matrix uniform locations
        unsigned int modelLoc = glGetUniformLocation(shader, "model");
        unsigned int viewLoc = glGetUniformLocation(shader, "view");
        unsigned int projectLoc = glGetUniformLocation(shader, "projection");

        // pass them to the shaders (3 different ways)
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(projectLoc, 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);

        glDrawArrays(GL_TRIANGLES, 0, 36);//绘制缓冲区中的数据  无索引缓冲
       // glUniform4f(location, 1,r, 0.4f, 1);//给uniform变量传数据
        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);//利用顶点  和索引缓冲区的数据进行绘制，状态机特性  将顶点和索引设置好后直接绘制，不用再给数据


         // Rendering
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glDeleteProgram(shader);

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
    return 0;
}







#if 0
//现代opengl画三角形 基于缓冲区(顶点和索引)和着色器 顶点缓冲区提供用于渲染的顶点数据
unsigned int buffers;//生成的缓冲区id  
glGenBuffers(1, &buffers);//生成1个缓冲区返回id
glBindBuffer(GL_ARRAY_BUFFER, buffers);//绑定这个缓冲区为当前缓冲区
glBufferData(GL_ARRAY_BUFFER, 4 * 2 * sizeof(float), pos, GL_STATIC_DRAW);//将自定义数据复制到当前绑定缓冲区中   数据从cpu发送到GPU

//生成索引缓冲区 //允许同时绑定多个类型不同的缓冲区
unsigned int ibo;//生成的缓冲区id  例子：生成一个渲染id缓冲区
glGenBuffers(1, &ibo);//生成一个缓冲区返回id
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);//绑定这个缓冲区为当前缓冲区
glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), index, GL_STATIC_DRAW);//将自定义数据复制到当前绑定缓冲区中

//顶点是一个一个被顶点着色器处理的
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)0);//告诉显卡缓冲区中数据的布局和用法 layout(location = 0)传到0，两个顶点，步长为2
glEnableVertexAttribArray(0);//启用顶点属性数组

//顶点是一个一个被顶点着色器处理的
glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)(3 * sizeof(float)));//告诉显卡缓冲区中数据的布局和用法 layout(location = 0)传到0，两个顶点，步长为2
glEnableVertexAttribArray(1);//启用顶点属性数组



   // position attribute for VB
    //着色器中顶点属性的位置为0，一个属性有9个float那么大，间距为5个float,第一个属性相对原点的偏移量为0
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);//末尾参数为第一个数据相对原点的便宜量 
glEnableVertexAttribArray(0);

// texture coord attribute
glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
glEnableVertexAttribArray(2);

//layout (location = 1) in vec3 aColor;    location的值跟glVertexAttribPointer设置的定位属性位置的值是对应的
//layout(location = 2) in vec2 aTexCoord;


#endif