#pragma once
#include <anax/System.hpp>
#include <anax/Component.hpp>
#include <map>

#include "PhysicsSystem.h"
#include "../GameObject.h"

class CollisionSystem :
	public anax::System<anax::Requires<anax::Component>>,
	public PhysicsSystem::ICollisionListener
{
public:
	void Update();
	void SetPWorld(b2World *world);
	b2World* GetPWorld();
private:
	void OnCollisionOccured(GameObject* e1, GameObject* e2);
	inline void KillEntity(GameObject* e1, GameObject* e2, anax::Entity& entity);
private:
	b2World *_world;
	std::map<GameObject*, GameObject*> _collisions;
};