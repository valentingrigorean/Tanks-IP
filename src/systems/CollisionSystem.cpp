#include <tank/systems/CollisionSystem.h>

bool existsPair(std::map<anax::Entity*, anax::Entity*>& map, anax::Entity* e1, anax::Entity* e2)
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

void CollisionSystem::OnCollisionOccured(anax::Entity * e1, anax::Entity * e2)
{
	if (!existsPair(_collisions, e1, e2))
		_collisions.insert(std::make_pair(e1, e2));
}