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

// ���ڳߴ�
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
    glewInit();//��ʼ��glew



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




    //������Ȳ���
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

    //�������㻺��������
    VertexBuffer VB(pos, sizeof(pos));

    //���ö�����������
    VertexBufferLayout layout;
    layout.push<float>(3);
    layout.push<float>(3);
    layout.push<float>(2);
   
    //�����������黺����,�󶨶��㻺�壬�����ö������Բ���
    VertexArray VA;
    VA.BindBuffer(VB, layout);
  
    //������������������
    IndexBuffer IB(indices,sizeof(indices));
    IB.Bind();

    //���������岢��
    TextureBuffer Texture(1);
    Texture.Bind();
    Texture.LoadImage("../wang.jpg");  
   
    //��Դ�ļ���ȡ��ɫ��Դ�룬����
    string vex;
    string fra;
    ReadShaderFromFile("Shader.shader", vex, fra);
    unsigned int shader = CreateShader(vex, fra);
    glUseProgram(shader);//״̬��������  ����״̬�� ���е�drawָ���ʹ�õ�ǰ״̬����

   // int location = glGetUniformLocation(shader, "u_Color");//�ҵ�GPU�ж����uniform�������ڴ�λ��
   // _ASSERT(location!=-1);//ȷ���ҵ�����λ��
   // glUniform4f(location,0.8f,0.5f,0.4f,1);//��uniform����������


     // Our state
    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))//glfw�ṩ���� glew���л���ͼ��
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



        //����任���󲢴��ݸ���ɫ��
        glm::mat4 trans = glm::mat4(1.0f);//��ʼ��
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

        glDrawArrays(GL_TRIANGLES, 0, 36);//���ƻ������е�����  ����������
       // glUniform4f(location, 1,r, 0.4f, 1);//��uniform����������
        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);//���ö���  �����������������ݽ��л��ƣ�״̬������  ��������������úú�ֱ�ӻ��ƣ������ٸ�����


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
//�ִ�opengl�������� ���ڻ�����(���������)����ɫ�� ���㻺�����ṩ������Ⱦ�Ķ�������
unsigned int buffers;//���ɵĻ�����id  
glGenBuffers(1, &buffers);//����1������������id
glBindBuffer(GL_ARRAY_BUFFER, buffers);//�����������Ϊ��ǰ������
glBufferData(GL_ARRAY_BUFFER, 4 * 2 * sizeof(float), pos, GL_STATIC_DRAW);//���Զ������ݸ��Ƶ���ǰ�󶨻�������   ���ݴ�cpu���͵�GPU

//�������������� //����ͬʱ�󶨶�����Ͳ�ͬ�Ļ�����
unsigned int ibo;//���ɵĻ�����id  ���ӣ�����һ����Ⱦid������
glGenBuffers(1, &ibo);//����һ������������id
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);//�����������Ϊ��ǰ������
glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), index, GL_STATIC_DRAW);//���Զ������ݸ��Ƶ���ǰ�󶨻�������

//������һ��һ����������ɫ�������
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)0);//�����Կ������������ݵĲ��ֺ��÷� layout(location = 0)����0���������㣬����Ϊ2
glEnableVertexAttribArray(0);//���ö�����������

//������һ��һ����������ɫ�������
glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)(3 * sizeof(float)));//�����Կ������������ݵĲ��ֺ��÷� layout(location = 0)����0���������㣬����Ϊ2
glEnableVertexAttribArray(1);//���ö�����������



   // position attribute for VB
    //��ɫ���ж������Ե�λ��Ϊ0��һ��������9��float��ô�󣬼��Ϊ5��float,��һ���������ԭ���ƫ����Ϊ0
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);//ĩβ����Ϊ��һ���������ԭ��ı����� 
glEnableVertexAttribArray(0);

// texture coord attribute
glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
glEnableVertexAttribArray(2);

//layout (location = 1) in vec3 aColor;    location��ֵ��glVertexAttribPointer���õĶ�λ����λ�õ�ֵ�Ƕ�Ӧ��
//layout(location = 2) in vec2 aTexCoord;


#endif