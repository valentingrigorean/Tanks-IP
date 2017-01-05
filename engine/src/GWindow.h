#pragma once

#include <string>
#include <assert.h>
#include <map>
#include "GOpengl.h"
#include "GError.h"


typedef void(*OnCloseCallback)();

class GWindow
{
public:
	GWindow(int height = 1024, int width = 768, std::string title = "Tanks 2d");
	~GWindow();

	bool isFullscreen() const;
	void setFullscreen(bool value);

	std::string getTitle() const;

	void init();
	void close();

	void setOnCloseCallback(OnCloseCallback callback);

	void swapBuffers();

	void begin();
	void end();

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
	static std::map<GLFWwindow*, GWindow*> CallbackMap;
};


