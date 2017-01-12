#include <tank/ResourceManager.h>
#include <soil/SOIL.h>

std::map<std::string, Shader*> ResourceManager::ShaderMap;
std::map<std::string, Texture2D*> ResourceManager::TextureMap;

Shader& ResourceManager::GetShader(std::string name)
{
	return *ShaderMap[name];
}

Shader& ResourceManager::LoadShader(std::string& vShaderFile, std::string& fShaderFile, std::string name)
{
	auto shader = new Shader;
	shader->AttachFile(vShaderFile.c_str()).
		AttachFile(fShaderFile.c_str()).
		Link();
	ShaderMap[name] = shader;
	return *shader;
}

Texture2D & ResourceManager::GetTexture(std::string name)
{
	return *TextureMap[name];
}

Texture2D& ResourceManager::LoadTexture(std::string& file, std::string name)
{
	auto texture = new Texture2D;
	
	int width, height;

	auto image = SOIL_load_image(file.c_str(), &width, &height, nullptr, SOIL_LOAD_RGBA);

	texture->Generate(width, height, image);
	
	SOIL_free_image_data(image);

	TextureMap[name] = texture;

	return *texture;
}

void ResourceManager::Clear()
{
	for (auto it : ShaderMap)
	{
		it.second->Dispose();
		delete it.second;
	}
	for (auto it : TextureMap)
	{
		it.second->Dispose();
		delete it.second;
	}
	ShaderMap.clear();
	TextureMap.clear();
}