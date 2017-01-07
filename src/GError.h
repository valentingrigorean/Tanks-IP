#pragma once

#include <string>
#include <iostream>
#include <exception>

#define FATAL_ERROR(message)\
	{\
		std::cerr << "Error in " << __FILE__ << " line " << __LINE__ << ": " << message << std::endl; \
		std::terminate(); \
	}
