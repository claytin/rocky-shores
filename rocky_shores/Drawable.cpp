#include "Drawable.h"

Drawable::Drawable(void){

}

Drawable::~Drawable(void){

}

void Drawable::compileVao(void){
	glDeleteBuffers(1, &vertexArrayObjectId);    //clear the buffer in case it was holding anything before operating on it

	GLfloat * vertexArray = asTriangleFloatArray();    //holds the floats (as opengl floats) from this objects mesh

	//fairly strait forward, just creats a vertex array buffer from the mesh, if you don't know what it does then learn da openglz
	glGenBuffers(1, &vertexArrayObjectId);
	glBindBuffer(GL_ARRAY_BUFFER, vertexArrayObjectId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * (faces.size() * 3 * 3), vertexArray, GL_STATIC_DRAW);

	//well our work here is done, that was pretty simple
}