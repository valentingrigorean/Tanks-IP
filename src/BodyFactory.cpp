#include <tank/BodyFactory.h>
#include <tank/GConstants.h>

BodyFactory::BodyFactory()
{

}

b2Body * BodyFactory::CreateRect(b2World &world, float x, float y, int w, int h, TILE_TYPE tileType)
{
	b2BodyDef bodyDef;

	bodyDef.position.Set(x * P2M, y* P2M);

	bodyDef.type = tileType == TILE_TYPE::DYNAMIC ? b2_dynamicBody : b2_staticBody;

	auto body = world.CreateBody(&bodyDef);

	b2PolygonShape shape;
	float scale = tileType == TILE_TYPE::DYNAMIC ? 0.95f : 1.f;
	w /= 2;
	h /= 2;
	shape.SetAsBox(w * P2M *scale, h * P2M* scale);


	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	fixtureDef.filter.categoryBits = tileType;

	switch (tileType)
	{
	case SOLID:
	case DESTROYABLE:
		fixtureDef.filter.maskBits = TILE_TYPE::DYNAMIC;
		break;
	case DYNAMIC:
		fixtureDef.filter.maskBits = TILE_TYPE::DYNAMIC | TILE_TYPE::SOLID | TILE_TYPE::DESTROYABLE;
		break;
	}

	fixtureDef.density = 1.f;
	body->CreateFixture(&fixtureDef);
	return body;
}
