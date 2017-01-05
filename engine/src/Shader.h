#pragma once
#include "GOpengl.h"
#include <vector>
#include <map>
#include "io\GFile.h"
#include "GError.h"


class Shader
{
public:
	Shader();
	~Shader();

	Shader& attach(const char* filePath);
	Shader& link();
	
	GLuint get() const;

	Shader& bindAttribute(const char* name,int count,int size, void* offsetPointer = 0);
	Shader& bindUniform(const char* name, GLfloat val);
	Shader& bindUniform(const char* name, const glm::vec2 &v);
	Shader& bindUniform(const char* name, const glm::vec3 &v);
	void use();
	void unuse();

private:
	GLuint create(const char* filePath);
	bool checkIfValid(GLuint id, GLenum type, bool isProgram);
	void printInfoLog(GLuint id,bool isProgram);
private:
	GLuint _program;
	std::vector<GLuint> _shaders;
	std::map<std::string, GLint> _attributes;
	bool _wasLink;
};
