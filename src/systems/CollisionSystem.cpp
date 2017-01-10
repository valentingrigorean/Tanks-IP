#include "CollisionSystem.h"

#include <algorithm>

#include "../components/TransformComponent.h"
#include "../components/CollisionComponent.h"

void CollisionSystem::Update(float dt)
{
	auto& entities = getEntities();

	Rect rect1, rect2;

	for (std::size_t i = 0; i < entities.size(); ++i)
	{
		auto& e1 = entities[i];

		if (!e1.getComponent<CollisionComponent>().causeEvents) continue;

		GetBoxRect(e1.getComponent<TransformComponent>(), rect1);

		for (std::size_t j = i + 1; j < entities.size(); ++j)
		{
			auto& e2 = entities[j];
			GetBoxRect(e2.getComponent<TransformComponent>(), rect2);			
			if (rect1.IsIntersected(rect2))
				NotifyCollision(e1, e2);
		}
	}
}

void CollisionSystem::AddListener(ICollisionListener & listener)
{
	_listeners.push_back(&listener);
}

void CollisionSystem::RemoveListener(ICollisionListener & listener)
{
	_listeners.erase(std::remove(_listeners.begin(), _listeners.end(), &listener), 
		_listeners.end());
}

void CollisionSystem::NotifyCollision(const anax::Entity & e1,const anax::Entity & e2)
{
	for (auto& lisner : _listeners)
		lisner->OnCollisionOccured(e1, e2);
}

void CollisionSystem::GetBoxRect(TransformComponent & tranform, Rect & rect)
{
	auto& pos = tranform.transform.GetPosition();
	rect.point.x = pos.x;
	rect.point.y = pos.y;
}
