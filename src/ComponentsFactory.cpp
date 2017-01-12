#include <tank/ComponentsFactory.h>

#include <tank/BodyFactory.h>
#include <tank/ObjectPool.h>
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

b2Body* ComponentsFactory::AddBody(b2World & world, GameObject & obj, void * userData)
{
	auto& bodyComp = obj.entity.addComponent<BodyComponent>();
	bodyComp.causeEvents = obj.tileType == TILE_TYPE::DYNAMIC;
	bodyComp.body = BodyFactory::CreateRect(world, obj.position.x, obj.position.y,
		obj.size.width, obj.size.height, obj.tileType);
	bodyComp.body->SetUserData(userData);
	obj.entity.activate();
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
	auto obj = ObjectPool::GetObject();
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
	bulletComp.owner = owner;
	bulletComp.dmg = gunComp.bulletDamage;
	obj->position = pos;
	obj->size = size;
	obj->entity = bulletEntity;
	obj->tileType = TILE_TYPE::DYNAMIC;

	auto body = AddBody(*world,*obj, obj);
	velocity.x *= gunComp.SPEED * P2M;
	velocity.y *= gunComp.SPEED * P2M;
	body->SetLinearVelocity(velocity);
}