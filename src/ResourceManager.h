#pragma once

#include <map>
#include <string>

#include "Texture2D.h"
#include "Shader.h"

class ResourceManager
{
public:
	static Shader& GetShader(std::string name);
	static Shader& LoadShader(const char* vShaderFile, const char* fShaderFile,std::string name);

	static Texture2D& GetTexture(std::string name);
	static Texture2D& LoadTexture(const char* file, std::string name);
	static void Clear();
private:
	ResourceManager();

	static std::map<std::string, Shader*> ShaderMap;
	static std::map<std::string, Texture2D*> TextureMap;
};