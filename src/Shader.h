#pragma once
#include "GOpengl.h"
#include <vector>
#include "Point.h"
#include "Color.h"

class Shader
{
public:
	Shader();
	
	void Dispose();

	GLuint GetId() const;

	Shader& AttachFile(const char * filePath);
	Shader& AttachSource(const char* sourceCode,GLenum type);

	Shader& Link();

	Shader& Bind();
	Shader& UnBind();

	Shader& SetFloat(const char* name, GLfloat value);
	Shader& SetInteger(const char* name, GLint);

	Shader& SetVector2f(const char* name, GLfloat x, GLfloat y);
	Shader& SetVector2f(const char* name, glm::vec2 &value);
	Shader& SetVector2f(const char* name, Point& p);

	Shader& SetVector3f(const char* name, GLfloat x, GLfloat y, GLfloat z);
	Shader& SetVector3f(const char* name, glm::vec3 &value);
	Shader& SetVector3f(const char* name, Color& value);

	Shader& SetVector4f(const char* name, GLfloat x, GLfloat y, GLfloat z,GLfloat w);
	Shader& SetVector4f(const char* name, glm::vec4 &value);

	Shader& SetMatrix4f(const char* name, glm::mat4 &value);

private:
	inline GLint GetIdForName(const char* name);
	GLenum GetProgramType(const char* filePath);
	bool CheckIfValid(GLuint id, bool isProgram);
	void PrintInfoLog(GLuint id, bool isProgram);
private:
	GLuint _id;
	std::vector<GLuint> _shaders;
};