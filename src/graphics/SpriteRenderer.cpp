#include <tank/graphics/SpriteRenderer.h>

SpriteRender::SpriteRender()
{

}

SpriteRender::SpriteRender(Shader& shader)
{
	_shader = shader;
	Init();
}

SpriteRender::~SpriteRender()
{
	glDeleteVertexArrays(1, &_vao);
}

void SpriteRender::DrawSprite(Shader & shader, Sprite & sprite, Transform2D & transform)
{
	shader.Bind().
		SetMatrix4f("model", transform.GetModel()).
		SetVector3f("spriteColor", sprite.GetColor()).
		SetInteger("flipX", sprite.GetFlipX()).
		SetInteger("flipY", sprite.GetFlipY());

	sprite.GetTexture().Bind();

	glBindVertexArray(_vao);

	glDrawArrays(GL_TRIANGLES, 0, 6);

	sprite.GetTexture().UnBind();

	_shader.UnBind();
	glBindVertexArray(0);
}

void SpriteRender::DrawSprite(Sprite & sprite, Transform2D & transform)
{
	DrawSprite(_shader, sprite, transform);
}

void SpriteRender::Init()
{
	GLfloat vertices[] =
	{
		//Pos			//Tex
		0.0f, 1.0f,		0.0f, 1.0f,
		1.0f, 0.0f,		1.0f, 0.0f,
		0.0f, 0.0f,		0.0f, 0.0f,

		0.0f, 1.0f,		0.0f, 1.0f,
		1.0f, 1.0f,		1.0f, 1.0f,
		1.0f, 0.0f,		1.0f, 0.0f
	};

	GLuint vbo;
	glGenVertexArrays(1, &_vao);
	glGenBuffers(1, &vbo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(_vao);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}