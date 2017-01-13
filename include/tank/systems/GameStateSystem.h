#pragma once
#include <anax/System.hpp>
#include <tank/components/TankComponent.h>
#include <tank/LevelGame.h>

struct GameObject;

class GameStateSystem : public anax::System<anax::Requires<TankComponent>>
{
public:

	struct IStateLisener
	{
		virtual void GameEnded(GameObject *won) = 0;
		virtual ~IStateLisener() = 0 {};
	};

	void Update();
	void SetStateLisener(IStateLisener &lisener);
	void SetLevelGame(LevelGame &levelGame);
private:
	IStateLisener *_lisener;
	LevelGame *_levelGame;
};