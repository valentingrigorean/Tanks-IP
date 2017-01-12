#include <tank/ComponentsFactory.h>

#include <tank/BodyFactory.h>

#include <tank/components/SpriteComponent.h>
#include <tank/components/TransformComponent.h>
#include <tank/components/HealthComponent.h>
#include <tank/components/TankComponent.h>
#include <tank/components/HealthComponent.h>
#include <tank/components/GunComponent.h>
#include <tank/components/BodyComponent.h>

anax::Entity ComponentsFactory::CreateSprite(anax::World & world, Texture2D & texture, Point position, Size size)
{
	auto& e = world.createEntity();
	e.addComponent<SpriteComponent>().sprite.SetTexture(texture);

	auto& transform = e.addComponent<TransformComponent>().transform;
	transform.SetPosition(position);
	transform.SetSize(size);
	e.activate();
	return e;
}

void ComponentsFactory::AddBody(b2World & world, GameObject & obj, void * userData)
{
	auto& bodyComp = obj.entity.addComponent<BodyComponent>();
	bodyComp.causeEvents = obj.tileType == TILE_TYPE::DYNAMIC;
	bodyComp.body = BodyFactory::CreateRect(world, obj.position.x, obj.position.y,
		obj.size.width, obj.size.height, obj.tileType);
	bodyComp.body->SetUserData(userData);
	obj.entity.activate();
}

void ComponentsFactory::AddTank(anax::Entity & entity, int health, int dmg, float speed)
{
	auto& tankComp = entity.addComponent<TankComponent>();
	tankComp.speed = speed;	
	auto& gunComp = entity.addComponent<GunComponent>();
	gunComp.bulletDamage = dmg;
	entity.activate();
	AddHealth(entity, health);
}

void ComponentsFactory::AddHealth(anax::Entity & entity, int health)
{
	auto& healthComp = entity.addComponent<HealthComponent>();
	healthComp.health = health;
	entity.activate();
}