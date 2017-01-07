#pragma once

#define G_KEY_ESCAPE 256

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


