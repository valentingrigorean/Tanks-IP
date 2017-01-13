#include <tank/systems/DebugDrawSystem.h>
#include <tank/glfw/DebugDraw.h>

DebugDrawSystem::DebugDrawSystem(int width, int height)
{
	g_camera.m_width = width;
	g_camera.m_height = height;
	g_camera.m_center.x = 14;
	g_camera.m_center.y = -14;
	g_camera.m_zoom = 0.6f;
	g_debugDraw.Create();

	uint32 flags = b2Draw::e_shapeBit |
		b2Draw::e_jointBit |
		b2Draw::e_aabbBit |
		b2Draw::e_pairBit |
		b2Draw::e_centerOfMassBit;
	g_debugDraw.Create();
	g_debugDraw.SetFlags(flags);
}

DebugDrawSystem::~DebugDrawSystem()
{
	g_debugDraw.Destroy();
}

void DebugDrawSystem::EnableDebug(bool value)
{
	_enabled = value;
}

bool DebugDrawSystem::IsEnabled() const
{
	return _enabled;
}

void DebugDrawSystem::Render()
{
	if (!_enabled) return;
	if (_world == nullptr) return;
	_world->DrawDebugData();
}

void DebugDrawSystem::SetWorld(b2World * world)
{
	_world = world;
	if (world != nullptr)
		_world->SetDebugDraw(&g_debugDraw);
}

b2World * DebugDrawSystem::GetWorld()
{
	return _world;
}