#pragma once
#include <string>


#define RESOURCE_FOLDER std::string("resources")
#define SHADER_FOLDER(file) \
	(RESOURCE_FOLDER + "/shaders/") + file

#define TEXTURE_FOLDER(file) \
	(RESOURCE_FOLDER + "/textures/") + file

#define LEVEL_FOLDER(file)\
	(RESOURCE_FOLDER + "/levels/") + file

#define BOX2D_SCALLING 100.f
#define CONVERT_PPM(pixels) pixels * BOX2D_SCALLING
#define CONVERT_MPP(metters) metters / BOX2D_SCALLING

