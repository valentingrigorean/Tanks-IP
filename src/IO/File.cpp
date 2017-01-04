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

	std::string File::readAllText(const char * path)
	{
		std::ifstream file;
		file.open(path);		
		ASSERT(file.fail(),"Failed to open file");		
		std::string text;
		while (!file.eof())
			std::getline(file, text);
		return text;
	}

	std::vector<char> File::readAllBytes(const char * path)
	{
		std::ifstream file;
		file.open(path,std::ios::binary);
		ASSERT(file.fail(), "Failed to open file");
		return std::vector<char>(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
	}
	std::string File::getExtension(const char * path)
	{
		std::string temp(path);
		auto index = temp.find_last_of('.');
		if (index < 0)
			return std::string();
		return temp.substr(index, temp.size() - index);
	}
}


