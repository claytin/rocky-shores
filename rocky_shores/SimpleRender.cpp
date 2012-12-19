#include "SimpleRender.h"

SimpleRender::SimpleRender(void){

}

SimpleRender::~SimpleRender(void){

}

void SimpleRender::setShader(GLuint _shaderId){
	shaderId = _shaderId;

		//THIS IS BAD AND ONLY FOR TESTING
	static const GLfloat vertex[] = {
		0.0f, 1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		-1.0f, -1.0f, 0.0f
	};

	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW);
}

//THIS DOES NOT DO ANYTING YET
void SimpleRender::setMatrix(glm::mat4 * view, glm::mat4 * projection){

}

void SimpleRender::render(void){
	glUseProgram(shaderId);    //use the shader that has been sent down to us from the heavens

	//use the vertex buffer for drawing
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(
		0,    //layout location 0 is always the vertex pos
		3,    //size of the vertex buffer
		GL_FLOAT,    //type of data, in this case it is gl floats for the vertex position
		GL_FALSE,    //not normalized
		0,    //i have no idea what this is (shold look it up)
		0    //the array starts at 0
	);

	glDrawArrays(GL_TRIANGLES, 0, 3);

	glDisableVertexAttribArray(0);
}