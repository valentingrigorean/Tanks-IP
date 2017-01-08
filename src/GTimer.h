#pragma once

class GTimer
{
public:
	~GTimer() {}
	virtual void Update() = 0;
	float GetDeltaTime();
	virtual double StartTime() = 0;
	float GetFps() const;
protected:
	GTimer();	
protected:
	double LastFrame;
	float DeltaTime;
private:
	int _frames;
	double _lastFrame;
	float _currentFrames;
	float _delta;
};