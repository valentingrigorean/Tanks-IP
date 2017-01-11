#include "InputSystem.h"

#include <anax/World.hpp>
#include <iostream>

#include "../GConstants.h"

#include "../components/InputComponent.h"
#include "../components/BodyComponent.h"
#include "../components/TransformComponent.h"
#include "../components/TankComponent.h"

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

		if (_input->GetKey(input.up))
		{
			SetData(entity, UP);
			continue;
		}
		if (_input->GetKey(input.down))
		{
			SetData(entity, DOWN);
			continue;
		}
		if (_input->GetKey(input.left))
		{
			SetData(entity, LEFT);
			continue;
		}
		if (_input->GetKey(input.right))
		{
			SetData(entity, RIGHT);
			continue;
		}
		SetData(entity, DIRECTION::UP, true);
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

void InputSystem::SetData(anax::Entity & e, DIRECTION dir,bool idle)
{
	if (!e.hasComponent<TankComponent>()) return;	
	if (!e.hasComponent<BodyComponent>()) return;
	auto& tankComp = e.getComponent<TankComponent>();
	auto& body = e.getComponent<BodyComponent>().body;

	if (idle)
	{
		body->SetLinearVelocity(b2Vec2_zero);
		return;
	}

	tankComp.direction = dir;
	b2Vec2 velocity = body->GetLinearVelocity();
	float rotation;

	auto speed = CONVERT_MPP(tankComp.speed);
	switch (dir)
	{
	case DIRECTION::UP:
		velocity.y = -speed;
		rotation = 0;
		break;
	case DIRECTION::DOWN:
		velocity.y = speed;
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
	body->SetTransform(body->GetPosition(), rotation);
}
