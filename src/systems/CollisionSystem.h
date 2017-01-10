#pragma once
#include <anax/System.hpp>
#include <vector>

#include "../Rect.h"
#include "../components/CollisionComponent.h"
#include "../components/TransformComponent.h"

class CollisionSystem :public anax::System < anax::Requires <TransformComponent,CollisionComponent>>
{
public:
	class ICollisionListener
	{
	public:
		virtual ~ICollisionListener() = 0 {};
		virtual void OnCollisionOccured(const anax::Entity& e1,const anax::Entity& e2) = 0;
	};

	void Update(float dt);
	void AddListener(ICollisionListener& listener);
	void RemoveListener(ICollisionListener& listener);
private:	
	void NotifyCollision(const anax::Entity &e1,const anax::Entity &e2);
	void GetBoxRect(TransformComponent& tranform, Rect &rect);
private:
	std::vector<ICollisionListener*> _listeners;
};