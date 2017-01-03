#pragma once
#include "Window.h"
#include <map>

namespace tanks::engine
{
	class Input
	{
	public:
		static bool getKey(int keyCode);
		static bool getKey(char key);
		static void pollEvents();
		static void registerWindow(Window *window);
		static void unregisterWindow(Window *window);
	private:
		Input();
		~Input();

		static void KeyCallback(GLFWwindow *window,int key,int scancode,int action,int mods);

		static std::map<int, bool> KeyMap;
	};
}

