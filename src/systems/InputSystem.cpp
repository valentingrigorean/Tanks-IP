#include <tank/systems/InputSystem.h>

#include <anax/World.hpp>
#include <iostream>

#include <tank/GConstants.h>

#include <tank/components/InputComponent.h>
#include <tank/components/BodyComponent.h>
#include <tank/components/TransformComponent.h>
#include <tank/components/TankComponent.h>
#include <tank/components/GunComponent.h>

InputSystem::InputSystem()
{
}

void InputSystem::Update()
{
	auto entities = getEntities();
	for (auto& entity : entities)
	{
		auto& body = entity.getComponent<BodyComponent>().body;
		auto& input = entity.getComponent<InputComponent>().keys;

		if (_input->GetKey(input.shot))
			SetFire(entity, true);
		else
			SetFire(entity, false);

		if (_input->GetKey(input.up))
		{
			SetDirection(entity, UP);
			continue;
		}
		if (_input->GetKey(input.down))
		{
			SetDirection(entity, DOWN);
			continue;
		}
		if (_input->GetKey(input.left))
		{
			SetDirection(entity, LEFT);
			continue;
		}
		if (_input->GetKey(input.right))
		{
			SetDirection(entity, RIGHT);
			continue;
		}
		
		SetIdle(entity);
	}
}

Input * InputSystem::GetInput() const
{
	return _input;
}

void InputSystem::SetInput(Input * input)
{
	_input = input;
}

void InputSystem::SetDirection(anax::Entity & e, DIRECTION dir)
{
	if (!e.hasComponent<TankComponent>()) return;
	if (!e.hasComponent<BodyComponent>()) return;
	auto& tankComp = e.getComponent<TankComponent>();
	auto& body = e.getComponent<BodyComponent>().body;

	tankComp.direction = dir;
	b2Vec2 velocity = b2Vec2_zero;
	float rotation;

	auto speed = tankComp.speed * P2M;
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

	body->SetLinearVelocity(velocity);
	body->SetTransform(body->GetPosition(),glm::radians(rotation));
}

void InputSystem::SetIdle(anax::Entity & e)
{
	if (!e.hasComponent<TankComponent>()) return;
	if (!e.hasComponent<BodyComponent>()) return;
	auto& tankComp = e.getComponent<TankComponent>();
	auto& body = e.getComponent<BodyComponent>().body;
	body->SetLinearVelocity(b2Vec2_zero);
}

void InputSystem::SetFire(anax::Entity & e,bool isShooting)
{
	if (!e.hasComponent<TankComponent>()) return;
	if (!e.hasComponent<GunComponent>()) return;
	auto& tankComp = e.getComponent<TankComponent>();
	auto& gunComp = e.getComponent<GunComponent>();
	gunComp.shooting = isShooting;
	gunComp.direction = tankComp.direction;	
}