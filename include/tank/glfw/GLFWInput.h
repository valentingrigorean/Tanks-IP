#pragma once
#include "../Input.h"
#include "../graphics/GOpengl.h"
#include <map>
#include <vector>

class GLFWInput : public Input
{
public:
	GLFWInput();
	~GLFWInput();
	bool GetKey(int keyCode);
	bool GetKey(char key);
	void PollEvents();
	void RegisterWindow(GLFWwindow *window);
private:
	
	static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);	
	static std::map<GLFWInput*, std::vector<GLFWwindow*>> RegisterMap;
	static std::map<int, bool> KeysMap;
};