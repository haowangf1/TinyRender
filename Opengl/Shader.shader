#shader vertex
#version 330 core
layout (location = 0) in vec3 aPoss;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;
out vec3 ourColors;
out vec2 TexCoord;
uniform mat4 transform;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
void main()
{
   gl_Position = projection * view * model*vec4(aPoss, 0.8);
   ourColors = aColor;
   TexCoord = vec2(aTexCoord.x, aTexCoord.y);
};


#shader fragment
#version 330 core
out vec4 FragColor;
in vec3 ourColors;
in vec2 TexCoord;
uniform sampler2D texture1;
void main()
{
   FragColor = texture(texture1, TexCoord);
};