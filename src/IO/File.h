#pragma once
#include <string>
#include <vector>

namespace tanks::io
{
	class File
	{
	public:
		static std::string ReadAllText(const char* path);
		static std::vector<char> ReadAllBytes(const char* path);
	private:
		File();
		~File();
	};
}
