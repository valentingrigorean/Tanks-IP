#include <fstream>
#include "File.h"
#include "..\error.h"

namespace tanks::io
{
	std::string File::ReadAllText(const char * path)
	{
		std::ifstream file;
		file.open(path);		
		ASSERT(file.fail(),"Failed to open file");		
		std::string text;
		while (!file.eof())
			std::getline(file, text);
		return text;
	}

	File::File()
	{
	}


	File::~File()
	{
	}
}


