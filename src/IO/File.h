#pragma once
#include <string>
#include <vector>

namespace tanks::io
{
	class File
	{
	public:
		static std::string readAllText(const char* path);
		static std::vector<char> readAllBytes(const char* path);
		static std::string getExtension(const char* path);
		static bool exists(const char* path);
		static std::string getCurrentDirectory();
	private:
		File();
		~File();
	};
}
