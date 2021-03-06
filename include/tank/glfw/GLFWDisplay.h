#pragma once
#include "../graphics/Display.h"
#include "../graphics/GOpengl.h"

class GLFWDisplay :public Display
{
public:
	GLFWDisplay(int width, int height, std::string& title);
	~GLFWDisplay();

	void Init();
	void SwapBuffers();
	void SetTitle(std::string & title);

	GLFWwindow* GetNativeWindow();
private:
	GLFWwindow *_window;
};