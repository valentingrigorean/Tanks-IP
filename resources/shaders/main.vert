#version 150
in vec3 position;
in vec3 color;
in vec2 texcoord;
out vec3 Color;
out vec2 Texcoord;

void main()
{
	Color = color;
	Texcoord = texcoord;
	gl_position = vec4(position,1.0);
}