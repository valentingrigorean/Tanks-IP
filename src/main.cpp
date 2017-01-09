#include "Game.h"
#include "GLFW\GLFWInput.h"
#include "GLFW\GLFWDisplay.h"

const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 600;

int main(int argc,char *argv[])
{
	GLFWDisplay display(SCREEN_WIDTH, SCREEN_HEIGHT,std::string("Tanks"));
	display.Init();
	GLFWInput input;
	input.RegisterWindow(display.GetNativeWindow());
	
	Game tanks(&display, &input);
	tanks.Init();
	tanks.MainLoop();	
	return 0;
}