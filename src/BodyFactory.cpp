#include "BodyFactory.h"
#include "GConstants.h"

BodyFactory::BodyFactory()
{

}

b2Body * BodyFactory::CreateRect(b2World &world,float x, float y, int w, int h, bool dynamic)
{
	b2BodyDef bodyDef;

	bodyDef.position.Set(CONVERT_MPP(x), CONVERT_MPP(y));
	if (dynamic)
		bodyDef.type = b2_dynamicBody;
	auto body = world.CreateBody(&bodyDef);

	b2PolygonShape shape;
	w /= 2;
	h /= 2;
	shape.SetAsBox(CONVERT_MPP(w), CONVERT_MPP(h));

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	fixtureDef.density = 1.f;
	body->CreateFixture(&fixtureDef);	
	return body;
}
