#shader vertex
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
out vec3 FragPos;
out vec3 Normal;
void main()
{
   FragPos = vec3(model * vec4(aPos, 1.0));
   Normal = aNormal;

   gl_Position = projection * view * vec4(FragPos, 1.0);

};


#shader fragment
#version 330 core
out vec4 FragColor;
in vec3  Normal;
in vec3  FragPos;
uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 cubeColor;

uniform vec3 viewPos;
void main()
{
	//ambient 环境光
	float anmitentStrength = 0.1;
	vec3 ambient = anmitentStrength * lightColor;

	//diffuse 漫反射
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);

	//specular highlight 镜面反射
	float specularStrength = 0.5;
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);

	float spec = pow(max(dot(viewDir, reflectDir), 0.00), 64);
	vec3 spcular = specularStrength * spec * lightColor;

	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;

	vec3 resault = (ambient + diffuse+ spcular) * cubeColor;

	FragColor = vec4(resault,1.0);
};