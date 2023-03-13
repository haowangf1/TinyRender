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
#include"Shader.h"
#include"ErrLog.h"

using namespace std;

#define GLEW_STATIC

// 窗口尺寸
const unsigned int SCR_WIDTH = 2160;
const unsigned int SCR_HEIGHT = 1440;

// camera
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

//key input
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    float cameraSpeed = static_cast<float>(2.5 * deltaTime);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}

int main(void)
{

    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

   // glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    //glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Hello World by wanghao", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    /* Make the window's context current */
    glfwMakeContextCurrent(window);


    // tell GLFW to capture our mouse
   // glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);


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
    -0.5f, -0.5f, -0.5f, 1.0f,0.5f,0.31f,     0.0f, 0.0f,
     0.5f, -0.5f, -0.5f, 1.0f,0.5f,0.31f,     1.0f, 0.0f,
     0.5f,  0.5f, -0.5f, 1.0f,0.5f,0.31f,     1.0f, 1.0f,
     0.5f,  0.5f, -0.5f, 1.0f,0.5f,0.31f,     1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f, 1.0f,0.5f,0.31f,     0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 1.0f,0.5f,0.31f,     0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f, 1.0f,0.5f,0.31f,   0.0f, 0.0f,
     0.5f, -0.5f,  0.5f, 1.0f,0.5f,0.31f,   1.0f, 0.0f,
     0.5f,  0.5f,  0.5f, 1.0f,0.5f,0.31f,   1.0f, 1.0f,
     0.5f,  0.5f,  0.5f, 1.0f,0.5f,0.31f,   1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f, 1.0f,0.5f,0.31f,   0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f, 1.0f,0.5f,0.31f,   0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f, 1.0f,0.5f,0.31f,    0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f, 1.0f,0.5f,0.31f,    1.0f, 0.0f,
    -0.5f, -0.5f, -0.5f, 1.0f,0.5f,0.31f,    1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 1.0f,0.5f,0.31f,   1.0f, 1.0f,
    -0.5f, -0.5f,  0.5f, 1.0f,0.5f,0.31f,   0.0f, 1.0f,
    -0.5f,  0.5f,  0.5f, 1.0f,0.5f,0.31f,   0.0f, 0.0f,

     0.5f,  0.5f,  0.5f, 1.0f,0.5f,0.31f,   1.0f, 0.0f,
     0.5f,  0.5f, -0.5f, 1.0f,0.5f,0.31f,   1.0f, 1.0f,
     0.5f, -0.5f, -0.5f, 1.0f,0.5f,0.31f,   0.0f, 1.0f,
     0.5f, -0.5f, -0.5f, 1.0f,0.5f,0.31f,   0.0f, 1.0f,
     0.5f, -0.5f,  0.5f, 1.0f,0.5f,0.31f,   0.0f, 0.0f,
     0.5f,  0.5f,  0.5f, 1.0f,0.5f,0.31f,   1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f, 1.0f,0.0f,0.0f,   0.0f, 1.0f,
     0.5f, -0.5f, -0.5f, 1.0f,0.0f,0.0f,   1.0f, 1.0f,
     0.5f, -0.5f,  0.5f, 1.0f,0.0f,0.0f,   1.0f, 0.0f,
     0.5f, -0.5f,  0.5f, 1.0f,0.0f,0.0f,   1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f, 1.0f,0.0f,0.0f,   0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f, 1.0f,0.0f,0.0f,   0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f, 1.0f,0.5f,0.31f,   0.0f, 1.0f,
     0.5f,  0.5f, -0.5f, 1.0f,0.5f,0.31f,   1.0f, 1.0f,
     0.5f,  0.5f,  0.5f, 1.0f,0.5f,0.31f,   1.0f, 0.0f,
     0.5f,  0.5f,  0.5f, 1.0f,0.5f,0.31f,   1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f, 1.0f,0.5f,0.31f,   0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f, 1.0f,0.5f,0.31f,   0.0f, 1.0f
    };


    float poslight[] = {
    -0.5f, -0.5f, -0.5f, 1.0f,1.0f,1.0f,     0.0f, 0.0f,
     0.5f, -0.5f, -0.5f, 1.0f,1.0f,1.0f,     1.0f, 0.0f,
     0.5f,  0.5f, -0.5f, 1.0f,1.0f,1.0f,     1.0f, 1.0f,
     0.5f,  0.5f, -0.5f, 1.0f,1.0f,1.0f,     1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f, 1.0f,1.0f,1.0f,     0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 1.0f,1.0f,1.0f,     0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f, 1.0f,1.0f,1.0f,   0.0f, 0.0f,
     0.5f, -0.5f,  0.5f, 1.0f,1.0f,1.0f,   1.0f, 0.0f,
     0.5f,  0.5f,  0.5f, 1.0f,1.0f,1.0f,   1.0f, 1.0f,
     0.5f,  0.5f,  0.5f, 1.0f,1.0f,1.0f,   1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f, 1.0f,1.0f,1.0f,   0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f, 1.0f,1.0f,1.0f,   0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f, 1.0f,1.0f,1.0f,    0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f, 1.0f,1.0f,1.0f,    1.0f, 0.0f,
    -0.5f, -0.5f, -0.5f, 1.0f,1.0f,1.0f,    1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 1.0f,1.0f,1.0f,   1.0f, 1.0f,
    -0.5f, -0.5f,  0.5f, 1.0f,1.0f,1.0f,   0.0f, 1.0f,
    -0.5f,  0.5f,  0.5f, 1.0f,1.0f,1.0f,   0.0f, 0.0f,

     0.5f,  0.5f,  0.5f, 1.0f,1.0f,1.0f,   1.0f, 0.0f,
     0.5f,  0.5f, -0.5f, 1.0f,1.0f,1.0f,   1.0f, 1.0f,
     0.5f, -0.5f, -0.5f, 1.0f,1.0f,1.0f,   0.0f, 1.0f,
     0.5f, -0.5f, -0.5f, 1.0f,1.0f,1.0f,   0.0f, 1.0f,
     0.5f, -0.5f,  0.5f, 1.0f,1.0f,1.0f,   0.0f, 0.0f,
     0.5f,  0.5f,  0.5f, 1.0f,1.0f,1.0f,   1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f, 1.0f,1.0f,1.0f,   0.0f, 1.0f,
     0.5f, -0.5f, -0.5f, 1.0f,1.0f,1.0f,   1.0f, 1.0f,
     0.5f, -0.5f,  0.5f, 1.0f,1.0f,1.0f,   1.0f, 0.0f,
     0.5f, -0.5f,  0.5f, 1.0f,1.0f,1.0f,   1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f, 1.0f,1.0f,1.0f,   0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f, 1.0f,1.0f,1.0f,   0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f, 1.0f,1.0f,1.0f,   0.0f, 1.0f,
     0.5f,  0.5f, -0.5f, 1.0f,1.0f,1.0f,   1.0f, 1.0f,
     0.5f,  0.5f,  0.5f, 1.0f,1.0f,1.0f,   1.0f, 0.0f,
     0.5f,  0.5f,  0.5f, 1.0f,1.0f,1.0f,   1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f, 1.0f,1.0f,1.0f,   0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f, 1.0f,1.0f,1.0f,   0.0f, 1.0f
    };

    float vertices_withNormal[] = {
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
    };

    unsigned int indices[] = {
         0, 1, 3, // first triangle
         1, 2, 3  // second triangle
    };


    VertexArray VA;
    VA.Bind();//状态机的特性是必须先绑定这个VAO,后续VBO的数据才会被这个VAO所记录
    //创建顶点缓冲区并绑定
    VertexBuffer VB(vertices_withNormal, sizeof(vertices_withNormal));
    //设置顶点属性数据
    VertexBufferLayout layoutcube;
    layoutcube.push<float>(3);
    layoutcube.push<float>(3);
    //创建顶点数组缓冲区,绑定顶点缓冲，并设置顶点属性布局
    VA.BindBuffer(VB, layoutcube);


    VertexArray VA_Light;
    VA_Light.Bind();//状态机的特性是必须先绑定这个VAO,后续VBO的数据才会被这个VAO所记录
    VertexBuffer VBlight(poslight, sizeof(poslight));
    VertexBufferLayout layoutlight;
    layoutlight.push<float>(3);
    layoutlight.push<float>(3);
    layoutlight.push<float>(2);
    VA_Light.BindBuffer(VBlight, layoutlight);
   
    
    //创建索引缓冲区并绑定
    IndexBuffer IB(indices,sizeof(indices));
    IB.Bind();
    //创建纹理缓冲并绑定
    TextureBuffer Texture(1);
   // Texture.Bind();
    //Texture.LoadImage("../wang.jpg");  
   

    //从源文件读取着色器源码，并绑定
    Shader Cubeshader("Shader.shader");
    

    //从源文件读取着色器源码，并绑定
    Shader Lightshader("light.shader");
  
   // int location = glGetUniformLocation(shader, "u_Color");//找到GPU中定义的uniform变量的内存位置
   // _ASSERT(location!=-1);//确保找到变量位置
   // glUniform4f(location,0.8f,0.5f,0.4f,1);//给uniform变量传数据

     // Our state
    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    glm::vec3 cubeTranslatevec3(0.0f, 0.0f, 0.0f);//cube的model translate矩阵
    glm::vec4 cubeColorvec3(1.0f, 0.5f, 0.31f, 1.0f);//cube的model color矩阵

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))//glfw提供窗口 glew进行绘制图形
    {
        // per-frame time logic
        // --------------------
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // keyinput
        // -----
        processInput(window);


        /* Render here */
        GLCALL(glClear(GL_COLOR_BUFFER_BIT))
        GLCALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)) // also clear the depth buffer now!

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
        if (show_demo_window)
            ImGui::ShowDemoWindow(&show_demo_window);

        //Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
        {
            static float f = 0.0f;
            static int counter = 0;

            ImGui::Begin("TinyRender Debug Window");                          // Create a window called "Hello, world!" and append into it.

            ImGui::Text("TinyRender Debug");
            ImGui::SliderFloat3("float", &cubeTranslatevec3.x, -10.0f, 10.0f);//
            ImGui::ColorEdit3("clear color", (float*)&cubeColorvec3); // Edit 3 floats representing a color


                      // Display some text (you can use a format strings too)
            ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
            ImGui::Checkbox("Another Window", &show_another_window);
            if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
                counter++;
            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::End();
        }

        // camera/view transformation
        glm::mat4 viewCamer = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);


 
        //1.2, 1.0, 2.0
        //绘制光源
        Lightshader.Bind();//要先绑定着色器 才能去设置着色中的变量
        glm::mat4 modellight = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        glm::mat4 viewlight = glm::mat4(1.0f);
        glm::mat4 projectionlight = glm::mat4(1.0f);
        modellight = glm::rotate(modellight, glm::radians(20.0f), glm::vec3(0.5f, 1.0f, 0.0f));
        modellight = glm::scale(modellight, glm::vec3(0.2f, 0.2f, 0.2f));
        viewCamer = glm::translate(viewCamer, glm::vec3(1.2f, 0.8f, -2.5f));
        projectionlight = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 1.0f, 100.0f);
        Lightshader.SetUniformMatrix4fv("modellight", modellight);
        Lightshader.SetUniformMatrix4fv("viewlight", viewCamer);
        Lightshader.SetUniformMatrix4fv("projectionlight", projectionlight);
        Lightshader.SetUniformVec4("u_color", 1.2f, 1.2f, 1.2f, 1.0f);
        VA_Light.Bind();//重新绑定要绘制的数据   
        Lightshader.Bind();//重新绑定要使用的顶点着色器(状态机特性)
        GLCALL(glDrawArrays(GL_TRIANGLES, 0, 36)) //绘制缓冲区中的数据，无索引缓冲


        // create transformations
        //绘制立方体
        Cubeshader.Bind();//要先绑定着色器 才能去设置着色中的变量
        glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);
        model = glm::rotate(model,  glm::radians(30.0f), glm::vec3(1.0f, 1.0f, 0.0f));
        model = glm::translate(model, cubeTranslatevec3);//和imgui进行交互
        viewCamer = glm::translate(viewCamer, glm::vec3(0.0f, 0.0f, -4.0f));
        projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 1.0f, 100.0f);
        Cubeshader.SetUniformMatrix4fv("model", model);
        Cubeshader.SetUniformMatrix4fv("view", viewCamer);
        Cubeshader.SetUniformMatrix4fv("projection", projection);
        Cubeshader.SetUniformVec3("cubeColor", cubeColorvec3.x, cubeColorvec3.y, cubeColorvec3.z);
        Cubeshader.SetUniformVec3("lightColor", 1.0f, 1.0f, 1.0f);
        Cubeshader.SetUniformVec3("lightPos", 0,0,2.0);
        Cubeshader.SetUniformVec3("viewPos", 0, 0, 2.0);
        VA.Bind();//绑定要绘制的数据
        Cubeshader.Bind();//绑定要使用的顶点着色器(状态机特性)
        GLCALL(glDrawArrays(GL_TRIANGLES, 0, 36))//绘制缓冲区中的数据  无索引缓冲


         // Rendering
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }


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