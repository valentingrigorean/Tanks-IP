#include <tank/systems/GunControlSystem.h>
#include <tank/ComponentsFactory.h>

GunControlSystem::GunControlSystem()
{
}

void GunControlSystem::Update(float dt)
{	
	auto& entities = getEntities();
	for (auto entity : entities)
	{
		auto& gunComp = entity.getComponent<GunComponent>();
		gunComp.timeSinceLastShot += dt;
		if (gunComp.shooting && gunComp.timeSinceLastShot >= gunComp.minimumShotInterval)
		{
			gunComp.timeSinceLastShot = 0;
			ComponentsFactory::CreateBullet(entity, gunComp);
		}
	}
}
