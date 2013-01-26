#include "SimpleRender.h"

SimpleRender::SimpleRender(void){

}

SimpleRender::~SimpleRender(void){

}

void SimpleRender::setShader(GLuint _shaderId){
	shaderId = _shaderId;


}

//TODO THIS DOES NOT DO ANYTING YET
void SimpleRender::setMatrix(glm::mat4 * view, glm::mat4 * projection){

}

void SimpleRender::render(Drawable * draw){
	
	glUseProgram(shaderId);    //use the shader that has been sent down to us from the heavens

	//use the vertex buffer for drawing
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, draw->getVaoId());
	glVertexAttribPointer(
		0,    //layout location 0 is always the vertex pos
		3,    //size of the vertex buffer
		GL_FLOAT,    //type of data, in this case it is gl floats for the vertex
		GL_FALSE,    //not normalized
		0,    //i have no idea what this is (should look it up (and yet i sill haven't)
		0    //the array starts at 0
	);

	glDrawArrays(GL_TRIANGLES, 0, 0);

	glDisableVertexAttribArray(0);
	
}