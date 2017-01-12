#pragma once

#include <vector>
#include "GameObject.h"

struct PoolContainer
{
	GameObject obj;
	bool isFree;

	PoolContainer()
	{

	}

	PoolContainer(bool _isFree) :obj(),isFree(_isFree)
	{

	}
};

class ObjectPool
{
public:
	static GameObject* GetObject();
	static void Free(GameObject* object);
private:
	ObjectPool();
	static GameObject* FindObject();
	static std::vector<PoolContainer> AllObjects;
};