#include "GTimer.h"

GTimer::GTimer()
{
	_frames = 0;
	DeltaTime = 0;
	LastFrame = 0;
}

void GTimer::Update()
{
	_frames++;
	auto delta = LastFrame - _lastFrame;
	if (delta >= 1.0f)
	{
		_currentFrames = float(_frames) / (float)delta;
		_frames = 0;
		_lastFrame = LastFrame;
	}
}

float GTimer::GetDeltaTime()
{
	if (DeltaTime < 0 || DeltaTime > 1)
		DeltaTime = 0.025f;
	return DeltaTime;
}

float GTimer::GetFps() const
{
	return _currentFrames;
}