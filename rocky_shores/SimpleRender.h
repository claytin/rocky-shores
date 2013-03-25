//SimpleRender.h / SimpleRender.cpp
//used to do simple rendering that is not optomised for performances
//-mgc480

#pragma once
#include <gl\glew.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include "Drawable.h"

class SimpleRender{

public:
	SimpleRender(void);
	~SimpleRender(void);

	void setShader(GLuint shaderId);	//can only use one shader, pass in the shader id already linked
	void setMatrix(glm::mat4 * view, glm::mat4 * projection);	//set the matrix for rendering, it can only have at a time but can be switched
	void render(Drawable * Drawable);	//renders the given drawable object with the preset shader and matrices

private:
	//the shader that will be used for all rendering
	GLuint shaderId;

	//the matricies used to transform the object, NOTE: each object has a model matrix
	glm::mat4 * view;
	glm::mat4 * projection;

	//open matrix id of model view project matrix
	GLuint matrixId;

};