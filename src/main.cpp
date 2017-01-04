#include "engine\Engine.h"

int main(char ** argv, int argc) 
{
	
	auto game = new tanks::engine::Engine();
	game->mainLoop();
	delete game;
	return 0;
}