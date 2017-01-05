#pragma once
#include "GOpengl.h"
#include <vector>
#include "io\GFile.h"
#include "GError.h"


class Shader
{
public:
	Shader();
	~Shader();

	Shader& attach(const char* filePath);
	Shader& link();
	void bind(GLuint location, float value);
	void bind(GLuint location, glm::mat4 const & matrix);
	void use();
	void unuse();

private:
	GLuint create(const char* filePath);
	bool checkIfValid(GLuint id, GLenum type, bool isProgram);
	void printInfoLog(GLuint id);
private:
	GLuint _program;
	std::vector<GLuint> _shaders;
};
