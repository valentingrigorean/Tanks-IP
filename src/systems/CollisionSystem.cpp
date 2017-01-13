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
		if (!(e1.hasComponent<BulletComponent>() || e2.hasComponent<BulletComponent>())) continue;

		auto& bulletEntity = e1.hasComponent<BulletComponent>() ? e1 : e2;
		auto& bulletComp = bulletEntity.getComponent<BulletComponent>();

		if (e1.hasComponent<HealthComponent>() || e2.hasComponent<HealthComponent>())
		{
			auto& healthEnity = e1.hasComponent<HealthComponent>() ? e1 : e2;

			auto& healthComp = healthEnity.getComponent<HealthComponent>();
			healthComp.health -= bulletComp.dmg;
			if (healthComp.health < 0)
				KillEntity(collision.first, collision.second, healthEnity);			
		}
		
		KillEntity(collision.first, collision.second, bulletEntity);
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

inline void CollisionSystem::KillEntity(GameObject * e1, GameObject * e2, anax::Entity & entity)
{
	if (e1->entity == entity)
		e1->Kill();
	else
		e2->Kill();
}
