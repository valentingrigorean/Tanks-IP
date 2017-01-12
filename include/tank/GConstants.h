#pragma once
#include <string>


#define RESOURCE_FOLDER std::string("resources")
#define SHADER_FOLDER(file) \
	(RESOURCE_FOLDER + "/shaders/") + file

#define TEXTURE_FOLDER(file) \
	(RESOURCE_FOLDER + "/textures/") + file

#define LEVEL_FOLDER(file)\
	(RESOURCE_FOLDER + "/levels/") + file

const float M2P = 20.f;
const float P2M = 1.f / M2P;

#define RADIAN_TO_DEGREES(r) r*57.2958f

