#include <tank/Utils.h>
#include <tank/GConstants.h>

std::string GetShaderPath(const char * file)
{
	return SHADER_FOLDER(file);
}

std::string GetTexturePath(const char * file)
{
	return TEXTURE_FOLDER(file);
}

std::string GetLevelPath(const char * file)
{
	return LEVEL_FOLDER(file);
}
