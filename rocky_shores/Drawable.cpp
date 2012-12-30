#include "Drawable.h"

Drawable::Drawable(void){

}

Drawable::~Drawable(void){

}

void Drawable::compileVao(void){
	glDeleteBuffers(1, &vertexArrayObjectId);    //clear the buffer in case it was holding anything before operating on it
	std::cout << vertexArrayObjectId << std::endl;
	const GLfloat * vertexArray = (GLfloat*)asTriangleFloatArray();    //the data that the vertex array object will be filled with
	//this data is unorganized, unoptomized, and extreamly repetative, use with caution because it is really ineficient

	//fairly strait forward, just creats a vertex array buffer from the mesh, if you don't know what it does then learn da openglz
	glGenBuffers(1, &vertexArrayObjectId);
	glBindBuffer(GL_ARRAY_BUFFER, vertexArrayObjectId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexArray), vertexArray, GL_STATIC_DRAW);

	std::cout << vertexArrayObjectId << std::endl;

	//well our work here is done, that was pretty simple
}