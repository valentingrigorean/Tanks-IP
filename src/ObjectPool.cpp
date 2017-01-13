#include <tank/ObjectPool.h>
#include <algorithm>

std::list<GameObject> ObjectPool::AllObjects(1000);
std::vector<GameObject*> ObjectPool::UsedObjects;



GameObject * ObjectPool::GetObject()
{
	return FindObject();
}

void ObjectPool::Free(GameObject * object)
{
	UsedObjects.erase(std::remove(UsedObjects.begin(), UsedObjects.end(), object),
		UsedObjects.end());
}

GameObject * ObjectPool::FindObject()
{
	if (AllObjects.size() == UsedObjects.size())
	{
		Resize();
	}
	for (auto& it : AllObjects)
	{
		if (std::find(UsedObjects.begin(), UsedObjects.end(), &it) == UsedObjects.end())
		{
			UsedObjects.push_back(&it);
			return &it;
		}
	}
	return nullptr;
}

void ObjectPool::Resize()
{
	for (std::size_t i = 0; i < 1000; i++)
	{
		AllObjects.push_back(GameObject());
	}
}