#include <iostream>
#include "Window.h"

int main(char ** argv, int argc) {
	auto* window = new tanks::Window();
	window->init();

	int a;
	std::cin >> a;
	delete window;
	return 0;
}