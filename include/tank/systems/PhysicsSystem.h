#pragma once
#include <anax/System.hpp>
#include <anax/Entity.hpp>
#include <Box2D/Box2D.h>

#include <tank/GameObject.h>

struct TransformComponent;
struct BodyComponent;

class PhysicsSystem :
	public anax::System<anax::Requires<TransformComponent, BodyComponent>>,
	b2ContactListener
{
public:
	PhysicsSystem();

	struct ICollisionListener
	{
		virtual ~ICollisionListener() = 0 {};
	
		virtual void OnCollisionOccured(GameObject *e1,GameObject *e2) = 0;
	};

	void Update(float dt);

	void SetListener(ICollisionListener& listener);

	void SetPhysicsWorld(b2World * world);
	b2World* GetPhysicsWorld();
private:
	void BeginContact(b2Contact* contact);
private:
	b2World *_world;
	ICollisionListener* _listener;
};