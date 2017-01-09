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
	gl_Position = projection * model * vec4(
		flipX ? -vertex.x : vertex.x,
		flipY ? -vertex.y : vertex.y,0.0,1.0);
}