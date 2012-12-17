//SimpleRender.h / SimpleRender.cpp
//used to do simple rendering that is not optomised for performances
//it does not require opengl 3.0 and is used in place if the computer does not support it
//its also simple rendering for example load screen
//-mgc480

#pragma once
#include <gl\glew.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

class SimpleRender{

public:
	SimpleRender(void);
	~SimpleRender(void);

	void setShader(GLuint shader);	//can only use one shader, pass in the shader id already linked
	void setMatrix(glm::mat4 * view, glm::mat4 * projection);	//set the matrix for rendering, it can only have at a time but can be switched
	void render();	//simple call that renders everything

private:

	//holds the matrix that will be used in rendering
	glm::mat4 * model;
	glm::mat4 * view;
	glm::mat4 * projection;
	glm::mat4 * modelViewProjection;
};