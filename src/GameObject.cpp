#include <tank/GameObject.h>
#include <tank/ObjectPool.h>
#include <tank/components/BodyComponent.h>

GameObject::GameObject()
{
	memset(this, 0, sizeof(GameObject));
}

void GameObject::Kill(b2World * world)
{
	if (entity.isValid() && entity.isActivated())
	{
		if (world != nullptr && entity.hasComponent<BodyComponent>())
			world->DestroyBody(entity.getComponent<BodyComponent>().body);
		entity.kill();
	}
	ObjectPool::Free(this);
	memset(this, 0, sizeof(GameObject));
}