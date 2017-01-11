#include "PhysicsSystem.h"
#include <algorithm>

#include "../GConstants.h"

#include "../components/BodyComponent.h"
#include "../components/TransformComponent.h"

PhysicsSystem::PhysicsSystem():_listener(nullptr)
{
}

void PhysicsSystem::Update(float dt)
{
	_world->Step(dt, 6, 2);

	NotifyLiseners();
	auto& entities = getEntities();
	for (auto& entity : entities)
	{
		auto& transform = entity.getComponent<TransformComponent>().transform;
		auto& body = entity.getComponent<BodyComponent>().body;
		auto position = body->GetPosition();
		transform.SetPosition(CONVERT_PPM(position.x), CONVERT_PPM(position.y));
		transform.SetRotate(body->GetAngle());
	}
}

void PhysicsSystem::SetListener(ICollisionListener & listener)
{
	_listener = &listener;
}


void PhysicsSystem::SetPhysicsWorld(b2World * world)
{
	_world = world;
	_world->SetContactListener(this);
}

b2World * PhysicsSystem::GetPhysicsWorld()
{
	return _world;
}

void PhysicsSystem::BeginContact(b2Contact * contact)
{	
	auto body1 = contact->GetFixtureA()->GetBody();
	auto body2 = contact->GetFixtureB()->GetBody();
	_collisions.push_back(CollisionHandler(body1, body2));
}

void PhysicsSystem::NotifyLiseners()
{
	if (_listener == nullptr) return;
	if (_collisions.size() == 0) return;
	for (auto& collision : _collisions)
	{
		_listener->OnCollisionOccured(&collision);
		collision.Dispose(*_world);
	}
	_collisions.clear();
}
