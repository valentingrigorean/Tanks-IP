#pragma once

#include "graphics/GOpengl.h"

#define G_KEY_ESCAPE 256
#define G_KEY_UP 265
#define G_KEY_DOWN 264
#define G_KEY_LEFT 263
#define G_KEY_RIGHT 262

class Input
{
public:
	~Input() {}
	virtual bool GetKey(int keyCode) = 0;
	virtual bool GetKey(char key) = 0;
	virtual void PollEvents() = 0;
protected:
	Input(){}
};