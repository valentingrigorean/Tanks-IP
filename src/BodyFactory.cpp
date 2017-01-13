#include <tank/BodyFactory.h>
#include <tank/GConstants.h>

b2Body * BodyFactory::CreateRect(b2World & world, BodyConfig & config)
{
	b2BodyDef bodyDef;

	bodyDef.position.Set(config.x * P2M, -config.y* P2M);

	bodyDef.type = config.dynamic ? b2_dynamicBody : b2_staticBody;

	auto body = world.CreateBody(&bodyDef);

	b2PolygonShape shape;
	auto w = config.w / 2;
	auto h = config.h / 2;
	shape.SetAsBox(w * P2M * config.scale, h * P2M* config.scale);


	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	fixtureDef.filter.categoryBits = config.categoryBits;
	fixtureDef.filter.maskBits = config.maskBits;


	fixtureDef.density = 1.f;
	body->CreateFixture(&fixtureDef);
	return body;
}

BodyFactory::BodyFactory()
{

}

