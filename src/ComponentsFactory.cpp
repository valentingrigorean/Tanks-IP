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
	bodyComp.body->SetUserData(userData);
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
	auto bodyEntity = owner.getComponent<BodyComponent>().body;
	auto world = bodyEntity->GetWorld();
	Point pos;
	Point offset;
	Size size(10, 10);

	b2Vec2 velocity;

	auto offsetX = (transform.GetSize().width / 2.f) + (size.width / 2.f) + 1;
	auto offsetY = (transform.GetSize().height / 2.f) + (size.height / 2.f) + 1;

	offset.x = transform.GetSize().width / 2.f - size.width / 2.f;
	offset.y = transform.GetSize().height / 2.f - size.height / 2.f;

	switch (gunComp.direction)
	{
	case UP:
		pos.x = transform.GetPosition().x;
		pos.y = transform.GetPosition().y - offsetY;
		velocity.x = 0;
		velocity.y = 1;
		offset.y = offsetY - size.height;
		break;
	case DOWN:
		pos.x = transform.GetPosition().x;
		pos.y = transform.GetPosition().y + offsetY;
		velocity.x = 0;
		velocity.y = -1;
		offset.y = offsetY - size.height;
		break;
	case LEFT:
		pos.x = transform.GetPosition().x - offsetX;
		pos.y = transform.GetPosition().y;
		velocity.x = -1;
		velocity.y = 0;
		offset.x = offsetX - size.width;
		break;
	case RIGHT:
		pos.x = transform.GetPosition().x + offsetX;
		pos.y = transform.GetPosition().y;
		velocity.x = 1;
		velocity.y = 0;
		offset.x = offsetX - size.width;
		break;
	}

	auto& bulletEntity = CreateSprite(owner.getWorld(), ResourceManager::GetTexture("bullet"), pos, size);
	auto& tranEntity = bulletEntity.getComponent<TransformComponent>().transform;
	tranEntity.SetOffset(offset);

	auto& bulletComp = bulletEntity.addComponent<BulletComponent>();

	auto obj = ObjectPool::GetObject();
	obj->entity = bulletEntity;

	bulletComp.owner = owner;
	bulletComp.dmg = gunComp.bulletDamage;
	auto mask = TILE_TYPE::DESTROYABLE | TILE_TYPE::DYNAMIC | TILE_TYPE::SOLID;
	//auto mask = 0x1;
	BodyConfig bodyConfig(pos, size, TILE_TYPE::DYNAMIC, mask);
	bodyConfig.dynamic = true;
	auto body = AddBody(*world, bulletEntity, bodyConfig, obj, true);
	velocity.x *= gunComp.SPEED * P2M;
	velocity.y *= gunComp.SPEED * P2M;
	body->SetLinearVelocity(velocity);
}