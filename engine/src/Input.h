#pragma once
#include "GWindow.h"
#include <map>

class Input
{
public:
	static bool getKey(int keyCode);
	static bool getKey(char key);
	static void pollEvents();
	static void registerWindow(GWindow *window);
	static void unregisterWindow(GWindow *window);
private:
	Input();
	~Input();

	static void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);

	static std::map<int, bool> KeyMap;
};


