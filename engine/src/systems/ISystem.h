#pragma once


class ISystem
{
public:

	virtual ~ISystem() {}

	virtual void update(float dt) = 0;

	virtual void init() = 0;

	virtual void sendMessage() = 0;
};


