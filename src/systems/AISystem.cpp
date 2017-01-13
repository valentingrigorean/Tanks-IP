#include <tank/systems/AISystem.h>
#include <tank/components/GunComponent.h>
#include <tank/components/TankComponent.h>
#include <tank/components/BodyComponent.h>
#include <tank/GConstants.h>
#include <glm/glm.hpp>
#include <iostream>

void AISystem::Update(float dt)
{
	auto& entities = getEntities();
	for (auto entity : entities)
	{
		auto& aiComp = entity.getComponent<AIComponent>();
		aiComp.timeSinceUpdate += dt;
		if (aiComp.timeSinceUpdate >= aiComp.minimumInterval)
		{
			aiComp.timeSinceUpdate = 0;
			RandomAction(entity);
		}
	}
}

void AISystem::RandomAction(anax::Entity & entity)
{
	ACTION_TYPE action;
	auto r = _random.NextFloat();
	if (r < 0.1)
		action = ACTION_TYPE::NONE;
	else if (r < 0.4)
		action = ACTION_TYPE::SHOT;
	else
		action = ACTION_TYPE::DIR;	
	auto& gunComp = entity.getComponent<GunComponent>();
	auto& tankComp = entity.getComponent<TankComponent>();
	auto& body = entity.getComponent<BodyComponent>().body;
		
	switch (action)
	{
	case AISystem::NONE:
		gunComp.shooting = false;
		body->SetLinearVelocity(b2Vec2_zero);
		break;
	case AISystem::DIR:
		r = _random.NextFloat();
		if (r < 0.25f)
			tankComp.direction = DIRECTION::UP;
		else if (r < 0.5f)
			tankComp.direction = DIRECTION::LEFT;
		else if (r < 0.75f)
			tankComp.direction = DIRECTION::RIGHT;
		else
			tankComp.direction = DIRECTION::DOWN;
		gunComp.direction = tankComp.direction;
		SetDirection(tankComp.direction, body, tankComp.speed);
		break;
	case AISystem::SHOT:
		gunComp.shooting = !gunComp.shooting;
		break;
	}
}

void AISystem::SetDirection(DIRECTION dir, b2Body * body, float speed)
{
	b2Vec2 velocity = b2Vec2_zero;
	speed *= P2M;
	float rotation;
	switch (dir)
	{
	case DIRECTION::UP:
		velocity.y = speed;
		rotation = 0;
		break;
	case DIRECTION::DOWN:
		velocity.y = -speed;
		rotation = 180.f;
		break;
	case DIRECTION::LEFT:
		velocity.x = -speed;
		rotation = -90.f;
		break;
	case DIRECTION::RIGHT:
		velocity.x = speed;
		rotation = 90.f;
		break;
	}
	if (body->GetLinearVelocity().x != 0 && body->GetLinearVelocity().y)
		body->SetLinearVelocity(b2Vec2_zero);
	else
		body->SetLinearVelocity(velocity);
	body->SetTransform(body->GetPosition(), glm::radians(rotation));
}
