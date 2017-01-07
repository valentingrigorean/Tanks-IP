#pragma once
#include <sstream>
#include "GConstants.h"

template<typename T>
std::string Convert(T val)
{
	std::ostringstream buff;
	buff << val;
	return buff.str();
}

template<typename T>
inline T Clamp(T val, T min, T max)
{
	if (val < min)
		return min;
	if (val > max)
		return max;
	return val;
}

std::string GetShaderPath(const char* file)
{
	return SHADER_FOLDER(file);
}

std::string GetTexturePath(const char* file)
{
	return TEXTURE_FOLDER(file);
}