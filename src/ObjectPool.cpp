#include <tank/ObjectPool.h>

std::vector<PoolContainer> ObjectPool::AllObjects(1000);

GameObject * ObjectPool::GetObject()
{	
	return FindObject();
}

void ObjectPool::Free(GameObject * object)
{
	for (int i = 0; i < AllObjects.size(); i++)
	{
		auto item = &AllObjects[i];
		if (&(item->obj) == object)
		{
			item->isFree = true;
			return;
		}
	}
}

GameObject * ObjectPool::FindObject()
{
	if (AllObjects.size() == 0)
	{
		for (int i = 0; i < AllObjects.size(); i++)
			AllObjects.push_back(PoolContainer(true));
		auto item = &AllObjects.back();
		item->isFree = false;
		return &(item->obj);
	}
	for (int i = 0; i < AllObjects.size(); i++)
	{
		auto item = &AllObjects[i];
		if (item->isFree)
		{
			item->isFree = false;
			return &(item->obj);
		}
	}
	return nullptr;
}
