#version 330 core
layout (location = 0)in vec4 vertex; // <Vec 2 position, vec 2 texCoords>

out vec2 TexCoords;

uniform mat4 model;
uniform mat4 projection;
uniform bool flipX;
uniform bool flipY;

void main()
{
	TexCoords = vertex.zw;
	float x = flipX ? 1-vertex.x : vertex.x;
	float y = flipY ? 1-vertex.y : vertex.y;
	gl_Position = projection * model * vec4(x,y,0.0,1.0);
}