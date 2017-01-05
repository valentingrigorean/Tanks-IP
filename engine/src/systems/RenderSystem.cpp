#include "RenderSystem.h"
#include "..\GConstants.h"


GLuint vao;
GLuint vbo;

RenderSystem::RenderSystem(Graphics *graphics) :_graphics(graphics)
{
}


RenderSystem::~RenderSystem()
{
	_shader.unuse();
}

void RenderSystem::update(float dt)
{
	_graphics->begin();
	_shader.use();
	_shader.bindUniform("triangleColor", glm::vec3((sin(dt * 4.0f) + 1.0f) / 2.0f, 0.0f, 0.0f));
	glDrawArrays(GL_TRIANGLES, 0, 3);
	std::cout << dt << std::endl;
	_shader.unuse();
	_graphics->end();
}

void RenderSystem::init()
{
	_shader.attach((SHADER_FOLDER + "main.frag").c_str()).
		attach((SHADER_FOLDER + "main.vert").c_str());

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// Create a Vertex Buffer Object and copy the vertex data to it
	GLuint vbo;
	glGenBuffers(1, &vbo);

	float vertices[] = {
		0.0f,  0.5f, 1.0f, 0.0f, 0.0f, // Vertex 1: Red
		0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // Vertex 2: Green
		-0.5f, -0.5f, 0.0f, 0.0f, 1.0f  // Vertex 3: Blue
	};
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	_shader.link();
	_shader.bindAttribute("position",2, 5 * sizeof(float),0);
	_shader.bindAttribute("color", 3, 5 * sizeof(float), (void*)(2 * sizeof(float)));	

}
void RenderSystem::sendMessage()
{
}
