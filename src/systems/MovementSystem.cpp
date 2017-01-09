#include "MovementSystem.h"

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
