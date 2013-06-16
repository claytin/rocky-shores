//Drawable.h / Drawable.cpp
//base class for any sprite or object that can be rendered
//has position, a mesh, and optionaly texture or color
//-mgc480

#pragma once
#include <glm\glm.hpp>
#include "Mesh.h"
#include <gl\glew.h>

class Drawable : public Mesh, public glm::mat4{    //it uses glm::mat4 as its model space matrix because every drawable object must have a position (z can be left 0 for 2d space)

public:
	Drawable(void);
	~Drawable(void);

	GLuint * getVertexArrayId(void){    //get the id of the vertex buffer object as a opengl unsigned integer
		return &vertexArrayId;
	}

	GLuint * getVertexBufferId(void){
		return &vertexBufferId;
	}
private:

	GLuint vertexArrayId;    //holds the vertex buffer data as a vertex array
	GLuint vertexBufferId;    //where the vertex data is held

	GLuint textureId;    //holds the texture of the mesh if there is one, not required if the mesh doesn't have a texture
};