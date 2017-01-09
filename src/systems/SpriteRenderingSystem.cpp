#include "SpriteRenderingSystem.h"
#include "../components/SpriteComponent.h"
#include "../components/TransformComponent.h"
#include <anax/World.hpp>

SpriteRenderingSystem::SpriteRenderingSystem()
{
}

SpriteRenderingSystem::SpriteRenderingSystem(SpriteRender & renderer) :_renderer(&renderer)
{
}

void SpriteRenderingSystem::Render()
{	
	auto entities = getEntities();
	for (auto& entity : entities)
	{
		auto& sprite = entity.getComponent<SpriteComponent>();
		auto& transform = entity.getComponent<TransformComponent>();
		_renderer->DrawSprite(sprite.sprite, transform.transform);
	}
}

void SpriteRenderingSystem::SetRenderer(SpriteRender & renderer)
{
	_renderer = &renderer;
}

SpriteRender & SpriteRenderingSystem::GetRenderer() const
{
	return *_renderer;
}
