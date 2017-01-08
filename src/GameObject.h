#pragma once
#include "Transform2D.h"
#include "Color.h"
#include "Sprite.h"
#include "SpriteRenderer.h"
#include "World.h"

class GameObject
{
public:
	
	GameObject();
	GameObject(Point pos, Size size, Point velocity = Point(0.f, 0.f));
	GameObject(Point pos, Size size, Sprite sprite, Point velocity = Point(0.f, 0.f));


	bool IsSolid() const;
	void SetSolid(bool value);

	bool IsAlive() const;
	void SetAlive(bool value);

	Transform2D& GetTransform();
	
	Sprite& GetSprite();
	void SetSprite(Sprite sprite);

	Point& GetVelocity();

	virtual void Update(float dt,World& world);
	virtual void Draw(SpriteRender &render);
private:
	Transform2D _transform;
	bool _isSolid;
	bool _isAlive;
	Sprite _sprite;
	Point _velocity;
};