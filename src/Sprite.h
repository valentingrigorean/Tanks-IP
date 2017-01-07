#pragma once
#include <glm\glm.hpp>
#include "Texture2D.h"

class Sprite
{
public:
	Sprite(Texture2D &texture);
	Texture2D& GetTexture();

	glm::vec2& GetPosition();
	glm::vec2& GetSize();
	glm::vec3& GetColor();
	
	float GetRotate();
	void SetRotate(GLfloat rotate);

	float GetScale();
	void SetScale(GLfloat scale);

	glm::mat4 GetModel();
private:
	glm::vec2 _position;
	glm::vec2 _size;
	glm::vec3 _color;
	GLfloat _rotate;	
	GLfloat _scale;
	Texture2D _texture;
};