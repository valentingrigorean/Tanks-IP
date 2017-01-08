#pragma once
#include <string>
#include <vector>

class GFile
{
public:
	static std::string ReadAllText(const char* path);
	static std::vector<std::string> ReadAllLines(const char* path);
	static std::vector<char> ReadAllBytes(const char* path);
	static std::string GetExtension(const char* path);
	static bool Exists(const char* path);
	static std::string GetCurrentDirectory();
private:
	GFile();	
};
