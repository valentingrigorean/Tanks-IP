#pragma once
#include "GOpengl.h"
#include "Shader.h"
#include "Sprite.h"

class SpriteRender
{
public:
	SpriteRender(Shader &shader);
	~SpriteRender();

	void DrawSprite(Sprite& sprite);
private:
	void Init();
private:
	GLuint _vao;
	Shader _shader;
};