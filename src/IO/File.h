#pragma once
#include <string>

namespace tanks::io
{
	class File
	{
	public:
		static std::string ReadAllText(const char* path);
	private:
		File();
		~File();
	};
}
