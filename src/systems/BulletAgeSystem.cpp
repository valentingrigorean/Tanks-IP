#include <tank/systems/BulletAgeSystem.h>
#include <tank/components/BodyComponent.h>
#include <tank/GameObject.h>

void BulletAgeSystem::Update(float dt)
{
	auto& entities = getEntities();
	for (auto entity : entities)
	{
		auto& bulletComp = entity.getComponent<BulletComponent>();
		bulletComp.lifeRemaining -= dt;
		if (bulletComp.lifeRemaining <= 0)
		{
			if (entity.hasComponent<BodyComponent>())
			{
				auto& bodyComp = entity.getComponent<BodyComponent>().body;
				auto obj = static_cast<GameObject*>(bodyComp->GetUserData());
				if (obj != nullptr)
					obj->Kill();
			}
			else
				entity.kill();
		}
	}
}
