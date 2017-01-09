#pragma once

#include <anax/System.hpp>
#include "../SpriteRenderer.h"

struct SpriteComponent;
struct TransformComponent;

class SpriteRenderingSystem : public anax::System<anax::Requires<SpriteComponent,TransformComponent>>
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