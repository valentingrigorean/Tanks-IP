#pragma once

#include <anax/System.hpp>
#include "../graphics/SpriteRenderer.h"

struct SpriteComponent;
struct TransformComponent;

class SpriteRenderingSystem : public anax::System<anax::Requires<TransformComponent, SpriteComponent>>
{
public:
	SpriteRenderingSystem();
	SpriteRenderingSystem(SpriteRender &renderer);

	void Render();

	void SetRenderer(SpriteRender& renderer);
	SpriteRender& GetRenderer() const;

private:
	SpriteRender *_renderer;
};