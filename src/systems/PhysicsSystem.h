#pragma once
#include <anax/System.hpp>
#include <anax/Entity.hpp>
#include <Box2D/Box2D.h>
#include <vector>


struct TransformComponent;
struct BodyComponent;

struct CollisionContainer
{
	b2Body* body;
	anax::Entity* entity;

	CollisionContainer(b2Body *body)
	{
		entity = static_cast<anax::Entity*>(body->GetUserData());
	}
};

struct CollisionHandler
{
	CollisionContainer c1;
	CollisionContainer c2;

	enum DESTROY_TYPE
	{
		NONE,
		BOTH,
		FIRST,
		SECOND
	};

	DESTROY_TYPE destroy = NONE;
	CollisionHandler(b2Body *body1, b2Body *body2) :c1(body1), c2(body2)
	{

	}
private:
	friend class PhysicsSystem;

	void Dispose(b2World & world)
	{
		switch (destroy)
		{
		case CollisionHandler::NONE:
			break;
		case CollisionHandler::BOTH:
			c1.entity->kill();
			c2.entity->kill();

			world.DestroyBody(c1.body);
			world.DestroyBody(c2.body);
			break;
		case CollisionHandler::FIRST:
			c1.entity->kill();
			world.DestroyBody(c1.body);
			break;
		case CollisionHandler::SECOND:
			c2.entity->kill();
			world.DestroyBody(c2.body);
			break;		
		}
	}
};

class PhysicsSystem :
	public anax::System<anax::Requires<TransformComponent,BodyComponent>>,
	b2ContactListener
{
public:
	PhysicsSystem();

	

	struct ICollisionListener
	{
		virtual ~ICollisionListener() = 0 {};

		/// Occurs when an Entity has collided with another entity
		/// \param e1 The first entity that has been collided with
		/// \param e2 The second entity that has been collided with
		/// \note e1 Is guarenteed to have the causesEvent flag to be true
		virtual void OnCollisionOccured(CollisionHandler* handler) = 0;
	};

	void Update(float dt);

	void SetListener(ICollisionListener& listener);

	void SetPhysicsWorld(b2World * world);
	b2World* GetPhysicsWorld();
private:
	void BeginContact(b2Contact* contact);
	void NotifyLiseners();
private:
	b2World *_world;
	ICollisionListener* _listener;
	std::vector<CollisionHandler> _collisions;
};