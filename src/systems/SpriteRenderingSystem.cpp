#include <tank/systems/SpriteRenderingSystem.h>
#include <tank/components/SpriteComponent.h>
#include <tank/components/TransformComponent.h>
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
	std::sort(entities.begin(), entities.end(), [](anax::Entity& e1, anax::Entity& e2)
	{
		return e1.getComponent<SpriteComponent>().zOrder > e2.getComponent<SpriteComponent>().zOrder;
	});
	for (auto& entity : entities)
	{
		auto& sprite = entity.getComponent<SpriteComponent>().sprite;
		auto& transform = entity.getComponent<TransformComponent>().transform;
		_renderer->DrawSprite(sprite, transform);
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
