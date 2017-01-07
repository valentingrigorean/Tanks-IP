#pragma once
#include "../GTimer.h"

class GLFWTimer : public GTimer
{
public:
	GLFWTimer();
	~GLFWTimer();
	void Update();
	inline double StartTime();
};