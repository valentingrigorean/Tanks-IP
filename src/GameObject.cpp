#include <tank/GameObject.h>
#include <tank/ObjectPool.h>
#include <tank/components/BodyComponent.h>

GameObject::GameObject()
{
	memset(this, 0, sizeof(GameObject));
}

void GameObject::Kill()
{
	if (entity.isValid() && entity.isActivated())
	{
		if (entity.hasComponent<BodyComponent>())
		{
			auto body = entity.getComponent<BodyComponent>().body;
			if (body != nullptr)
				body->GetWorld()->DestroyBody(body);
		}
		entity.kill();
	}
	ObjectPool::Free(this);
	memset(this, 0, sizeof(GameObject));
}