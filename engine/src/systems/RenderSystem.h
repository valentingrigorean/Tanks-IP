#pragma once
#include "ISystem.h"
#include "../Shader.h"

class GWindow;
class RenderSystem :public ISystem
{
public:
	RenderSystem(GWindow* window);
	~RenderSystem();

	void update(float dt);
	void init();
	void sendMessage();

private:
	Shader _shader;
	GWindow* _window;
};


