#pragma once
#include "GOpengl.h"
#include "Shader.h"
#include "Sprite.h"
#include "Transform2D.h"

class SpriteRender
{
public:
	SpriteRender();
	SpriteRender(Shader &shader);
	~SpriteRender();

	void DrawSprite(Shader& shader, Sprite &sprite, Transform2D &transform);
	void DrawSprite(Sprite& sprite,Transform2D &transform);
private:
	void Init();
private:
	GLuint _vao;
	Shader _shader;
};