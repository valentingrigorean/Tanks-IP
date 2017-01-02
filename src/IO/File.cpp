#include <fstream>
#include "File.h"
#include "..\error.h"

namespace tanks::io
{
	File::File()
	{
	}


	File::~File()
	{
	}

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

	std::vector<char> File::ReadAllBytes(const char * path)
	{
		std::ifstream file;
		file.open(path,std::ios::binary);
		ASSERT(file.fail(), "Failed to open file");
		return std::vector<char>(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
	}	
}


