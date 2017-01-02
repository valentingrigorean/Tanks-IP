#pragma once

#include <string>
#include <GLFW\glfw3.h>
#include <assert.h>
#include "error.h"

namespace tanks
{
	class Window
	{
	public:
		Window(int height = 1024, int width = 768, std::string title = "Tanks 2d");
		~Window();

		bool is_fullscreen() const;
		void set_fullscreen(bool value);

		void init();
		void close();

	private:
		int _width;
		int _height;
		bool _fullscreen;
		bool _wasInit;
		std::string _title = "";
		GLFWwindow* _window;
	};
}

