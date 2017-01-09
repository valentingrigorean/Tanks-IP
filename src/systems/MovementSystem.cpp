#include "MovementSystem.h"
#include "../components/TransformComponent.h"
#include "../components/VelocityComponent.h"

MovementSystem::MovementSystem()
{
}

void MovementSystem::Update(double deltaTime)
{
	auto entities = getEntities();
	for (auto& entity : entities)
	{
		auto& transform = entity.getComponent<TransformComponent>().transform;
		auto& velocity = entity.getComponent<VelocityComponent>().velocity;
		velocity *= (float)deltaTime;
		transform.Move(velocity.x, velocity.y);
	}
}
