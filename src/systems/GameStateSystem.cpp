#include <tank/systems/GameStateSystem.h>
#include <tank/GameObject.h>

void GameStateSystem::Update()
{
	auto& entities = getEntities();
	if (entities.size() > 1) return;
	if (_lisener == nullptr) return;

	auto entity = entities[0];
	for (auto obj : _levelGame->GetAllObjects())
		if (obj->entity == entity)
			_lisener->GameEnded(obj);
}

void GameStateSystem::SetStateLisener(IStateLisener & lisener)
{	
	_lisener = &lisener;
}

void GameStateSystem::SetLevelGame(LevelGame & levelGame)
{
	_levelGame = &levelGame;
}
