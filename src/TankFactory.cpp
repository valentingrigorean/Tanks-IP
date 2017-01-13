#include <tank/TankFactory.h>
#include <tank/components/GunComponent.h>
#include <tank/components/HealthComponent.h>
#include <tank/components/TankComponent.h>
#include <tank/components/SpriteComponent.h>
#include <tank/ResourceManager.h>

void TankFactory::CreateTank(GameObject * tank, TANK_TYPE type)
{
	if (tank == nullptr || !tank->entity.isValid()) return;

	auto& tankComp = tank->entity.getComponent<TankComponent>();
	auto& healthComp = tank->entity.getComponent<HealthComponent>();
	auto& gunComp = tank->entity.getComponent<GunComponent>();
	auto& spriteComp = tank->entity.getComponent<SpriteComponent>();

	int dmg = 1;
	float speed = 45.f;
	int health = 5;
	std::string texture = "tank_s";
	switch (type)
	{
	case SPEED:
		speed *= 1.5f;
		break;
	case HEALTH:
		health = 7;
		texture = "tank_h";
		break;
	case DAMAGE:
		dmg = 2;
		texture = "tank_d";
		break;	
	}

	tankComp.speed = speed;
	healthComp.health = health;
	gunComp.bulletDamage = dmg;
	spriteComp.sprite.SetTexture(ResourceManager::GetTexture(texture));
}
