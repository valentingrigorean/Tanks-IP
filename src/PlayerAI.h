#pragma once
#include "Player.h"

class PlayerAI : public Player
{
public:
	PlayerAI();

	void Update(float dt, World& world);
};