#pragma once
#include <string>
#include <vector>

class GFile
{
public:
	static std::string readAllText(const char* path);
	static std::vector<char> readAllBytes(const char* path);
	static std::string getExtension(const char* path);
	static bool exists(const char* path);
	static std::string getCurrentDirectory();
private:
	GFile();
	~GFile();
};
