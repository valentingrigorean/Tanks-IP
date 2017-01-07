#include "ResourceManager.h"
#include <soil\SOIL.h>

std::map<std::string, Shader*> ResourceManager::ShaderMap;
std::map<std::string, Texture2D*> ResourceManager::TextureMap;

Shader& ResourceManager::GetShader(std::string name)
{
	return *ShaderMap[name];
}

Shader& ResourceManager::LoadShader(const char * vShaderFile, const char * fShaderFile, std::string name)
{
	auto shader = new Shader;
	shader->AttachFile(vShaderFile).
		AttachFile(fShaderFile).
		Link();
	ShaderMap[name] = shader;
	return *shader;
}

Texture2D & ResourceManager::GetTexture(std::string name)
{
	return *TextureMap[name];
}

Texture2D& ResourceManager::LoadTexture(const char * file, std::string name)
{
	auto texture = new Texture2D;
	
	int width, height;

	auto image = SOIL_load_image(file, &width, &height, nullptr, SOIL_LOAD_RGBA);

	texture->Generate(width, height, image);
	
	SOIL_free_image_data(image);

	TextureMap[name] = texture;

	return *texture;
}

void ResourceManager::Clear()
{
	for (auto it : ShaderMap)
		delete it.second;
	for (auto it : TextureMap)
		delete it.second;

	ShaderMap.clear();
	TextureMap.clear();
}