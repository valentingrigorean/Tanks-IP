#include "Game.h"
#include "GLFW\GLFWInput.h"
#include "GLFW\GLFWDisplay.h"
#include "GLFW\GLFWTimer.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

int main(int argc,char *argv[])
{
	GLFWDisplay display(SCREEN_WIDTH, SCREEN_HEIGHT,std::string("Tanks"));
	display.Init();
	GLFWInput input;
	input.RegisterWindow(display.GetNativeWindow());
	GLFWTimer timer;
	Game tanks(&display, &input,&timer);
	tanks.Init();
	tanks.MainLoop();	
	return 0;
}