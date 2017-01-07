#include <fstream>
#include "GFile.h"
#include "..\GError.h"
#include <stdio.h>

#if _WIN32
#include <Windows.h>
#endif


GFile::GFile()
{
}



std::string GFile::ReadAllText(const char * path)
{
	std::ifstream file;
	file.open(path);
	if (file.fail())
		FATAL_ERROR(std::string("Failed to open file:") + path);
	std::string line;
	std::string sb;
	while (!file.eof())
	{
		std::getline(file, line);
		sb.append(line).append("\n");
	}
	return sb;
}

std::vector<char> GFile::ReadAllBytes(const char * path)
{
	std::ifstream file;
	file.open(path, std::ios::binary);
	if (file.fail())
		FATAL_ERROR(std::string("Failed to open file:") + path);
	return std::vector<char>(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
}
std::string GFile::GetExtension(const char * path)
{
	std::string temp(path);
	auto index = temp.find_last_of('.');
	if (index < 0)
		return std::string();
	return temp.substr(index, temp.size() - index);
}
bool GFile::Exists(const char * path)
{
	
	return false;
}

#undef GetCurrentDirectory
std::string GFile::GetCurrentDirectory()
{
#if _WIN32
	char result[MAX_PATH];
	return std::string(result, GetModuleFileName(NULL, result, MAX_PATH));
#else
	return std::string();
#endif
}

#ifdef UNICODE
#define GetCurrentDirectory  GetCurrentDirectoryW
#else
#define GetCurrentDirectory  GetCurrentDirectoryA
#endif

