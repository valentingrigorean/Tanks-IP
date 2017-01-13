#pragma once
#include <tank/GameObject.h>


enum TANK_TYPE
{
	SPEED = 1,
	HEALTH = 0x2,
	DAMAGE = 0x3
};

class TankFactory
{
public:
	static void CreateTank(GameObject * tank, TANK_TYPE type);
private:
	TankFactory();
};