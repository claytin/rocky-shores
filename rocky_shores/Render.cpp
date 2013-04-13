#include "Render.h"

Render::Render(void) : shader(NULL){

}

Render::~Render(void){

}

void Render::setShader(ShaderProgram * _shader){
	shader = _shader;

	//register the mvp matrix whit the shader now that its been set
	//matrixId = glGetUniformLocation(shaderId, "MVP");
}

//TODO THIS DOES NOT DO ANYTING YET
void Render::setMatrix(glm::mat4 * _view, glm::mat4 * _projection){
	view = _view;
	projection = _projection;
}

void Render::render(Drawable * drawObject){
	glUseProgram(shader->getProgramId());    //use the shader that has been set beforehand

	glBindVertexArray(*drawObject->getVertexArrayId());

	glDrawArrays(GL_TRIANGLES, 0, 3);

	//unbind the vertex array for next render
	glBindVertexArray(0);

	//unbind shader used
	glUseProgram(0);

	glDisableVertexAttribArray(0);
	
}

void Render::compileVertexBuffer(Drawable * drawObject){
	compileVertexBuffer(drawObject->asTriangleFloatArray(), drawObject->getVertexArrayId(), drawObject->getVertexBufferId());

}

void Render::compileVertexBuffer(GLfloat * vertexData, GLuint * VAO, GLuint * VBO){
	// make and bind the VAO
    glGenVertexArrays(1, VAO);
    glBindVertexArray(*VAO);
    
    // make and bind the VBO
    glGenBuffers(1, VBO);
    glBindBuffer(GL_ARRAY_BUFFER, *VBO);
    
    // Put the three triangle verticies into the VBO
    GLfloat vertexData1[] = {
        //  X     Y     Z
         0.0f, 0.8f, 0.0f,
        -0.8f,-0.8f, 0.0f,
         0.8f,-0.8f, 0.0f,
    };
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData1), vertexData1, GL_STATIC_DRAW);
    
    // connect the xyz to the "vert" attribute of the vertex shader
	
	glEnableVertexAttribArray(shader->attrib("vert"));
	glVertexAttribPointer(shader->attrib("vert"), 3, GL_FLOAT, GL_FALSE, 0, NULL);
    
    // unbind the VBO and VAO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}