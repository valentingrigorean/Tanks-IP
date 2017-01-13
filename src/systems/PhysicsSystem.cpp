#include <tank/systems/PhysicsSystem.h>
#include <iostream>

#include <tank/GConstants.h>

#include <tank/components/BodyComponent.h>
#include <tank/components/TransformComponent.h>
#include <tank/components/BulletComponent.h>
#include <tank/components/TankComponent.h>


inline void FixBullet(float *x, float *y, Transform2D& bulletTran, anax::Entity& owner)
{
	auto& transform = owner.getComponent<TransformComponent>().transform;
	auto& tankComp = owner.getComponent<TankComponent>();
	switch (tankComp.direction)
	{
	case UP:
		*x += transform.GetSize().width / 2.f - bulletTran.GetSize().width /2.f;
		break;
	case DOWN:
		
		break;
	case LEFT:
		
		break;
	case RIGHT:
		
		break;
	}
}

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
		auto x = position.x * M2P;
		auto y = -position.y * M2P;
		transform.SetPosition(x, y);
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