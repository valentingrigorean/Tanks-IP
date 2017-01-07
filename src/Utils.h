#pragma once
#include <sstream>

template<typename T>
std::string Convert(T val)
{
	std::ostringstream buff;
	buff << val;
	return buff.str();
}