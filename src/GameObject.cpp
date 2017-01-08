#include "GameObject.h"

GameObject::GameObject():_transform(0.f,0.f,1.f,1.f),_velocity(0.f,0.f)
{
}

GameObject::GameObject(Point pos, Size size, Sprite sprite, Point velocity):
	_transform(pos,size),_velocity(velocity),_sprite(sprite)
{
}

bool GameObject::IsSolid() const
{
	return _isSolid;
}

void GameObject::SetSolid(bool value)
{
	_isSolid = value;
}

bool GameObject::IsAlive() const
{
	return _isAlive;
}

void GameObject::SetAlive(bool value)
{
	_isAlive = value;
}

Transform2D & GameObject::GetTransform()
{
	return _transform;
}

Sprite & GameObject::GetSprite()
{
	return _sprite;
}

void GameObject::SetSprite(Sprite sprite)
{
	_sprite = sprite;
}

Point & GameObject::GetVelocity()
{
	return _velocity;
}

void GameObject::Draw(SpriteRender & render)
{
	render.DrawSprite(_sprite, _transform);
}
