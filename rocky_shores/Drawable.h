//Drawable.h / Drawable.cpp
//base class for any sprite or object that can be rendered
//has position, a mesh, and optionaly texture or color

#pragma once
#include <glm\glm.hpp>
#include "Mesh.h"
#include <gl\glew.h>

class Drawable : glm::mat4{    //it uses glm::mat4 as its model space matrix

public:
	Drawable(void);
	~Drawable(void);

	void compileVao(void);    //compile the mesh of the object into a simple vao with the veretices from Mesh::asTraiangleArray function

private:
	Mesh mesh;    //the mesh used for this object, each object of this type can only have one mesh

	GLuint vertexArrayObjectId;    //this holds the mesh that has been compiled as a vao
	GLuint textureId;    //holds the texture of the mesh if there is one, not required if the mesh doesn't have a texture
};

