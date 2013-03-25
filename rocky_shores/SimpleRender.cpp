#include "SimpleRender.h"

SimpleRender::SimpleRender(void){

}

SimpleRender::~SimpleRender(void){

}

void SimpleRender::setShader(GLuint _shaderId){
	shaderId = _shaderId;

	//register the mvp matrix whit the shader now that its been set
	matrixId = glGetUniformLocation(shaderId, "MVP");
}

//TODO THIS DOES NOT DO ANYTING YET
void SimpleRender::setMatrix(glm::mat4 * _view, glm::mat4 * _projection){
	view = _view;
	projection = _projection;
}

void SimpleRender::render(Drawable * draw){

	//the model view projection matrix is redone every frame (could be much more efficient)
	//glm::mat4 modelViewProjection = *projection * *view * *draw;
	
	glUseProgram(shaderId);    //use the shader that has been set beforehand

	//glUniformMatrix4fv(matrixId, 1, GL_FALSE, &modelViewProjection[0][0]);

	//the vertex position data
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, draw->getVaoId());
	glVertexAttribPointer(
		0,    //layout location 0 is always the vertex pos
		3,    //size of the vertex buffer
		GL_FLOAT,    //type of data, in this case it is gl floats for the vertex
		GL_FALSE,    //not normalized
		0,    //i have no idea what this is (should look it up (and yet i sill haven't))
		0    //the array starts at 0
	);

	//the vertex color data
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, draw->getVaoId());
	glVertexAttribPointer(
		1,
		3,
		GL_FLOAT,
		GL_FALSE,
		0,
		0
	);

	glDrawArrays(GL_TRIANGLES, 0, 3);

	glDisableVertexAttribArray(0);
	
}