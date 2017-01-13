#pragma once

#include <list>
#include "GameObject.h"

class ObjectPool
{
public:
	static GameObject* GetObject();
	static void Free(GameObject* object);
private:
	ObjectPool();
	static GameObject* FindObject();
	static std::list<GameObject> AllObjects;
	static std::vector<GameObject*> UsedObjects;
	static void Resize();
};