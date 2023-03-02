#shader vertex
#version 330 core
layout(location = 0) in vec3 aPoss;
layout(location = 1) in vec3 aColor;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
out vec3 color;
void main()
{
	gl_Position = projection * view * model * vec4(aPoss, 0.8);
	color = aColor;
};


#shader fragment
#version 330 core
out vec3 FragColor;
in vec3 color;
void main()
{
	FragColor = color;
};