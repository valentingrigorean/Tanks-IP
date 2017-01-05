#pragma once
#include "ISystem.h"
#include "../Shader.h"
#include "../Graphics.h"

class GWindow;
class RenderSystem :public ISystem
{
public:
	RenderSystem(Graphics* graphics);
	~RenderSystem();

	void update(float dt);
	void init();
	void sendMessage();

private:
	Shader _shader;
	Graphics* _graphics;
};


