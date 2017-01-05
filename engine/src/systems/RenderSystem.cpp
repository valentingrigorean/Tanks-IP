#include "RenderSystem.h"
#include "..\GConstants.h"

RenderSystem::RenderSystem(GWindow *window):_window(window)
{
}


RenderSystem::~RenderSystem()
{
}

void RenderSystem::update(float dt)
{
	
}

void RenderSystem::init()
{		
	std::cout << GFile::getCurrentDirectory() << std::endl;
	_shader.attach((SHADER_FOLDER + "main.frag").c_str()).
		attach((SHADER_FOLDER + "main.vert").c_str()).
		link();
}
void RenderSystem::sendMessage()
{
}
