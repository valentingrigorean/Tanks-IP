#include <tank/systems/CollisionSystem.h>
#include <tank/components/BulletComponent.h>
#include <tank/components/HealthComponent.h>

bool existsPair(std::map<GameObject*, GameObject*>& map, GameObject* e1, GameObject* e2)
{
	for (auto it : map)
		if (it.first == e1 || it.second == e2)
			return true;
	return false;
}

void CollisionSystem::Update()
{
	for (auto collision : _collisions)
	{
		auto& e1 = collision.first->entity;
		auto& e2 = collision.second->entity;
		if (HandleBullet(collision.first, collision.second)) continue;
	}
	_collisions.clear();
}

void CollisionSystem::SetPWorld(b2World * world)
{
	_world = world;
}

b2World * CollisionSystem::GetPWorld()
{
	return _world;
}

void CollisionSystem::OnCollisionOccured(GameObject* e1, GameObject* e2)
{
	if (!existsPair(_collisions, e1, e2))
		_collisions.insert(std::make_pair(e1, e2));
}

bool CollisionSystem::HandleBullet(GameObject * obj1, GameObject * obj2)
{
	auto& e1 = obj1->entity;
	auto& e2 = obj2->entity;
	if (!e1.isValid() || !e2.isValid()) 
		return false;
	if (!(e1.hasComponent<BulletComponent>() || e2.hasComponent<BulletComponent>()))
		return false;

	auto& bulletEntity = e1.hasComponent<BulletComponent>() ? e1 : e2;
	auto& bulletComp = bulletEntity.getComponent<BulletComponent>();

	if (bulletComp.owner == e1 || bulletComp.owner == e2)
		return true;

	if (e1.hasComponent<HealthComponent>() || e2.hasComponent<HealthComponent>())
	{
		auto& healthEnity = e1.hasComponent<HealthComponent>() ? e1 : e2;

		auto& healthComp = healthEnity.getComponent<HealthComponent>();
		healthComp.health -= bulletComp.dmg;
		if (healthComp.health <= 0)
			KillEntity(obj1, obj2, healthEnity);
	}

	KillEntity(obj1, obj2, bulletEntity);
	return true;
}

inline void CollisionSystem::KillEntity(GameObject * e1, GameObject * e2, anax::Entity & entity)
{
	if (e1->entity == entity)
		e1->Kill();
	else
		e2->Kill();
}
