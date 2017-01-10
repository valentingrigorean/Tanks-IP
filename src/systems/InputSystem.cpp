#include "InputSystem.h"

#include <anax/World.hpp>
#include <iostream>

#include "../components/InputComponent.h"
#include "../components/VelocityComponent.h"
#include "../components/TransformComponent.h"

InputSystem::InputSystem()
{
}

void InputSystem::Update()
{
	auto entities = getEntities();
	
	for (auto& entity : entities)
	{
		auto& velocity = entity.getComponent<VelocityComponent>();
		auto& input = entity.getComponent<InputComponent>();

		

		if (_input->GetKey(input.keys.up))
		{
			velocity.velocity.y = -velocity.speed;
			if (entity.hasComponent<TransformComponent>())
			{
				auto& transform = entity.getComponent<TransformComponent>().transform;
				transform.SetRotate(0);
			}
		}
		if (_input->GetKey(input.keys.down))
		{
			velocity.velocity.y = velocity.speed;
			if (entity.hasComponent<TransformComponent>())
			{
				auto& transform = entity.getComponent<TransformComponent>().transform;
				transform.SetRotate(180.f);
			}
		}
		if (_input->GetKey(input.keys.left))
		{
			velocity.velocity.x = -velocity.speed;
			if (entity.hasComponent<TransformComponent>())
			{
				auto& transform = entity.getComponent<TransformComponent>().transform;
				transform.SetRotate(-90.f);
			}
		}
		if (_input->GetKey(input.keys.right))
		{
			velocity.velocity.x = velocity.speed;
			if (entity.hasComponent<TransformComponent>())
			{
				auto& transform = entity.getComponent<TransformComponent>().transform;
				transform.SetRotate(90.f);
			}
		}		
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
