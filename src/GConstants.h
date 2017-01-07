#pragma once
#include <string>

#define RESOURCE_FOLDER std::string("resources")
#define SHADER_FOLDER(file) \
	(RESOURCE_FOLDER + "/shaders/") + file

#define TEXTURE_FOLDER(file) \
	(RESOURCE_FOLDER + "/textures/") + file