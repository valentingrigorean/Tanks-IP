#pragma once

#include<Box2D/Box2D.h>

class DebugDrawSystem
{
public:
	DebugDrawSystem(int width,int height);
	~DebugDrawSystem();

	void EnableDebug(bool value);
	bool IsEnabled() const;

	void Render();

	void SetWorld(b2World * world);
	b2World* GetWorld();

private:
	b2World * _world;
	bool _enabled;
};