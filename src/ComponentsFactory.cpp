#include <tank/ComponentsFactory.h>
#include <tank/ObjectPool.h>
#include <tank/GameObject.h>

#include <tank/ResourceManager.h>
#include <tank/components/SpriteComponent.h>
#include <tank/components/TransformComponent.h>
#include <tank/components/HealthComponent.h>
#include <tank/components/TankComponent.h>
#include <tank/components/HealthComponent.h>
#include <tank/components/GunComponent.h>
#include <tank/components/BodyComponent.h>
#include <tank/components/BulletComponent.h>

#include <tank/GConstants.h>

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

b2Body * ComponentsFactory::AddBody(b2World & world, anax::Entity & entity, BodyConfig & config, void * userData, bool causeEvents)
{
	auto& bodyComp = entity.addComponent<BodyComponent>();
	bodyComp.causeEvents = causeEvents;
	bodyComp.body = BodyFactory::CreateRect(world, config);
	entity.activate();
	return bodyComp.body;
}

void ComponentsFactory::AddTank(anax::Entity & entity, int health, int dmg, float speed)
{
	auto& tankComp = entity.addComponent<TankComponent>();
	tankComp.speed = speed;
	auto& gunComp = entity.addComponent<GunComponent>();
	gunComp.bulletDamage = dmg;
	AddHealth(entity, health);
}

void ComponentsFactory::AddHealth(anax::Entity & entity, int health)
{
	auto& healthComp = entity.addComponent<HealthComponent>();
	healthComp.health = health;
	entity.activate();
}

void ComponentsFactory::CreateBullet(anax::Entity & owner, GunComponent &gunComp)
{
	
	auto& transform = owner.getComponent<TransformComponent>().transform;
	auto world = owner.getComponent<BodyComponent>().body->GetWorld();
	Point pos;
	Size size(20, 20);

	b2Vec2 velocity;

	switch (gunComp.direction)
	{
	case UP:
		pos.x = transform.GetPosition().x + (transform.GetSize().width / 2);
		pos.y = transform.GetPosition().y;
		velocity.x = 0;
		velocity.y = -1;
		break;
	case DOWN:
		pos.x = transform.GetPosition().x + (transform.GetSize().width / 2);
		pos.y = transform.GetPosition().y + transform.GetSize().height;
		velocity.x = 0;
		velocity.y = 1;
		break;
	case LEFT:
		pos.x = transform.GetPosition().x + (transform.GetSize().width / 2);
		pos.y = transform.GetPosition().y + (transform.GetSize().height / 2);
		velocity.x = -1;
		velocity.y = 0;
		break;
	case RIGHT:
		pos.x = transform.GetPosition().x + transform.GetSize().width;
		pos.y = transform.GetPosition().y + (transform.GetSize().height / 2);
		velocity.x = 1;
		velocity.y = 0;
		break;
	}

	auto& bulletEntity = CreateSprite(owner.getWorld(), ResourceManager::GetTexture("bullet"), pos, size);
	auto& bulletComp = bulletEntity.addComponent<BulletComponent>();

	auto obj = ObjectPool::GetObject();
	obj->entity = bulletEntity;

	bulletComp.owner = owner;
	bulletComp.dmg = gunComp.bulletDamage;
	BodyConfig bodyConfig(pos, size, TILE_TYPE::DYNAMIC, TILE_TYPE::DESTROYABLE | TILE_TYPE::DYNAMIC | TILE_TYPE::SOLID);

	auto body = AddBody(*world, bulletEntity, bodyConfig, obj, true);
	velocity.x *= gunComp.SPEED * P2M;
	velocity.y *= gunComp.SPEED * P2M;
	body->SetLinearVelocity(velocity);
}