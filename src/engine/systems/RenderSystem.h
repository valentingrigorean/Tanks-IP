#pragma once
#include "ISystem.h"
#include "../Shader.h"

namespace tanks::engine
{
	class RenderSystem:public ISystem
	{
	public:
		RenderSystem();
		~RenderSystem();

		void update(float dt);
		void init();
		void sendMessage();

	private:
		Shader _shader;
	};

}
