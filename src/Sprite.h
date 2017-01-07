#pragma once
#include "Texture2D.h"

class Sprite
{
public:
	Sprite(Texture2D &texture);
	Texture2D& GetTexture();

	inline glm::vec2& GetPosition();
	inline glm::vec2& GetSize();
	inline glm::vec3& GetColor();
	
	inline float GetRotate();
	inline void SetRotate(GLfloat rotate);

	inline float GetScale();
	inline void SetScale(GLfloat scale);

	inline glm::mat4& GetModel();
private:
	glm::vec2 _position;
	glm::vec2 _size;
	glm::vec3 _color;
	GLfloat _rotate;	
	GLfloat _scale;
	Texture2D _texture;
};