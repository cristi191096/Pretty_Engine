#shader vertex
#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec4 color;

out vec4 pos;
out vec4 col;

void main()
{
	gl_Position = vec4(position, 1.0);
	pos = vec4(position, 0);
	col = color;
};

#shader fragment
#version 330 core

out vec4 color;

//uniform vec4 u_Color;

in vec4 pos;
in vec4 col;

void main()
{
	color = col;
};