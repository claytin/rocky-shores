//Render.h / Render.cpp
//uses a given shader, matrix, and drawable and renders them to the screen
//-mgc480

#pragma once
#include <gl\glew.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include "Drawable.h"
#include "ShaderProgram.h"

class Render{

public:
	Render(void);	//the shader is set to null by default so it will not render untile it has a shader
	~Render(void);

	void setShader(ShaderProgram * shader);	//can only use one shader, pass in the shader id already linked
	void setMatrix(glm::mat4 * view, glm::mat4 * projection);	//set the matrix for rendering, it can only have at a time but can be switched
	void render(Drawable * Drawable);	//renders the given drawable object with the preset shader and matrices
	void compileVertexBuffer(Drawable * object);
	void compileVertexBuffer(GLfloat * vertexData, GLuint * VAO, GLuint * VBO);

private:
	//the shader that will be used for all rendering
	ShaderProgram * shader;

	//the matricies used to transform the object, NOTE: each object has a model matrix
	glm::mat4 * view;
	glm::mat4 * projection;

	//open matrix id of model view project matrix
	GLuint matrixId;

};