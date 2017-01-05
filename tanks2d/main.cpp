#include <Engine.h>

int main(char ** argv, int arcv)
{
	GWindow window(1024, 768, "Tanks 2d");

	Engine engine(&window);
	engine.mainLoop();
	return 0;
}