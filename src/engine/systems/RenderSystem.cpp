#include "RenderSystem.h"
#include "../../constants.h"

namespace tanks::engine
{

	RenderSystem::RenderSystem():ISystem()
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
		std::cout << io::File::getCurrentDirectory() << std::endl;
		_shader.attach((SHADER_FOLDER + "main.frag").c_str()).
			attach((SHADER_FOLDER + "main.vert").c_str()).
			link();
	}
	void RenderSystem::sendMessage()
	{
	}
}