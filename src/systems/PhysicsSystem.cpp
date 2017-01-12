#include <tank/systems/PhysicsSystem.h>
#include <iostream>

#include <tank/GConstants.h>

#include <tank/components/BodyComponent.h>
#include <tank/components/TransformComponent.h>


PhysicsSystem::PhysicsSystem() :_listener(nullptr)
{
}

void PhysicsSystem::Update(float dt)
{
	_world->Step(dt, 6, 2);

	auto& entities = getEntities();
	for (auto& entity : entities)
	{
		auto& transform = entity.getComponent<TransformComponent>().transform;
		auto& body = entity.getComponent<BodyComponent>().body;
		auto position = body->GetPosition();
		transform.SetPosition(position.x * M2P, position.y * M2P);
		transform.SetRotate(RADIAN_TO_DEGREES(body->GetAngle()));
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
	if (_listener == nullptr) return;
	auto e1 = static_cast<GameObject*>(
		contact->GetFixtureA()->GetBody()->GetUserData());
	auto e2 = static_cast<GameObject*>(
		contact->GetFixtureB()->GetBody()->GetUserData());
	_listener->OnCollisionOccured(e1, e2);
}