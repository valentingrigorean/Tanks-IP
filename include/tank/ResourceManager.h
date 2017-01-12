#pragma once

#include <map>
#include <string>

#include "graphics/Texture2D.h"
#include "graphics/Shader.h"

class ResourceManager
{
public:
	static Shader& GetShader(std::string name);
	static Shader& LoadShader(std::string& vShaderFile, std::string& fShaderFile,std::string name);

	static Texture2D& GetTexture(std::string name);
	static Texture2D& LoadTexture(std::string& file, std::string name);
	static void Clear();
private:
	ResourceManager();

	static std::map<std::string, Shader*> ShaderMap;
	static std::map<std::string, Texture2D*> TextureMap;
};