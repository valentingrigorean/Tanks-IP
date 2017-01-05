#pragma once

class GTimer
{
public:
	static void update();
	static float getDeltaTime();
	static float getFps();
private:
	GTimer();
	static double _lastTime;	
	static double _previews;
	static int _frames;
	static float _delta;
};