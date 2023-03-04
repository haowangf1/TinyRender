#shader vertex
#version 330 core
layout(location = 0) in vec3 aPoss;
uniform mat4 modellight;
uniform mat4 viewlight;
uniform mat4 projectionlight;
uniform vec4 u_color;
out vec4 color;
void main()
{
	gl_Position = projectionlight * viewlight * modellight * vec4(aPoss, 0.8);
	color = u_color;
	 
};


#shader fragment
#version 330 core
out vec4 FragColor;
in vec4 color;
void main()
{
	FragColor = color;
};