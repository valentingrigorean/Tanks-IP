#pragma once

#include <string>
#include <GLFW\glfw3.h>
#include <assert.h>
#include <map>
#include "..\error.h"

namespace tanks::engine
{

	typedef void(*OnCloseCallback)();

	class Window
	{
	public:
		Window(int height = 1024, int width = 768, std::string title = "Tanks 2d");
		~Window();

		bool isFullscreen() const;
		void setFullscreen(bool value);

		void init();
		void close();

		void setOnCloseCallback(OnCloseCallback callback);


		inline GLFWwindow* getContext() const
		{
			return _window;
		}
	private:
		static void internalCloseCallback(GLFWwindow* window);
	private:
		int _width;
		int _height;
		bool _fullscreen;		
		bool _isDisposed;
		std::string _title = "";
		OnCloseCallback _onCloseCallback;
		GLFWwindow* _window;
		static std::map<GLFWwindow*, Window*> CallbackMap;
	};
}

